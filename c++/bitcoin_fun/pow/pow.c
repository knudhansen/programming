#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tinycrypt/sha256.h"

#include "utilities.h"

int main(int argc, char *argv[]) {

  struct tc_sha256_state_struct sha256State;
  uint8_t shaData[TC_SHA256_DIGEST_SIZE];
  uint8_t shaDigest[TC_SHA256_DIGEST_SIZE];

  memset(shaData, 0, sizeof(shaData));

  int difficulty = atoi(argv[1]);
  int score = 0;

  if (argc > 2) {
    atobi(shaData, sizeof(shaData), argv[2]);
  }

  int attemptCount = 0;
  int highScore = 0;

  char *shaDataString = (char*)malloc(sizeof(shaData)*2+1);

  while (score < difficulty) {
    tc_sha256_init(&sha256State);
    tc_sha256_update(&sha256State,
		     shaData,
		     sizeof(shaData));
    tc_sha256_final(shaDigest, &sha256State);
    
    score = countLeadingZeroes(shaDigest, TC_SHA256_DIGEST_SIZE);
    if (score > highScore) {
      highScore = score;
    }
    sprintf8BitArray(shaDataString, shaData, sizeof(shaData));
    printf("%s -- %4d -- leading 0's: %d\n", shaDataString, highScore, score);

    increment8BitArray(shaData, sizeof(shaData));
  }

  free(shaDataString);

  printDigest(shaDigest);
}

