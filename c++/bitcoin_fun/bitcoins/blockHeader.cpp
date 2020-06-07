#include "blockHeader.h"

#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BlockHeader::BlockHeader(int32_t blockVersion, const char *previousBlockHeaderHash, uint32_t nBits) {

  this->blockVersion = blockVersion;
  memcpy(this->previousBlockHeaderHash, previousBlockHeaderHash, BLOCKHEADER_HASH_BYTE_SIZE);
  memset(this->merkelRootHash, 0, BLOCKHEADER_HASH_BYTE_SIZE);
  this->nBits = nBits;

  this->nonce = 0;

}

void BlockHeader::setMerkelRootHash(const char *merkelRootHash) {
  memcpy(this->merkelRootHash, merkelRootHash, BLOCKHEADER_HASH_BYTE_SIZE);
}
void BlockHeader::setNonce(uint32_t nonce) {
  this->nonce = nonce;
}
void BlockHeader::updateTime(void) {
  // get the current time
  const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
  // cast the duration into seconds
  const std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());

  // return the number of seconds
  this->time = seconds.count();
  printf("seconds since epoch %08x\n", this->time);
}

char *BlockHeader::toString(void) {
  char *retString = (char*)malloc(100 * sizeof(char));
  sprintf(retString, "time=%08x, nBits=%08x, nonce=%08x", this->time, this->nBits, this->nonce);
  return retString;
}

void BlockHeader::serialize(unsigned char serializedBlockHeader[BLOCKHEADER_SERIALIZED_BYTE_SIZE]) {
  // serializing version
  serializedBlockHeader[0] = (this->blockVersion >>  0) & 0xff;
  serializedBlockHeader[1] = (this->blockVersion >>  8) & 0xff;
  serializedBlockHeader[2] = (this->blockVersion >> 16) & 0xff;
  serializedBlockHeader[3] = (this->blockVersion >> 24) & 0xff;
  // previous block hash
  memcpy(&(serializedBlockHeader[4]), this->previousBlockHeaderHash, BLOCKHEADER_HASH_BYTE_SIZE);
  // merkel root hash
  memcpy(&(serializedBlockHeader[4 + BLOCKHEADER_HASH_BYTE_SIZE]), this->merkelRootHash, BLOCKHEADER_HASH_BYTE_SIZE);
  // time
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 0 + 0] = (this->time >>  0) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 0 + 1] = (this->time >>  8) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 0 + 2] = (this->time >> 16) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 0 + 3] = (this->time >> 24) & 0xff;
  // nBits
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 4 + 0] = (this->nBits >>  0) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 4 + 1] = (this->nBits >>  8) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 4 + 2] = (this->nBits >> 16) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 4 + 3] = (this->nBits >> 24) & 0xff;
  // nonce
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 8 + 0] = (this->nonce >>  0) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 8 + 1] = (this->nonce >>  8) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 8 + 2] = (this->nonce >> 16) & 0xff;
  serializedBlockHeader[4 + 2 * BLOCKHEADER_HASH_BYTE_SIZE + 8 + 3] = (this->nonce >> 24) & 0xff;
}
