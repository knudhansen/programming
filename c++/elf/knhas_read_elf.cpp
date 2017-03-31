//class ElfIdentity {
//    ElfIdentityClass identityClass;
//    ElfIdentityData identityData;
//    ElfIdentityVersion identityVersion;
//};
//
//class ElfHeader {
//    ElfIdentity *identity;
//    ElfType type;
//    ElfMachine machine;
//    ElfVersion version;
//    ElfEntry entry;
//    ElfPHOffset pHOffset;
//    ElfSHOffset sHOffset;
//    ElfFlags flags;
//    ElfHeaderSize headerSize;
//    ElfProgramHeaderEntrySize programHeaderEntrySize;
//    ElfProgramHeaderNumber programHeaderNumber;
//    ElfSectionHeaderEntrySize sectionHeaderEntrySize;
//    ElfSectionHeaderNumber sectionHeaderNumber;
//    ElfSectionHeaderStringIndex sectionHeaderStringIndex;
//};
//
//class ElfFile {
//    ElfHeader *header;
//    ElfProgramHeaderTable *programHeaderTable;
//    ElfSectionHeaderTable *sectionHeaderTable;
//    ElfSections **sections;
//    ElfSegments **segments;
//};

#include <stdio.h>
#include <string.h>

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long  uint64;

typedef uint16 Elf32_Half;
typedef uint32 Elf32_Word;
typedef uint32 Elf32_Addr;
typedef uint32 Elf32_Off;
typedef uint16 Elf64_Half;
typedef uint32 Elf64_Word;
typedef uint64 Elf64_Addr;
typedef uint64 Elf64_Off;

#define ELF_IDENTITY_MAG_SIZE 4


typedef enum {
    ELFCLASSNONE = 0,
    ELFCLASS32 = 1, // 32-bit object file
    ELFCLASS64 = 2  // 64-bit object file
} elfClass_t;

// Object file byte orderings.
typedef enum {
  ELFDATANONE = 0, // Invalid data encoding.
  ELFDATA2LSB = 1, // Little-endian object file
  ELFDATA2MSB = 2  // Big-endian object file
} elfData_t;

class ElfIdentity {
private:
    char mag[ELF_IDENTITY_MAG_SIZE];
    elfClass_t eclass;
    elfData_t edata;
public:
    ElfIdentity(void);
    void constructFromFile(FILE *file);
    void print(void);
    elfClass_t getClass(void);
    elfData_t getData(void);
    int getByteSize(void);
};

class ElfHeader {
private:
    ElfIdentity *elfIdentity;
    uint16 e_type;
    uint16 e_machine;
    uint32 e_version;
    union elfHeader {
        struct elf32Header {
            Elf32_Addr    e_entry;     // Address to jump to in order to start program
            Elf32_Off     e_phoff;     // Program header table's file offset, in bytes
            Elf32_Off     e_shoff;     // Section header table's file offset, in bytes
            Elf32_Word    e_flags;     // Processor-specific flags
            Elf32_Half    e_ehsize;    // Size of ELF header, in bytes
            Elf32_Half    e_phentsize; // Size of an entry in the program header table
            Elf32_Half    e_phnum;     // Number of entries in the program header table
            Elf32_Half    e_shentsize; // Size of an entry in the section header table
            Elf32_Half    e_shnum;     // Number of entries in the section header table
            Elf32_Half    e_shstrndx;  // Sect hdr table index of sect name string table
        } elf32;
        struct elf64Header {
            Elf64_Addr    e_entry;
            Elf64_Off     e_phoff;
            Elf64_Off     e_shoff;
            Elf64_Word    e_flags;
            Elf64_Half    e_ehsize;
            Elf64_Half    e_phentsize;
            Elf64_Half    e_phnum;
            Elf64_Half    e_shentsize;
            Elf64_Half    e_shnum;
            Elf64_Half    e_shstrndx;
        } elf64;
    } elfheader2;

public:
    ElfHeader(void);
    void constructFromFile(FILE *file);
    void print(void);
    int getByteSize(void);
    int getShnum(void);
};

int main() {

    FILE *elfFile;
    elfFile = fopen("test.o","r");

    ElfHeader *elfHeader = new ElfHeader();
    elfHeader->constructFromFile(elfFile);
    
    elfHeader->print();
//    printf("start file\n");
//    while (lastByte != EOF) {
//        printf("%02x\n", lastByte);
//        fread(&lastByte, 1, 1, elfFile);
//    }
//    printf("end file\n");

    fclose(elfFile);

}

ElfHeader::ElfHeader(void) {
    printf("constructing header\n");
    this->elfIdentity = new ElfIdentity();
}

void ElfHeader::constructFromFile(FILE *file) {
    printf("constructing header from file\n");
    this->elfIdentity->constructFromFile(file);
    fread(&this->e_type, sizeof(e_type), 1, file);
    fread(&this->e_machine, sizeof(e_machine), 1, file);
    fread(&this->e_version, sizeof(e_version), 1, file);
    if (this->elfIdentity->getData() != ELFDATA2LSB) {
        printf("error:: only LSD class supported for now.\n");
        return;
    }
    switch (this->elfIdentity->getClass()) {
    case ELFCLASSNONE:
        printf("class none illegal\n");
        break;
    case ELFCLASS32:
        printf("class 32\n");
        fread(&this->elfheader2.elf32, 1, sizeof(this->elfheader2.elf32), file);
        break;
    case ELFCLASS64:
        printf("class 64\n");
        fread(&this->elfheader2.elf64, 1, sizeof(this->elfheader2.elf64), file);
        break;
    default:
        printf("unknown class\n");
    }
}

int ElfHeader::getShnum(void) {
    switch (this->elfIdentity->getClass()) {
    case ELFCLASSNONE:
        printf("class none illegal\n");
        return -1;
    case ELFCLASS32:
        printf("class 32\n");
        return this->elfheader2.elf32.e_shnum;
    case ELFCLASS64:
        printf("class 64\n");
        return this->elfheader2.elf64.e_shnum;
        break;
    default:
        printf("unknown class\n");
        return -1;
    }
}

void ElfHeader::print(void) {
    this->elfIdentity->print();
    printf("e_type: %d\n", this->e_type);
    printf("e_machine: %d\n", this->e_machine);
    printf("e_version: %d\n", this->e_version);
    printf("e_shentsize: %d\n", this->getShnum());
}

int ElfHeader::getByteSize(void) {
    int size = 0;
    size += this->elfIdentity->getByteSize();
}

ElfIdentity::ElfIdentity(void) {
    printf("constructing identity\n");
}

void ElfIdentity::constructFromFile(FILE *file) {
    printf("constructing identity from file\n");
    fread(this->mag, 1, ELF_IDENTITY_MAG_SIZE, file);
    fread(&this->eclass, 1, 1, file);
    fread(&this->edata, 1, 1, file);
    fseek(file, 10, SEEK_CUR);
}

void ElfIdentity::print(void) {
    char magString[ELF_IDENTITY_MAG_SIZE+1];
    memset(magString, 0, sizeof(magString));
    strncpy(magString, this->mag, ELF_IDENTITY_MAG_SIZE);
    printf("MAG: %x-%s\n", magString[0], &(magString[1]));
}

int ElfIdentity::getByteSize(void) {
    return 16;
}

elfClass_t ElfIdentity::getClass(void) {
    return this->eclass;
}

elfData_t ElfIdentity::getData(void) {
    return this->edata;
}
