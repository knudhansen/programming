#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tinycrypt/sha256.h"

#include "utilities.h"

int main(int argc, char *argv[]) {

  struct tc_sha256_state_struct sha256State;
  uint8_t shaData[TC_SHA256_DIGEST_SIZE];
  uint8_t shaDigest[TC_SHA256_DIGEST_SIZE];

  uint32_t histogram[256];

  memset(histogram, 0, sizeof(histogram));
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
    histogram[score]++;
    if (score > highScore) {
      highScore = score;
    }
    sprintf8BitArray(shaDataString, shaData, sizeof(shaData));
    printf("%s -- %4d -- %04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x.%04x -- leading 0's: %d\n", shaDataString, highScore, histogram[highScore], histogram[highScore-1], histogram[highScore-2], histogram[highScore-3], histogram[highScore-4], histogram[highScore-5], histogram[highScore-6], histogram[highScore-7], histogram[highScore-8], histogram[highScore-9], histogram[highScore-10], histogram[highScore-11], histogram[highScore-12], histogram[highScore-13], histogram[highScore-14], histogram[highScore-15], score);

    increment8BitArray(shaData, sizeof(shaData));
  }

  free(shaDataString);

  printDigest(shaDigest);
}

