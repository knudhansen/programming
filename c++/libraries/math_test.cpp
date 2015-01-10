#include <stdio.h>
#include "math.h"

int main() {
  int a = 1;
  int b = 2;

  printf("%d + %d = %d\n", a, b, add(a,b));

  long c = 3;
  long d = 4;

  printf("%ld + %ld = %ld\n", c, d, add(c,d));
}
