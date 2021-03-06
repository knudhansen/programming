#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCCESS 0
#define FAILURE 1

#define NUMBER_OF_CHAR_PER_BYTE 2

#define PRIMARY_PARTITION_TABLE_HEADER_BYTE_OFFSET 0x000
#define BACKUP_PARTITION_TABLE_HEADER_BYTE_OFFSET  0x400


typedef struct nvram_struct {
    uint8_t **sectorData;
    int sectorByteSize;
    int sectorCount;
    uint8_t eraseValue;
} nvram_t; 

typedef enum partitionType_enum {
    BOOT_PARTITION,
    NONBOOT_PARTITION
} partitionType_t;

typedef uint8_t guid_t[16];

const guid_t guidPartitionTypeBoot = {0x21, 0x68, 0x61, 0x48, 0x64, 0x49, 0x6E, 0x6F,
                                      0x74, 0x4E, 0x65, 0x65, 0x64, 0x45, 0x46, 0x49};

typedef struct partitionTableHeader_struct {
    char name[8];
    uint32_t revision;
    uint32_t firstPartitionHeaderAddress;
    uint32_t partitionEntrySize;
    uint32_t crc;
} partitionTableHeader_t;

typedef struct partitionEntry_struct {
    guid_t type;
    uint32_t address;
    uint32_t size;
    uint64_t attributeFlags;
    char name[28];
    uint32_t crc;
} partitionEntry_t;

static void createNvram(nvram_t *nvram, int sectorByteSize, int sectorCount, uint8_t eraseValue);
static void deleteNvram(nvram_t *nvram);
static void printNvram(nvram_t *nvram);
static void readNvram(const nvram_t *nvram, uint32_t address, uint8_t *data, int size);
static void writeNvram(nvram_t *nvram, uint32_t address, const uint8_t *data, int size);
static int writeNvramFromFile(nvram_t *nvram, uint32_t address, const char *filePath);
static void eraseSectorNvram(nvram_t *nvram, int sectorIndex);
 
static int boot(nvram_t *nvram);

static int readPartitionTableHeader(nvram_t *nvram, partitionTableHeader_t *partitionTableHeader, uint32_t *address);
static int readPartitionHeader(nvram_t *nvram, partitionEntry_t *partitionEntry, uint32_t *address);
static bool isBootPartition(partitionEntry_t *partitionEntry);
static bool isEndOfPartitionTable(partitionEntry_t *partitionEntry);
static void printPartitionTableHeader(partitionTableHeader_t *partitionTableHeader);

static char*    getUint8ArrayHexString(const uint8_t *ptr, const int length);
static char*    getUint8ArrayString(const uint8_t *ptr, const int length);
static uint32_t getUint8ArrayUint32(const uint8_t *ptr);
static uint64_t getUint8ArrayUint64(const uint8_t *ptr);

static uint32_t computeCrc32(const uint8_t *ptr, int byteLength);


int main(int argc, char *argv[]) {
    int i;
    nvram_t nvram;
    createNvram(&nvram, 512, 10, 0xff);
    for (i = 0; i < nvram.sectorCount; i++) {
        eraseSectorNvram(&nvram, i);
    }
    
    printf("booting from erased nvram\n");
    boot(&nvram);

    printf("booting from nvram.image\n");
    writeNvramFromFile(&nvram, 0, "nvram.image");
    printNvram(&nvram);
    boot(&nvram);
//
//    printf("booting from nvram.image where 0st sector was erased\n");
//    eraseSectorNvram(&nvram, 1);
//    boot(&nvram);

    deleteNvram(&nvram);
}

static int boot(nvram_t *nvram) {
    int i;

    uint32_t nvramPtr = 0;

    nvramPtr = PRIMARY_PARTITION_TABLE_HEADER_BYTE_OFFSET;
    partitionTableHeader_t partitionTableHeader;
    if (readPartitionTableHeader(nvram, &partitionTableHeader, &nvramPtr) != SUCCESS) {
        printf("    Error reading the partition table header\n");
        return -1;
    }

//    nvramPtr = partitionTableHeader.firstPartitionHeaderAddress;
//    for (i = 0; ; i++) {
//        partitionEntry_t partitionEntry;
//        uint8_t crcCheck = readPartitionHeader(nvram, &partitionEntry, &nvramPtr);
//        if (isEndOfPartitionTable(&partitionEntry)) {
//            printf("    partition %2d: reached end of partition table... No boot partition found\n", i);
//            return -1;
//        } else if (crcCheck != SUCCESS) {
//            printf("    partition %2d: Wrong header in CRC\n", i);
//        } else if (isBootPartition(&partitionEntry)) {
//            printf("    partition %2d: found boot partition... Booting from it\n", i);
//            break;
//        } else {
//            printf("    partition %2d: unknown partition type\n", i);
//        }
//        nvramPtr += partitionTableHeader.partitionEntrySize;
//    }
    
    return 0;
}

static int readPartitionTableHeader(nvram_t *nvram, partitionTableHeader_t *partitionTableHeader, uint32_t *address) {
    uint8_t partitionTableHeaderRead[sizeof(*partitionTableHeader)];
    readNvram(nvram, *address, partitionTableHeaderRead, sizeof(partitionTableHeaderRead));

    uint8_t *ptr = partitionTableHeaderRead;
    uint32_t computedCrc = computeCrc32(partitionTableHeaderRead, sizeof(partitionTableHeaderRead) - sizeof(partitionTableHeader->crc));
    ptr += 8;
    partitionTableHeader->revision = getUint8ArrayUint32(ptr);
    ptr += 4;
    partitionTableHeader->firstPartitionHeaderAddress = getUint8ArrayUint32(ptr);    
    ptr += 4;
    partitionTableHeader->partitionEntrySize = getUint8ArrayUint32(ptr);
    ptr += 4;
    partitionTableHeader->crc = getUint8ArrayUint32(ptr);
    ptr += 4;

    address += sizeof(partitionTableHeaderRead);

    if (computedCrc == partitionTableHeader->crc) {
        return SUCCESS;
    } else {
	printf("expected %08x, read %08x\n", computedCrc, partitionTableHeader->crc);
        return FAILURE;
    }
}

static int readPartitionEntry(nvram_t *nvram, partitionEntry_t *partitionEntry, uint32_t *address) {
    uint8_t partitionEntryRead[sizeof(*partitionEntry)];
    readNvram(nvram, *address, partitionEntryRead, sizeof(partitionEntry));

    uint8_t *ptr = partitionEntryRead;
    uint32_t computedCrc = computeCrc32(partitionEntryRead, sizeof(partitionEntryRead) - sizeof(partitionEntry->crc));
    memcpy(partitionEntry->type, ptr, sizeof(partitionEntry->type));
    ptr += sizeof(partitionEntry->type);
    partitionEntry->address = getUint8ArrayUint64(ptr);
    ptr += sizeof(partitionEntry->address);
    partitionEntry->size = getUint8ArrayUint64(ptr);
    ptr += sizeof(partitionEntry->size);
    partitionEntry->attributeFlags = getUint8ArrayUint64(ptr);
    ptr += sizeof(partitionEntry->attributeFlags);
    memcpy(partitionEntry->name, ptr, sizeof(partitionEntry->name));
    ptr += sizeof(partitionEntry->name);
    partitionEntry->crc = getUint8ArrayUint32(ptr);
    ptr += sizeof(partitionEntry->crc);
    if (computedCrc == partitionEntry->crc) {
        return SUCCESS;
    } else {
	printf("expected %08x, read %08x\n", computedCrc, partitionEntry->crc);
        return FAILURE;
    }
}

static bool isBootPartition(partitionEntry_t *partitionEntry) {
    return (0 == memcmp(partitionEntry->type, guidPartitionTypeBoot, sizeof(partitionEntry->type)));
}
static void printPartitionTableHeader(partitionTableHeader_t *partitionTableHeader) {
    printf("%20s:%20s:%04x\n","PT Header","revision",partitionTableHeader->revision);
    printf("%20s:%20s:%04x\n","","first PH address",partitionTableHeader->firstPartitionHeaderAddress);
    printf("%20s:%20s:%04x\n","","PH size",partitionTableHeader->partitionEntrySize);
    printf("%20s:%20s:%04x\n","","PH CRC",partitionTableHeader->crc);
}
static void printPartitionEntry(partitionEntry_t *partitionEntry) {
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
   int i, j;
   unsigned int byte, crc, mask;

   i = 0;
   crc = 0xFFFFFFFF;
   for (i=0; i<byteLength; i++) {
      byte = ptr[i];            // Get next byte.
      crc = crc ^ byte;
      for (j = 7; j >= 0; j--) {    // Do eight times.
         mask = -(crc & 1);
         crc = (crc >> 1) ^ (0xEDB88320 & mask);
      }
   }
   return ~crc;
}

static void createNvram(nvram_t *nvram, int sectorByteSize, int sectorCount, uint8_t eraseValue) {
    int i;

    nvram->sectorByteSize = sectorByteSize;
    nvram->sectorCount = sectorCount;
    nvram->eraseValue = eraseValue;
    nvram->sectorData = (uint8_t**)malloc(sectorCount * sizeof(uint8_t*));
    for (i = 0; i < sectorCount; i++) {
        nvram->sectorData[i] = (uint8_t*)malloc(sectorByteSize * sizeof(uint8_t));
    }
}

static void deleteNvram(nvram_t *nvram) {
    int i;
    for (i = 0; i < nvram->sectorCount; i++) {
        free(nvram->sectorData[i]);
    }
    free(nvram->sectorData);
}

static void readNvram(const nvram_t *nvram, uint32_t address, uint8_t *data, int size) {   
    int sectorIndex = address / nvram->sectorByteSize;
    int offsetInSector = address % nvram->sectorByteSize;
    uint8_t *ptr;
    ptr = data;
    int remainingToRead = size;

    while(remainingToRead > 0) {
        int readInSector = remainingToRead > nvram->sectorByteSize - offsetInSector ? nvram->sectorByteSize - offsetInSector: remainingToRead;
        memcpy(ptr, &(nvram->sectorData[sectorIndex][offsetInSector]), readInSector);
        offsetInSector = 0;
        sectorIndex++;
        ptr += readInSector;
        remainingToRead -= readInSector;
    }
}
static void writeNvram(nvram_t *nvram, uint32_t address, const uint8_t *data, int size) {
    int sectorIndex = address / nvram->sectorByteSize;
    int offsetInSector = address % nvram->sectorByteSize;
    const uint8_t *ptr;
    ptr = data;
    int remainingToWrite = size;

    while(remainingToWrite > 0) {
        int writeInSector = remainingToWrite > nvram->sectorByteSize - offsetInSector ? nvram->sectorByteSize - offsetInSector: remainingToWrite;
        memcpy(&(nvram->sectorData[sectorIndex][offsetInSector]), ptr, writeInSector);
        offsetInSector = 0;
        sectorIndex++;
        ptr += writeInSector;
        remainingToWrite -= writeInSector;
    }
}

static int writeNvramFromFile(nvram_t *nvram, uint32_t address, const char *filePath) {
    FILE *nvramContent = fopen(filePath,"r");
    if (nvramContent == NULL) {
	return FAILURE;
    }

    uint8_t data[nvram->sectorByteSize * nvram->sectorCount];
    memset(data, 0, sizeof(data));

    ssize_t read;
    char *line = (char*)malloc((NUMBER_OF_CHAR_PER_BYTE + 1) * sizeof(char));
    size_t len = 0;
    int byteCount = 0;
    int ptr = 0;
    while ((read = getline(&line, &len, nvramContent)) != -1) {
	/** check if the line is a comment **/
	if (strncmp(line, "//", 2) == 0) {
	    continue;
	}
	
	/** check if it is an address **/
	if (strncmp(line, "@", 1) == 0) {
	    char *strEnd;
	    ptr=strtoul(line+1, &strEnd, 16);
	    printf("Address line detected :: %08x\n", ptr);
	    continue;
	}

	/** remove characters pasted the NUMBER_OF_CHAR_PER_BYTE first characters **/
	line[NUMBER_OF_CHAR_PER_BYTE] = (char)0;
	
	/** convert the line to a number **/
	char *strEnd;
	data[ptr++] = (uint8_t)strtoul(line,&strEnd, 16);
    }
    free(line);
    fclose(nvramContent);
    
    writeNvram(nvram, address, data, sizeof(data));
    return SUCCESS;
}

static void printNvram(nvram_t *nvram) {
    int sectorIndex;
    int byteIndex;
    for (sectorIndex = 0; sectorIndex < nvram->sectorCount; sectorIndex++) {
        printf("[%04x]:",sectorIndex);
        for (byteIndex = 0; byteIndex < nvram->sectorByteSize; byteIndex++) {
            printf("%02x",nvram->sectorData[sectorIndex][byteIndex]);
        }
        printf("\n");
    }
}

static void eraseSectorNvram(nvram_t *nvram, int sectorIndex) {
    int byteIndex;
    for (byteIndex = 0; byteIndex < nvram->sectorByteSize; byteIndex++) {
        nvram->sectorData[sectorIndex][byteIndex] = nvram->eraseValue;
    }
}
