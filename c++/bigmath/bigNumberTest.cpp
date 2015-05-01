#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>

#define ASSERT(x) assert(x, __FILE__, __LINE__);


void assert(const bool condition, const char* file, const int line);

int main(int argc, char **argv)
{

  /* 0-length numbers. */
  
  printf("testing 0-length numbers...\n");

  BigNumber bn0_a;
  BigNumber bn0_b;

  BigNumber bn0_sum = bn0_a + bn0_b;

  ASSERT(bn0_a == bn0_b);
  ASSERT(bn0_sum == bn0_a);
  ASSERT(bn0_sum == bn0_b);

  printf("...done\n\n");



  /* illegal big numbers. */

  printf("testing illegal big numbers...\n");

  for (unsigned char i = 1; i < 0x80; i++) {

    char big_number_string[2];
    sprintf(big_number_string, "%c", i);
    bool illegal = ( (i >= 0x00 && i < 0x30) ||
		     (i >= 0x3a && i < 0x41) ||
		     (i >= 0x47 && i < 0x61) ||
		     (i >= 0x67) );
    try {
      BigNumber bnIllegalSingleCharacter = BigNumber(big_number_string);
      if (illegal) {
	ASSERT(false);
      }
    } catch (const char* message) {
      if (!illegal) {
	ASSERT(false);
      }
    }
    
  }

  printf("...done\n\n");




  /* 1-length numbers. */

  printf("testing 1-length numbers...\n");

  BigNumber bn1_z = BigNumber("0");

  ASSERT(bn0_a == bn1_z);
  ASSERT(bn0_b == bn1_z);
  ASSERT(bn0_sum == bn1_z);

  BigNumber bn1_a = BigNumber("1");
  BigNumber bn1_b = BigNumber("2");
  BigNumber bn1_c = BigNumber("3");

  ASSERT(bn1_a != bn1_b);
  ASSERT(bn1_a != bn1_c);
  ASSERT(bn1_b != bn1_c);

  BigNumber bn1_sum_ab = bn1_a + bn1_b;

  ASSERT(bn1_sum_ab == bn1_c);

  BigNumber bn1_d = BigNumber("ffffffff");

  ASSERT(bn1_d != bn1_a);
  ASSERT(bn1_d != bn1_b);
  ASSERT(bn1_d != bn1_c);

  BigNumber bn1_sum_dd = bn1_d + bn1_d;

  ASSERT(bn1_sum_dd != bn1_a);
  ASSERT(bn1_sum_dd != bn1_b);
  ASSERT(bn1_sum_dd != bn1_c);
  ASSERT(bn1_sum_dd != bn1_d);

  printf("...done\n\n");



  /* 2-length numbers. */

  printf("testing 2-length numbers...\n");

  BigNumber bn2_a = BigNumber("100000000");

  ASSERT(bn2_a != bn0_a);
  ASSERT(bn2_a != bn0_b);
  ASSERT(bn2_a != bn0_sum);
  ASSERT(bn2_a != bn1_z);
  ASSERT(bn2_a != bn1_a);
  ASSERT(bn2_a != bn1_b);
  ASSERT(bn2_a != bn1_c);
  ASSERT(bn2_a != bn1_d);
  ASSERT(bn2_a != bn1_sum_dd);

  BigNumber bn2_b = BigNumber("100000001");

  ASSERT(bn2_a != bn2_b);
  ASSERT((bn2_a + bn1_a) == bn2_b);

  BigNumber bn2_c = BigNumber("200000001");

  ASSERT((bn2_a + bn2_b) == bn2_c);
  // FIXME: this does not even compile! There must be something wrong with operator==:  ASSERT(bn2_c == (bn2_a + bn2_b));

  BigNumber bn2_d = BigNumber("1fffffffe");

  ASSERT(bn2_d == bn1_sum_dd);

  printf("...done\n\n");



  /* long numbers. */


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

}


void assert(const bool condition, const char *file, const int line) {

  if (!condition) {
    printf("assertion at %s::%d failed!\n", file, line);

    throw condition;
  }

}
