#include "utilities.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

static int read32BitArrayFromString(const char *string, uint32_t *destination, int wordSize);
static int print32BitArray(const char * prefix, const uint32_t *array, int arrayLength);
static int countLeadingZeroBits(uint8_t value, uint8_t mask);

/******* needs updating after changing from tinycrypt to mbedtls *******/
/*
int readPrivateKey(const char *string, uint32_t *lPrivate) {
    return read32BitArrayFromString(string, lPrivate, NUM_ECC_DIGITS);
}

int readRandom(const char *string, uint32_t *lRandom) {
    return read32BitArrayFromString(string, lRandom, NUM_ECC_DIGITS * 2);
}

int readPublicKey(const char *string, EccPoint *publicKey) {
    int xStatus = read32BitArrayFromString(string, publicKey->x, NUM_ECC_DIGITS);
    int yStatus = read32BitArrayFromString(string+NUM_ECC_DIGITS, publicKey->y, NUM_ECC_DIGITS);
    return xStatus | yStatus;
} 

int readSignature(const char *string, uint32_t *r, uint32_t *s) {
    int rStatus = read32BitArrayFromString(string, r, NUM_ECC_DIGITS);
    int sStatus = read32BitArrayFromString(string+NUM_ECC_DIGITS, s, NUM_ECC_DIGITS);
    return rStatus | sStatus;
}

void printPrivateKey(const uint32_t *lPrivate) {
    print32BitArray("private key", lPrivate, NUM_ECC_DIGITS);
}

void printSignature(const uint32_t *r, const uint32_t *s) {
    print32BitArray("signature.r", r, NUM_ECC_DIGITS);
    print32BitArray("signature.s", s, NUM_ECC_DIGITS);
}
*/
void printDigest(const uint8_t *digest) {
    print8BitArray("sha256 digest", digest, 64);
}

/*
void printRandom(const uint32_t *random) {
    print32BitArray("random", random, NUM_ECC_DIGITS * 2);
}

void printPublicKey(const EccPoint *publicKey) {
    print32BitArray("publicKey.x", publicKey->x, NUM_ECC_DIGITS);
    print32BitArray("publicKey.y", publicKey->y, NUM_ECC_DIGITS);
}
*/
static int read32BitArrayFromString(const char *string, uint32_t *destination, int wordSize) {
    int i;
    for (i=0; i<wordSize; i++) {
        char wordString[9];
        memset(wordString,0,sizeof(wordString));
        strncpy(wordString,string+8*i,8);
        destination[i] = strtoul(wordString, 0, 16);
    }
    return 0;
}

static int print32BitArray(const char * prefix, const uint32_t *array, int arrayLength) {
    int i;
    printf("%s: 0x", prefix);
    for (i=0; i<arrayLength; i++) {
        printf("%08x", array[i]);
    }
    printf("\n");
    return 0;
}

int print8BitArray(const char * prefix, const uint8_t *array, int arrayLength) {
  char *arrayString = (char*)malloc(arrayLength*2+1);
  sprintf8BitArray(arrayString, array, arrayLength);
  printf("%s: %s\n",prefix,arrayString);
  free(arrayString);
  return 0;
}

int sprintf8BitArray(char *output, const uint8_t *array, int arrayLength) {
  if (arrayLength > 0) {
    sprintf(output, "%02x", *array);
    output[2] = 0;
    sprintf8BitArray(output+2, array+1, arrayLength-1);
  }
  return 0;
}

unsigned int countLeadingZeroes(const uint8_t *array, int arrayLength) {
  if (arrayLength == 0) {
    return 0;
  } else if (arrayLength != 0 && (*array) == 0) {
    return countLeadingZeroes(array + 1, arrayLength - 1) + 8;
  } else {
    return countLeadingZeroBits(*array, 0x80);
  }
}

static int countLeadingZeroBits(uint8_t value, uint8_t mask) {
  if (mask == 0 || (value & mask) != 0) {
    return 0;
  } else {
    return countLeadingZeroBits(value, mask >> 1) + 1;
  }
}

void increment8BitArray(uint8_t *array, int arrayLength) {
  if (arrayLength != 0) {
    array[arrayLength-1]++;
    if (array[arrayLength-1] == 0) {
      increment8BitArray(array, arrayLength - 1);
    }
  }
}

void atobi(uint8_t *array, int arrayLength, const char *string) {
  char byteString[3];
  byteString[2] = 0;
  int i = 1;
  while (i < arrayLength && 2*i <= strlen(string)) {
    strncpy(byteString, string+strlen(string)-2*i, 2);
    array[arrayLength - i] = (uint8_t)strtoul(byteString, 0, 16);
    i++;
  }
}
