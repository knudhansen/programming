#include "blockHeader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  BlockHeader *blockHeader = new BlockHeader(1, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 1);
  blockHeader->updateTime();

  char *blockHeaderString = blockHeader->toString();
  printf("blockHeader: %s\n", blockHeaderString);
  free(blockHeaderString);

  unsigned char serializedBlockHeader[BLOCKHEADER_SERIALIZED_BYTE_SIZE];
  memset(serializedBlockHeader, 0, sizeof(serializedBlockHeader));

  blockHeader->serialize(serializedBlockHeader);

  printf("seralizedBlock: ");
  for (int i = 0; i < BLOCKHEADER_SERIALIZED_BYTE_SIZE; i++) {
    printf("%02x", serializedBlockHeader[i]);
  }
  printf("\n");

}
