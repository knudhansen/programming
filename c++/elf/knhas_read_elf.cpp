
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long  uint64;

/* 32-bit types */
typedef uint16 Elf32_Half;
typedef uint32 Elf32_Word;
typedef uint32 Elf32_Addr;
typedef uint32 Elf32_Off;

/* 64-bit types */
typedef uint16 Elf64_Half;
typedef uint32 Elf64_Word;
typedef uint64 Elf64_Xword;
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

typedef enum {
  SHT_SYMTAB = 2,
  SHT_STRTAB = 3
} shType_t;

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
  int getShoff(void);
  int getShstrndx(void);
  elfClass_t getClass(void);
};

class ElfSectionHeader {
private:
  union elfSectionHeader {
    struct elf32Section {
      Elf32_Word sh_name;      // Section name (index into string table)
      Elf32_Word sh_type;      // Section type (SHT_*)
      Elf32_Word sh_flags;     // Section flags (SHF_*)
      Elf32_Addr sh_addr;      // Address where section is to be loaded
      Elf32_Off  sh_offset;    // File offset of section data, in bytes
      Elf32_Word sh_size;      // Size of section, in bytes
      Elf32_Word sh_link;      // Section type-specific header table index link
      Elf32_Word sh_info;      // Section type-specific extra information
      Elf32_Word sh_addralign; // Section address alignment
      Elf32_Word sh_entsize;   // Size of records contained within the section
    } elf32;
    struct elf64Section {
      Elf64_Word  sh_name;
      Elf64_Word  sh_type;
      Elf64_Xword sh_flags;
      Elf64_Addr  sh_addr;
      Elf64_Off   sh_offset;
      Elf64_Xword sh_size;
      Elf64_Word  sh_link;
      Elf64_Word  sh_info;
      Elf64_Xword sh_addralign;
      Elf64_Xword sh_entsize;
    } elf64;
  } elfSectionHeader;
  ElfHeader *elfHeader;
public:
  ElfSectionHeader(void);
  void constructFromFile(FILE* file, ElfHeader* elfHeader);
  shType_t getShtype(void);
  long getShoffset(void);
  long getShsize(void);
  int getShname(void);
  elfClass_t getElfClass(void);
  void print(void);
};

class ElfSection {
private:
  ElfSectionHeader *elfSectionHeader;
  char *name;
public:
  ElfSection(ElfSectionHeader* elfSectionHeader, char* sectionNameStringTable);
  void constructFromFile(FILE* file);
  char* getName(void);
  long getShoffset(void);
  long getShsize(void);
  void print(void);
};

class ElfSymbol {
private:
  typedef struct elf32SymbolTableEntry {
    Elf32_Word    st_name;
    Elf32_Addr    st_value;
    Elf32_Word    st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf32_Half    st_shndx;
  } elf32SymbolTableEntry_t;
  typedef struct elf64SymbolTableEntry {
    Elf64_Word    st_name;
    unsigned char st_info;
    unsigned char st_other;
    Elf64_Half    st_shndx;
    Elf64_Addr    st_value;
    Elf64_Xword   st_size;
  } elf64SymbolTableEntry_t;
  union elfSymbolTableEntry {
    elf32SymbolTableEntry_t elf32;
    elf64SymbolTableEntry_t elf64;
  } elfSymbolTableEntry;
  ElfSectionHeader *elfSectionHeader;
  char *name;
public:
  ElfSymbol(ElfSectionHeader* elfSectionHeader);
  static size_t getSymbolTableEntrySize(elfClass_t elfClass);
  void constructFromFile(FILE* file, char* stringTable);
  void print(void);
};

int main() {
  
  FILE *elfFile;
  elfFile = fopen("test2.o","r");
  
  // read elf header
  ElfHeader *elfHeader = new ElfHeader();
  elfHeader->constructFromFile(elfFile);
  elfHeader->print();
  
  ElfSectionHeader *nameStringTableSectionHeader = NULL;
  ElfSectionHeader *symbolTableSectionHeader = NULL;

  ElfSymbol **symbolTable = NULL;

  // read elf section headers and finding symbole table section header
  ElfSectionHeader **elfSectionHeaders = (ElfSectionHeader**)malloc(sizeof(ElfSectionHeader*) * elfHeader->getShnum());
  fseek(elfFile, elfHeader->getShoff(), SEEK_SET);
  for (int shNdx = 0; shNdx < elfHeader->getShnum(); shNdx++) {
    printf("constructing section header %2d >>> ", shNdx);
    elfSectionHeaders[shNdx] = new ElfSectionHeader();
    elfSectionHeaders[shNdx]->constructFromFile(elfFile, elfHeader);
    if (elfSectionHeaders[shNdx]->getShtype() == SHT_SYMTAB) {
      symbolTableSectionHeader = elfSectionHeaders[shNdx];
    }
    elfSectionHeaders[shNdx]->print();
  }

  // reading the section name string table
  nameStringTableSectionHeader = elfSectionHeaders[elfHeader->getShstrndx()];
  fseek(elfFile, nameStringTableSectionHeader->getShoffset(), SEEK_SET);
  char* sectionNameStringTable = (char*)malloc(nameStringTableSectionHeader->getShsize() * sizeof(char));
  fread(sectionNameStringTable, sizeof(char), nameStringTableSectionHeader->getShsize(), elfFile);

  // creating sections
  ElfSection **elfSections = (ElfSection**)malloc(sizeof(ElfSection*) * elfHeader->getShnum());
  for (int shNdx = 0; shNdx < elfHeader->getShnum(); shNdx++) {
    elfSections[shNdx] = new ElfSection(elfSectionHeaders[shNdx], sectionNameStringTable);
    printf("%3d >>> ", shNdx);
    elfSections[shNdx]->print();
  }

  
  // reading the string table
  char *stringTable = NULL;
  for (int sNdx=0; sNdx < elfHeader->getShnum(); sNdx++) {
    if (strcmp(elfSections[sNdx]->getName(), ".strtab") == 0) {
      printf("found section header of string table: %d\n", sNdx);
      fseek(elfFile, elfSections[sNdx]->getShoffset(), SEEK_SET);
      stringTable = (char*)malloc(elfSections[sNdx]->getShsize() * sizeof(char));
      fread(stringTable, sizeof(char), elfSections[sNdx]->getShsize(), elfFile);
    }
  }

  // reading symbol table
  int numberOfSymbols = symbolTableSectionHeader->getShsize()/ElfSymbol::getSymbolTableEntrySize(elfHeader->getClass());
  printf("There are %d symbols in the symbol table\n", numberOfSymbols);

  symbolTable = (ElfSymbol**)malloc(numberOfSymbols * sizeof(ElfSymbol*));
  fseek(elfFile, symbolTableSectionHeader->getShoffset(), SEEK_SET);
  for (int i = 0; i < numberOfSymbols; i++) {
    symbolTable[i] = new ElfSymbol(symbolTableSectionHeader);
    symbolTable[i]->constructFromFile(elfFile, stringTable);
    symbolTable[i]->print();
  }

  fclose(elfFile);
}

ElfHeader::ElfHeader(void) {
  printf("constructing header\n");
  this->elfIdentity = new ElfIdentity();
}

void ElfHeader::constructFromFile(FILE *file) {
  printf("constructing header from file\n");
  this->elfIdentity->constructFromFile(file);
  fread(&(this->e_type), sizeof(e_type), 1, file);
  fread(&(this->e_machine), sizeof(e_machine), 1, file);
  fread(&(this->e_version), sizeof(e_version), 1, file);
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
    fread(&(this->elfheader2.elf32), 1, sizeof(this->elfheader2.elf32), file);
    break;
  case ELFCLASS64:
    printf("class 64\n");
    fread(&(this->elfheader2.elf64), 1, sizeof(this->elfheader2.elf64), file);
    break;
  default:
    printf("constructFromFile unknown class -- %d\n", this->elfIdentity->getClass());
  }
}

int ElfHeader::getShnum(void) {
  switch (this->elfIdentity->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return this->elfheader2.elf32.e_shnum;
  case ELFCLASS64:
    return this->elfheader2.elf64.e_shnum;
  default:
    printf("unknown class\n");
    break;
  }
  return -1;
}
int ElfHeader::getShoff(void) {
  switch (this->elfIdentity->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return this->elfheader2.elf32.e_shoff;
  case ELFCLASS64:
    return this->elfheader2.elf64.e_shoff;
  default:
    printf("unknown class\n");
    break;
  }
  return -1;
}

int ElfHeader::getShstrndx(void) {
  switch (this->elfIdentity->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return this->elfheader2.elf32.e_shstrndx;
  case ELFCLASS64:
    return this->elfheader2.elf64.e_shstrndx;
  default:
    printf("unknown class\n");
    break;
  }
  return -1;  
}

void ElfHeader::print(void) {
  this->elfIdentity->print();
  printf("e_type: %d\n", this->e_type);
  printf("e_machine: %d\n", this->e_machine);
  printf("e_version: %d\n", this->e_version);
  printf("e_shnum: %d\n", this->getShnum());
}

int ElfHeader::getByteSize(void) {
  int size = 0;
  size += this->elfIdentity->getByteSize();
  return size;
}

elfClass_t ElfHeader::getClass(void) {
  return this->elfIdentity->getClass();
}

ElfIdentity::ElfIdentity(void) {
  printf("constructing identity\n");
  this->eclass = ELFCLASSNONE;
  this->edata = ELFDATANONE;
  memset(this->mag, 0, sizeof(this->mag));
}

void ElfIdentity::constructFromFile(FILE *file) {
  printf("constructing identity from file\n");
  fread(this->mag, 1, ELF_IDENTITY_MAG_SIZE, file);
  fread(&(this->eclass), 1, 1, file);
  fread(&(this->edata), 1, 1, file);
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

ElfSectionHeader::ElfSectionHeader(void) {
  memset(&(this->elfSectionHeader), 0, sizeof(this->elfSectionHeader));
}

void ElfSectionHeader::constructFromFile(FILE* file, ElfHeader* elfHeader) {
  this->elfHeader = elfHeader;
  switch (this->elfHeader->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    fread(&(this->elfSectionHeader.elf32), 1, sizeof(this->elfSectionHeader.elf32), file);
    break;
  case ELFCLASS64:
    fread(&(this->elfSectionHeader.elf64), 1, sizeof(this->elfSectionHeader.elf64), file);
    break;
  default:
    printf("constructFromFile unknown class -- %d\n", elfHeader->getClass());
  }
}

shType_t ElfSectionHeader::getShtype(void) {
  switch (this->elfHeader->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return (shType_t)this->elfSectionHeader.elf32.sh_type;
  case ELFCLASS64:
    return (shType_t)this->elfSectionHeader.elf64.sh_type;
  default:
    printf("unknown class -- %d\n", this->elfHeader->getClass());
  }
  return (shType_t)0;
}

long ElfSectionHeader::getShoffset(void) {
  switch (this->elfHeader->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return this->elfSectionHeader.elf32.sh_offset;
  case ELFCLASS64:
    return this->elfSectionHeader.elf64.sh_offset;
  default:
    printf("unknown class -- %d\n", this->elfHeader->getClass());
  }
  return 0;
}
 
long ElfSectionHeader::getShsize(void) {
  switch (this->elfHeader->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return this->elfSectionHeader.elf32.sh_size;
  case ELFCLASS64:
    return this->elfSectionHeader.elf64.sh_size;
  default:
    printf("unknown class -- %d\n", this->elfHeader->getClass());
  }
  return 0;
}

int ElfSectionHeader::getShname(void) {
  switch (this->elfHeader->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return this->elfSectionHeader.elf32.sh_name;
  case ELFCLASS64:
    return this->elfSectionHeader.elf64.sh_name;
  default:
    printf("unknown class -- %d\n", this->elfHeader->getClass());
  }
  return 0;
}

elfClass_t ElfSectionHeader::getElfClass(void) {
  return this->elfHeader->getClass();
}

void ElfSectionHeader::print(void) {
  switch (this->elfHeader->getClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    printf("sh_name: %4d - sh_type: %4d - sh_addr: %4d - sh_offset: %4d - sh_size: %4d - sh_addralign: %4d\n",
	   this->elfSectionHeader.elf32.sh_name,
	   this->elfSectionHeader.elf32.sh_type,
	   this->elfSectionHeader.elf32.sh_addr,
	   this->elfSectionHeader.elf32.sh_offset,
	   this->elfSectionHeader.elf32.sh_size,
	   this->elfSectionHeader.elf32.sh_addralign
	   );
    break;
  case ELFCLASS64:
    printf("sh_name: %4d - sh_type: %4d - sh_addr: %4ld - sh_offset: %4ld - sh_size: %4ld - sh_addralign: %4ld\n",
	   this->elfSectionHeader.elf64.sh_name,
	   this->elfSectionHeader.elf64.sh_type,
	   this->elfSectionHeader.elf64.sh_addr,
	   this->elfSectionHeader.elf64.sh_offset,
	   this->elfSectionHeader.elf64.sh_size,
	   this->elfSectionHeader.elf64.sh_addralign
	   );
    break;
  default:
    printf("constructFromFile unknown class -- %d\n", this->elfHeader->getClass());
  }  
}

ElfSection::ElfSection(ElfSectionHeader* elfSectionHeader, char* sectionNameStringTable) {
  this->elfSectionHeader = elfSectionHeader;
  this->name = &(sectionNameStringTable[this->elfSectionHeader->getShname()]);
}

void ElfSection::constructFromFile(FILE* file) {
}

char* ElfSection::getName(void) {
  return this->name;
}

long ElfSection::getShoffset(void) {
  return this->elfSectionHeader->getShoffset();
}

long ElfSection::getShsize(void) {
  return this->elfSectionHeader->getShsize();
}

void ElfSection::print(void) {
  printf("section -- name:%s\n", this->name);
}

ElfSymbol::ElfSymbol(ElfSectionHeader* elfSectionHeader) {
  this->elfSectionHeader = elfSectionHeader;
  this->name = NULL;
}

size_t ElfSymbol::getSymbolTableEntrySize(elfClass_t elfClass) {
  switch (elfClass) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    return sizeof(ElfSymbol::elf32SymbolTableEntry_t);
    break;
  case ELFCLASS64:
    return sizeof(ElfSymbol::elf64SymbolTableEntry_t);
    break;
  default:
    printf("constructFromFile unknown class -- %d\n", elfClass);
  }
  return 0;
}

void ElfSymbol::constructFromFile(FILE* file, char* stringTable) {
  switch (this->elfSectionHeader->getElfClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    fread(&(this->elfSymbolTableEntry.elf32), 1, sizeof(this->elfSymbolTableEntry.elf32), file);
    this->name = &(stringTable[this->elfSymbolTableEntry.elf32.st_name]);
    break;
  case ELFCLASS64:
    fread(&(this->elfSymbolTableEntry.elf64), 1, sizeof(this->elfSymbolTableEntry.elf64), file);
    this->name = &(stringTable[this->elfSymbolTableEntry.elf64.st_name]);
    break;
  default:
    printf("constructFromFile unknown class -- %d\n", this->elfSectionHeader->getElfClass());
  }
}

void ElfSymbol::print(void) {
  switch (this->elfSectionHeader->getElfClass()) {
  case ELFCLASSNONE:
    printf("class none illegal\n");
    break;
  case ELFCLASS32:
    printf("Symbol>> name: %s(%d) -- type: %d\n", this->name, this->elfSymbolTableEntry.elf32.st_name, this->elfSymbolTableEntry.elf32.st_info & 0xf);
    break;
  case ELFCLASS64:
    printf("Symbol>> name: %s(%d) -- type: %d\n", this->name, this->elfSymbolTableEntry.elf64.st_name, this->elfSymbolTableEntry.elf64.st_info & 0xf);
    break;
  default:
    printf("constructFromFile unknown class -- %d\n", this->elfSectionHeader->getElfClass());
  }
}
