#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  BigNumber bn1 = BigNumber("1");
  BigNumber bn2 = BigNumber("5");

  bn1.print();
  bn2.print();

  BigNumber bn3 = bn1 + bn2;

  bn3.print();

  int a = atoi("0x1234");
  printf("a == %d", a);
}
