#include <map>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/** FS under test **/

int fileHandleCounter = 0;

typedef struct {
  int fileId;
} FS_FILE;

int FS_FOpenEx(const char *fileName, const char *openMode, FS_FILE **ppFile) {
  *ppFile = (FS_FILE*)malloc(sizeof(FS_FILE));
  (*ppFile)->fileId = fileHandleCounter++;
  printf("opening file %s with mode %s. File handle id is %d\n", fileName, openMode, (*ppFile)->fileId);
  return 0;
}
int FS_FClose(FS_FILE *pFile) {
  free(pFile);
  return 0;
}
int FS_Read(FS_FILE *pFile, char *data, int data_size) {
  return data_size;
}
int FS_Write(FS_FILE *pFile, const char *data, int data_size) {
  return data_size;
}

/** FS reference model **/

const char fsrefDir[] = "ref";
std::map<FS_FILE*,FILE*> file_handles_map;

FILE *_getRefFileHandle(FS_FILE *pFile, bool erase) {
  FILE *rv = NULL;
  std::map<FS_FILE*,FILE*>::iterator it = file_handles_map.find(pFile);
  if (it != file_handles_map.end()) {
    rv = it->second; 
  }
  if (erase) {
    file_handles_map.erase(it);
  }
  return rv;
}

FILE *popRefFileHandle(FS_FILE *pFile) {
  return _getRefFileHandle(pFile, true);
}
FILE *getRefFileHandle(FS_FILE *pFile) {
  return _getRefFileHandle(pFile, false);
}

int fsrefOpen(const char *fileName, const char *openMode, FS_FILE **ppFile) {
  char *refFileName = (char*)malloc(strlen(fsrefDir) + 1 + strlen(fileName) + 1);
  sprintf(refFileName, "%s/%s", fsrefDir, fileName);
  printf("opening file %s (%s).\n", fileName, refFileName);

  FILE *f = fopen(refFileName, openMode);

  file_handles_map.insert(std::make_pair(*ppFile, f));

  if (f != NULL) {
    return 0;
  } else {
    return -1;
  }
}

int fsrefClose(FS_FILE *pFile) {
  FILE *f = popRefFileHandle(pFile);
  if (f == NULL) {
    return -1;
  }
  return fclose(f);
}

int fsrefRead(FS_FILE *pFile, char *data, int data_size) {
  FILE *f = getRefFileHandle(pFile);
  if (f == NULL) {
    return 0;
  }
  return fread(data, 1, data_size, f);
}
int fsrefWrite(FS_FILE *pFile, const char *data, int data_size) {
  FILE *f = getRefFileHandle(pFile);
  if (f == NULL) {
    return 0;
  }
  return fwrite(data, 1, data_size, f);
}

/** testbench **/

static char* toString(int value) {  
  char *string = (char*)malloc(log10(value)+1+1);
  sprintf(string, "%d", value);
  return string;
}
static void freeString(char* string) {
  free(string);
}

template<typename T>
void fstestAssertEqual(const char *functionName, const char *valueName, T futValue, T refValue) {
  const char assertEqualFailMessage[] = "ASSERT EQUAL FAILURE::";
  if (futValue != refValue) {
    char *futValueStr = toString(futValue);
    char *refValueStr = toString(refValue);
    char *exceptionMessage = (char*)malloc(strlen(assertEqualFailMessage) + 1 + strlen(functionName) + 1 + strlen(valueName) + 1 + strlen(futValueStr) + 2 + strlen(refValueStr) + 1);
    sprintf(exceptionMessage, "%s %s.%s %s!=%s", assertEqualFailMessage, functionName, valueName, futValueStr, refValueStr); 
    freeString(futValueStr);
    freeString(refValueStr);
    throw std::runtime_error(exceptionMessage);
  }
}

int fstestOpen(const char *fileName, const char *openMode, FS_FILE **ppFile) {
  int rvfut = FS_FOpenEx(fileName, openMode, ppFile);
  int rvref = fsrefOpen(fileName, openMode, ppFile);
  fstestAssertEqual("fstestOpen", "returnValue", rvfut, rvref);
  return rvfut;
}

int fstestClose(FS_FILE *pFile) {
  int rvfut = FS_FClose(pFile);
  int rvref = fsrefClose(pFile);
  fstestAssertEqual("fstestClose", "returnValue", rvfut, rvref);
  return rvfut;
}

int fstestRead(FS_FILE *pFile, char *data, int data_size) {
  int rvfut = FS_Read(pFile, data, data_size);
  int rvref = fsrefRead(pFile, data, data_size);
  fstestAssertEqual("fstestRead", "returnValue", rvfut, rvref);
  return rvfut;
}
int fstestWrite(FS_FILE *pFile, const char *data, int data_size) {
  int rvfut = FS_Write(pFile, data, data_size);
  int rvref = fsrefWrite(pFile, data, data_size);
  fstestAssertEqual("fstestWrite", "returnValue", rvfut, rvref);
  return rvfut;
}

int main(int argc, char *argv[]) {
  FS_FILE *file0;
  try {
    fstestOpen("file0.txt", "w", &file0);
    fstestWrite(file0, "abcd", 4);
    fstestClose(file0);
  } catch (const std::exception &exception) {
    printf("CAUGHT EXCEPTION: %s\n", exception.what());
  }
  return 0;
}
