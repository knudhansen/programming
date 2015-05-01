#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  BigNumber bn1 = BigNumber("123456");
  BigNumber bn2 = BigNumber("12344556674565");
  BigNumber bn4 = BigNumber("");
  BigNumber bn5 = BigNumber("11223344556677889900aabbccddeeff");
  BigNumber bn7 = BigNumber("ffffffff");
  BigNumber bn9 = BigNumber("12345678");
  BigNumber bna = BigNumber("100000000");

  bn1.print();
  bn2.print();
  bn4.print();
  bn7.print();

  BigNumber bn3 = bn1 + bn2;
  BigNumber bn6 = bn4 + bn2;
  BigNumber bn8 = bn7 + bn7;

  bn3.print();
  bn6.print();
  bn8.print();

  BigNumber bnb = bn1 * bna;

  bnb.print();

  unsigned long a = 0xffffffffL * 0xffffffffL;

  printf("%lx\n",a);

}
