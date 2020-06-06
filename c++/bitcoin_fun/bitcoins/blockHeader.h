#ifndef __BLOCKHEADER_H__
#define __BLOCKHEADER_H__

#include <cstdint>

#define BLOCKHEADER_HASH_BYTE_SIZE 32
#define BLOCKHEADER_SERIALIZED_BYTE_SIZE 80

class BlockHeader {

 private:
  int32_t blockVersion;
  char previousBlockHeaderHash[BLOCKHEADER_HASH_BYTE_SIZE];
  char merkelRootHash[BLOCKHEADER_HASH_BYTE_SIZE];
  uint32_t time;
  uint32_t nBits;
  uint32_t nonce;

 public:
  BlockHeader(int32_t blockVersion, const char *previousBlockHeaderHash, uint32_t nBits);
  ~BlockHeader(void);

  void setMerkelRootHash(const char *merkelRootHash);
  void setNonce(uint32_t nonce);
  void updateTime(void);

  void serialize(char serializedBlokHeader[BLOCKHEADER_SERIALIZED_BYTE_SIZE]);

};

#endif
