#ifndef KNUDS_UTILITIES_H
#define KNUDS_UTILITIES_H

#include <stdint.h>

int readPrivateKey(const char *string, uint32_t *lPrivate);
int readRandom(const char *string, uint32_t *lRandom);
//int readPublicKey(const char *string, EccPoint *publicKey);
int readSignature(const char *string, uint32_t *r, uint32_t *s);

void printPrivateKey(const uint32_t *lPrivate);
void printSignature(const uint32_t *r, const uint32_t *s);
void printDigest(const uint8_t *digest);
void printRandom(const uint32_t *random);
//void printPublicKey(const EccPoint *publicKey);
int print8BitArray(const char * prefix, const uint8_t *array, int arrayLength);
int sprintf8BitArray(char *output, const uint8_t *array, int arrayLength);

unsigned int countLeadingZeroes(const uint8_t *array, int arrayLength);

void increment8BitArray(uint8_t *array, int arrayLength);

void atobi(uint8_t *array, int arrayLength, const char *string);

#endif
