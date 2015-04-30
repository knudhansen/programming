#include <stdio.h>

#define MAX 10240

int main (int argc, char **argv) {

  bool prime[MAX];
  for (int i = 0; i < MAX; i++) {
    prime[i] = true;
  }

  for (int i = 2; i < MAX; i++) {
    if (prime[i]) {
      printf("%d is prime\n", i);
    }
    for (int j = 2; i*j < MAX; j++) {
      prime[i*j] = false;
    }
  }


}
