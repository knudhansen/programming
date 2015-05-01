#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  BigNumber bn1 = BigNumber("123456");
  BigNumber bn2 = BigNumber("12344556674565");
  BigNumber bn4 = BigNumber("");
  BigNumber bn5 = BigNumber("11223344556677889900aabbccddeeff");

  bn1.print();
  bn2.print();

  BigNumber bn3 = bn1 + bn2;

  //  bn3.print();

  long a = xatoi("12");
  printf("a == %ld\n", a);
}
