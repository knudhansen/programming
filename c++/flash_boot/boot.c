#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCCESS 0
#define FAILURE 1

#define NUMBER_OF_CHAR_PER_BYTE 2

#define NVRAM_BYTE_COUNT_MAGIC_WORD 4
#define PARTITION_TABLE_HEADER_BYTE_SIZE 

uint8_t nvram[512*1024];

//typedef struct nvram_struct {
//    uint8_t **sectorData;
//    int sectorByteSize;
//    int sectorCount;
//    uint8_t eraseValue;
//} nvram_t; 

typedef enum partitionType_enum {
    BOOT_PARTITION,
    NONBOOT_PARTITION
} partitionType_t;

typedef uint8_t guid_t[16];
typedef uint64_t lba_t;

const guid_t guidPartitionTypeBoot = {0x21, 0x68, 0x61, 0x48, 0x64, 0x49, 0x6E, 0x6F,
                                      0x74, 0x4E, 0x65, 0x65, 0x64, 0x45, 0x46, 0x49};

typedef struct partitionTableHeader_struct {
    char name[8];
    uint32_t revision;
    uint32_t firstPartitionHeaderAddress;
    uint32_t partitionHeaderSize;
    uint32_t crc;
} partitionTableHeader_t;

typedef struct partitionHeader_struct {
    guid_t type;
    guid_t guid;
    lba_t firstLba;
    lba_t lastLba;
    uint64_t attributeFlags;
    char name[68];
    uint32_t crc;
} partitionHeader_t;


static int boot(uint8_t *nvram);

static int initializeNvram(uint8_t *nvram, const char *filePath);
static int readMagicWord(uint8_t **nvramPtr);
static int readPartitionTableHeader(partitionTableHeader_t *partitionTableHeader, uint8_t **nvramPtr);
static int readPartitionHeader(partitionHeader_t *partitionHeader, uint8_t *nvramPtr);
static bool isBootPartition(partitionHeader_t *partitionHeader);
static bool isEndOfPartitionTable(partitionHeader_t *partitionHeader);
static void printPartitionTableHeader(partitionTableHeader_t *partitionTableHeader);

static char*    getUint8ArrayHexString(const uint8_t *ptr, const int length);
static char*    getUint8ArrayString(const uint8_t *ptr, const int length);
static uint32_t getUint8ArrayUint32(const uint8_t *ptr);
static uint64_t getUint8ArrayUint64(const uint8_t *ptr);

static uint32_t computeCrc32(const uint8_t *ptr, int byteLength);


int main(int argc, char *argv[]) {
    printf("booting from all zeroes\n");
    boot(nvram);

    printf("booting from all ones\n");
    memset(nvram, 1, sizeof(nvram));
    boot(nvram);

    printf("booting from nvram image with 2 valid boot partitions\n");
    if (initializeNvram(nvram, argv[1]) != SUCCESS) {
	printf("Error: could not open file %s!\n", argv[1]);
	return -1;
    }        
    boot(nvram);

//    printf("booting from nvram image with 2 valid boot partitions, the first of which gets erased\n");
//    if (initializeNvram(nvram, argv[1]) != SUCCESS) {
//	printf("Error: could not open file %s!\n", argv[1]);
//	return -1;
//    }        
//    eraseSector(nvram, 1, 0xff);
//    boot(nvram);
}

static int boot(uint8_t *nvram) {
    int i;

    uint8_t *nvramReadPtr;
    nvramReadPtr = nvram;

    if (readMagicWord(&nvramReadPtr) != SUCCESS) {
        printf("    Error: magic word mismatch\n");
        return -1;
    }
    
    partitionTableHeader_t partitionTableHeader;
    if (readPartitionTableHeader(&partitionTableHeader, &nvramReadPtr) != SUCCESS) {
        printf("    Error reading the partition table header\n");
        return -1;
    }
    //    printPartitionTableHeader(&partitionTableHeader);

    nvramReadPtr = &(nvram[partitionTableHeader.firstPartitionHeaderAddress]);
    for (i = 0; ; i++) {
        partitionHeader_t partitionHeader;
        if (isEndOfPartitionTable(&partitionHeader)) {
            printf("    partition %2d: reached end of partition table... No boot partition found\n", i);
            return -1;
        } else if (readPartitionHeader(&partitionHeader, nvramReadPtr) != SUCCESS) {
            printf("    partition %2d: Wrong header in CRC\n", i);
        } else if (isBootPartition(&partitionHeader)) {
            printf("    partition %2d: found boot partition... Booting from it\n", i);
            break;
        } else {
            printf("    partition %2d: unknown partition type\n", i);
        }
        nvramReadPtr += partitionTableHeader.partitionHeaderSize;
    }
    
    return 0;
}

static int initializeNvram(uint8_t *nvram, const char *filePath) {
    FILE *nvramContent = fopen(filePath,"r");
    if (nvramContent == NULL) {
	return FAILURE;
    }
    
    int nvram_idx = 0;
    
    ssize_t read;
    char *line = (char*)malloc((NUMBER_OF_CHAR_PER_BYTE + 1) * sizeof(char));
    size_t len = 0;
    while ((read = getline(&line, &len, nvramContent)) != -1) {

        /** check if the line is a comment **/
        if (strncmp(line, "//", 2) == 0) {
            continue;
        }

        /** remove characters pasted the NUMBER_OF_CHAR_PER_BYTE first characters **/
        line[NUMBER_OF_CHAR_PER_BYTE] = (char)0;

        /** convert the line to a number **/
        char *strEnd;
        nvram[nvram_idx++] = (uint8_t)strtoul(line,&strEnd, 16);
    }
    free(line);
    fclose(nvramContent);
    return SUCCESS;
}

static int readMagicWord(uint8_t **nvramPtr) {
    //    printf("%20s: %s\n","Magic Word", getUint8ArrayHexString(*nvramPtr, NVRAM_BYTE_COUNT_MAGIC_WORD));
    bool magicWordMatch = ((*nvramPtr)[0] == 0xfe) && ((*nvramPtr)[1] == 0xde) && ((*nvramPtr)[2] == 0xbe) && ((*nvramPtr)[3] == 0xda);
    (*nvramPtr) += NVRAM_BYTE_COUNT_MAGIC_WORD;
    return magicWordMatch?SUCCESS:FAILURE;
}

static int readPartitionTableHeader(partitionTableHeader_t *partitionTableHeader, uint8_t **nvramPtr) {
    uint32_t computedCrc = computeCrc32(*nvramPtr, sizeof(*partitionTableHeader) - sizeof(partitionTableHeader->crc));
    *nvramPtr += 8;
    partitionTableHeader->revision = getUint8ArrayUint32(*nvramPtr);
    *nvramPtr += 4;
    partitionTableHeader->firstPartitionHeaderAddress = getUint8ArrayUint32(*nvramPtr);    
    *nvramPtr += 4;
    partitionTableHeader->partitionHeaderSize = getUint8ArrayUint32(*nvramPtr);
    *nvramPtr += 4;
    partitionTableHeader->crc = getUint8ArrayUint32(*nvramPtr);
    *nvramPtr += 4;
    if (computedCrc == partitionTableHeader->crc) {
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

static int readPartitionHeader(partitionHeader_t *partitionHeader, uint8_t *nvramPtr) {
    uint8_t *ptr;
    uint32_t computedCrc = computeCrc32(nvramPtr, sizeof(*partitionHeader) - sizeof(partitionHeader->crc));
    ptr = nvramPtr;
    memcpy(partitionHeader->type, ptr, sizeof(partitionHeader->type));
    ptr += sizeof(partitionHeader->type);
    memcpy(partitionHeader->guid, ptr, sizeof(partitionHeader->guid));
    ptr += sizeof(partitionHeader->guid);
    partitionHeader->firstLba = getUint8ArrayUint64(ptr);
    ptr += sizeof(partitionHeader->firstLba);
    partitionHeader->lastLba = getUint8ArrayUint64(ptr);
    ptr += sizeof(partitionHeader->lastLba);
    partitionHeader->attributeFlags = getUint8ArrayUint64(ptr);
    ptr += sizeof(partitionHeader->attributeFlags);
    memcpy(partitionHeader->name, ptr, sizeof(partitionHeader->name));
    ptr += sizeof(partitionHeader->name);
    partitionHeader->crc = getUint8ArrayUint32(ptr);
    ptr += sizeof(partitionHeader->crc);
    if (computedCrc == partitionHeader->crc) {
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

static bool isBootPartition(partitionHeader_t *partitionHeader) {
    return (0 == memcmp(partitionHeader->type, guidPartitionTypeBoot, sizeof(partitionHeader->type)));
}

static bool isEndOfPartitionTable(partitionHeader_t *partitionHeader) {
    int i;
    for (i = 0; i < sizeof(partitionHeader->type); i++) {
        if (partitionHeader->type[i] != 0x00) {
            return false;
        }
    }
    for (i = 0; i < sizeof(partitionHeader->type); i++) {
        if (partitionHeader->type[i] == 0xff) {
            return false;
        }
    }
    return true;
}
static void printPartitionTableHeader(partitionTableHeader_t *partitionTableHeader) {
    printf("%20s:%20s:%04x\n","PT Header","revision",partitionTableHeader->revision);
    printf("%20s:%20s:%04x\n","","first PH address",partitionTableHeader->firstPartitionHeaderAddress);
    printf("%20s:%20s:%04x\n","","PH size",partitionTableHeader->partitionHeaderSize);
    printf("%20s:%20s:%04x\n","","PH CRC",partitionTableHeader->crc);
}
static void printPartitionHeader(partitionHeader_t *partitionHeader) {
}

static char* getUint8ArrayHexString(const uint8_t *ptr, const int length) {
    int i;
    char *string = (char*)malloc((length*2+1)*sizeof(char));
    char *returnString = string;
    for (i = 0; i < length; i++) {
        sprintf(string, "%02x", ptr[i]);
        string += 2;
    }
    *string = (char)0;
    return returnString;
}
static char* getUint8ArrayString(const uint8_t *ptr, const int length) {
    int i;
    char *string = (char*)malloc((length*2+1)*sizeof(char));
    char *returnString = string;
    for (i = 0; i < length; i++) {
        string[i] = ptr[i];
    }
    string[length] = (char)0;
    return returnString;
}
static uint32_t getUint8ArrayUint32(const uint8_t *ptr) {
    int i;
    uint32_t returnValue = 0;
    for (i = 0; i < 4; i++) {
        returnValue <<= 8;
        returnValue += ptr[i];
    }
    return returnValue;
}
static uint64_t getUint8ArrayUint64(const uint8_t *ptr) {
    int i;
    uint64_t returnValue = 0;
    for (i = 0; i < 8; i++) {
        returnValue <<= 8;
        returnValue += ptr[i];
    }
    return returnValue;
}

static uint32_t computeCrc32(const uint8_t *ptr, int byteLength) {
    int i;
    uint32_t crc;
    crc = 0;
    for (i = 0; i < byteLength; i++) {
      crc = crc^ptr[i];
    }
    return crc;
}
