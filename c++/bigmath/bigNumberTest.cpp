#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ASSERT(x) assert(x, __FILE__, __LINE__);


void assert(const bool condition, const char* file, const int line);

int main(int argc, char **argv)
{

  unsigned int seed = time(NULL);
  srand(seed);
  
  printf("test seed = %08x\n\n", seed);

  /* 0-length numbers. */
  
  printf("testing 0-length numbers...\n");

  BigNumber bn0_a;
  BigNumber bn0_b;

  BigNumber bn0_sum = bn0_a + bn0_b;

  ASSERT(bn0_a == bn0_b);
  ASSERT(bn0_sum == bn0_a);
  ASSERT(bn0_sum == bn0_b);

  ASSERT(bn0_a <= bn0_a);
  ASSERT(bn0_a <= bn0_b);
  ASSERT(bn0_a <= bn0_sum);
  ASSERT(bn0_b <= bn0_a);
  ASSERT(bn0_b <= bn0_b);
  ASSERT(bn0_b <= bn0_sum);
  ASSERT(bn0_sum <= bn0_a);
  ASSERT(bn0_sum <= bn0_b);
  ASSERT(bn0_sum <= bn0_sum);

  printf("...done\n\n");

  /* illegal big numbers. */

  printf("testing illegal big numbers...\n");

  for (unsigned char i = 1; i < 0x80; i++) {

    char big_number_string[2];
    sprintf(big_number_string, "%c", i);
    bool illegal = ( (i < '0') ||
		     (i > '9' && i < 'A') ||
		     (i > 'F' && i < 'a') ||
		     (i > 'f') );
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

  BigNumber bn1_z = BigNumber((char*)"0");

  ASSERT(bn0_a == bn1_z);
  ASSERT(bn0_b == bn1_z);
  ASSERT(bn0_sum == bn1_z);

  BigNumber bn1_a = BigNumber((char*)"1");
  BigNumber bn1_b = BigNumber((char*)"2");
  BigNumber bn1_c = BigNumber((char*)"3");

  ASSERT(bn1_a != bn1_b);
  ASSERT(bn1_a != bn1_c);
  ASSERT(bn1_b != bn1_c);

  BigNumber bn1_sum_ab = bn1_a + bn1_b;

  ASSERT(bn1_sum_ab == bn1_c);

  BigNumber bn1_d = BigNumber((char*)"ffffffff");

  ASSERT(bn1_d != bn1_a);
  ASSERT(bn1_d != bn1_b);
  ASSERT(bn1_d != bn1_c);

  BigNumber bn1_sum_dd = bn1_d + bn1_d;

  ASSERT(bn1_sum_dd != bn1_a);
  ASSERT(bn1_sum_dd != bn1_b);
  ASSERT(bn1_sum_dd != bn1_c);
  ASSERT(bn1_sum_dd != bn1_d);

  ASSERT(bn0_a <= bn1_z);
  ASSERT(bn1_z <= bn0_a);
  ASSERT(bn0_a <= bn1_a);
  ASSERT(!(bn1_a <= bn0_a));
  ASSERT(bn0_a <= bn1_b);
  ASSERT(!(bn1_b <= bn0_a));
  ASSERT(bn0_a <= bn1_c);
  ASSERT(!(bn1_c <= bn0_a));
  ASSERT(bn0_a <= bn1_d);
  ASSERT(!(bn1_d <= bn0_a));
  ASSERT(bn0_a <= bn1_sum_ab);
  ASSERT(!(bn1_sum_ab <= bn0_a));
  ASSERT(bn0_a <= bn1_sum_dd);
  ASSERT(!(bn1_sum_dd <= bn0_a));
  ASSERT(bn0_b <= bn1_z);
  ASSERT(bn1_z <= bn0_b);
  ASSERT(bn0_b <= bn1_a);
  ASSERT(!(bn1_a <= bn0_b));
  ASSERT(bn0_b <= bn1_b);
  ASSERT(!(bn1_b <= bn0_b));
  ASSERT(bn0_b <= bn1_c);
  ASSERT(!(bn1_c <= bn0_b));
  ASSERT(bn0_b <= bn1_d);
  ASSERT(!(bn1_d <= bn0_b));
  ASSERT(bn0_b <= bn1_sum_ab);
  ASSERT(!(bn1_sum_ab <= bn0_b));
  ASSERT(bn0_b <= bn1_sum_dd);
  ASSERT(!(bn1_sum_dd <= bn0_b));
  ASSERT(bn0_sum <= bn1_z);
  ASSERT(bn1_z <= bn0_sum);
  ASSERT(bn0_sum <= bn1_a);
  ASSERT(!(bn1_a <= bn0_sum));
  ASSERT(bn0_sum <= bn1_b);
  ASSERT(!(bn1_b <= bn0_sum));
  ASSERT(bn0_sum <= bn1_c);
  ASSERT(!(bn1_c <= bn0_sum));
  ASSERT(bn0_sum <= bn1_d);
  ASSERT(!(bn1_d <= bn0_sum));
  ASSERT(bn0_sum <= bn1_sum_ab);
  ASSERT(!(bn1_sum_ab <= bn0_sum));
  ASSERT(bn0_sum <= bn1_sum_dd);
  ASSERT(!(bn1_sum_dd <= bn0_sum));

  ASSERT(bn1_z <= bn1_z);
  ASSERT(bn1_z <= bn1_a);
  ASSERT(bn1_z <= bn1_b);
  ASSERT(bn1_z <= bn1_c);
  ASSERT(bn1_z <= bn1_d);
  ASSERT(bn1_z <= bn1_sum_ab);
  ASSERT(bn1_z <= bn1_sum_dd);
  ASSERT(!(bn1_a <= bn1_z));
  ASSERT(bn1_a <= bn1_a);
  ASSERT(bn1_a <= bn1_b);
  ASSERT(bn1_a <= bn1_c);
  ASSERT(bn1_a <= bn1_d);
  ASSERT(bn1_a <= bn1_sum_ab);
  ASSERT(bn1_a <= bn1_sum_dd);
  ASSERT(!(bn1_b <= bn1_z));
  ASSERT(!(bn1_b <= bn1_a));
  ASSERT(bn1_b <= bn1_b);
  ASSERT(bn1_b <= bn1_c);
  ASSERT(bn1_b <= bn1_d);
  ASSERT(bn1_b <= bn1_sum_ab);
  ASSERT(bn1_b <= bn1_sum_dd);
  ASSERT(!(bn1_c <= bn1_z));
  ASSERT(!(bn1_c <= bn1_a));
  ASSERT(!(bn1_c <= bn1_b));
  ASSERT(bn1_c <= bn1_c);
  ASSERT(bn1_c <= bn1_d);
  ASSERT(bn1_c <= bn1_sum_ab);
  ASSERT(bn1_c <= bn1_sum_dd);
  ASSERT(!(bn1_d <= bn1_z));
  ASSERT(!(bn1_d <= bn1_a));
  ASSERT(!(bn1_d <= bn1_b));
  ASSERT(!(bn1_d <= bn1_c));
  ASSERT(bn1_d <= bn1_d);
  ASSERT(!(bn1_d <= bn1_sum_ab));
  ASSERT(bn1_d <= bn1_sum_dd);
  ASSERT(!(bn1_sum_ab <= bn1_z));
  ASSERT(!(bn1_sum_ab <= bn1_a));
  ASSERT(!(bn1_sum_ab <= bn1_b));
  ASSERT(bn1_sum_ab <= bn1_c);
  ASSERT(bn1_sum_ab <= bn1_d);
  ASSERT(bn1_sum_ab <= bn1_sum_ab);
  ASSERT(bn1_sum_ab <= bn1_sum_dd);
  ASSERT(!(bn1_sum_dd <= bn1_z));
  ASSERT(!(bn1_sum_dd <= bn1_a));
  ASSERT(!(bn1_sum_dd <= bn1_b));
  ASSERT(!(bn1_sum_dd <= bn1_c));
  ASSERT(!(bn1_sum_dd <= bn1_d));
  ASSERT(!(bn1_sum_dd <= bn1_sum_ab));
  ASSERT(bn1_sum_dd <= bn1_sum_dd);

  printf("...done\n\n");



  /* 2-length numbers. */

  printf("testing 2-length numbers...\n");

  BigNumber bn2_a = BigNumber((char*)"100000000");

  ASSERT(bn2_a != bn0_a);
  ASSERT(bn2_a != bn0_b);
  ASSERT(bn2_a != bn0_sum);
  ASSERT(bn2_a != bn1_z);
  ASSERT(bn2_a != bn1_a);
  ASSERT(bn2_a != bn1_b);
  ASSERT(bn2_a != bn1_c);
  ASSERT(bn2_a != bn1_d);
  ASSERT(bn2_a != bn1_sum_dd);

  BigNumber bn2_b = BigNumber((char*)"100000001");

  ASSERT(bn2_a != bn2_b);
  ASSERT((bn2_a + bn1_a) == bn2_b);

  BigNumber bn2_c = BigNumber((char*)"200000001");

  ASSERT((bn2_a + bn2_b) == bn2_c);
  // FIXME: this does not even compile! There must be something wrong with operator==:  ASSERT(bn2_c == (bn2_a + bn2_b));

  BigNumber bn2_d = BigNumber((char*)"1fffffffe");

  ASSERT(bn2_d == bn1_sum_dd);

  BigNumber bn2_e = BigNumber((char*)"ffffffffffffffff");

  BigNumber bn2_sum_ee = bn2_e + bn2_e;

  BigNumber bn3_a = BigNumber((char*)"1fffffffffffffffe");

  ASSERT(bn2_sum_ee == bn3_a);

  ASSERT(!(bn2_a <= bn0_a));
  ASSERT(bn0_a <= bn2_a);
  ASSERT(!(bn2_a <= bn0_b));
  ASSERT(bn0_b <= bn2_a);
  ASSERT(!(bn2_a <= bn0_sum));
  ASSERT(bn0_sum <= bn2_a);
  ASSERT(!(bn2_a <= bn1_z));
  ASSERT(bn1_z <= bn2_a);
  ASSERT(!(bn2_a <= bn1_a));
  ASSERT(bn1_a <= bn2_a);
  ASSERT(!(bn2_a <= bn1_b));
  ASSERT(bn1_b <= bn2_a);
  ASSERT(!(bn2_a <= bn1_c));
  ASSERT(bn1_c <= bn2_a);
  ASSERT(!(bn2_a <= bn1_d));
  ASSERT(bn1_d <= bn2_a);
  ASSERT(!(bn2_a <= bn1_sum_ab));
  ASSERT(bn1_sum_ab <= bn2_a);
  ASSERT(bn2_a <= bn1_sum_dd);
  ASSERT(!(bn1_sum_dd <= bn2_a));
  ASSERT(!(bn2_b <= bn0_a));
  ASSERT(bn0_a <= bn2_b);
  ASSERT(!(bn2_b <= bn0_b));
  ASSERT(bn0_b <= bn2_b);
  ASSERT(!(bn2_b <= bn0_sum));
  ASSERT(bn0_sum <= bn2_b);
  ASSERT(!(bn2_b <= bn1_z));
  ASSERT(bn1_z <= bn2_b);
  ASSERT(!(bn2_b <= bn1_a));
  ASSERT(bn1_a <= bn2_b);
  ASSERT(!(bn2_b <= bn1_b));
  ASSERT(bn1_b <= bn2_b);
  ASSERT(!(bn2_b <= bn1_c));
  ASSERT(bn1_c <= bn2_b);
  ASSERT(!(bn2_b <= bn1_d));
  ASSERT(bn1_d <= bn2_b);
  ASSERT(!(bn2_b <= bn1_sum_ab));
  ASSERT(bn1_sum_ab <= bn2_b);
  ASSERT(bn2_b <= bn1_sum_dd);
  ASSERT(!(bn1_sum_dd <= bn2_b));
  ASSERT(!(bn2_c <= bn0_a));
  ASSERT(bn0_a <= bn2_c);
  ASSERT(!(bn2_c <= bn0_b));
  ASSERT(bn0_b <= bn2_c);
  ASSERT(!(bn2_c <= bn0_sum));
  ASSERT(bn0_sum <= bn2_c);
  ASSERT(!(bn2_c <= bn1_z));
  ASSERT(bn1_z <= bn2_c);
  ASSERT(!(bn2_c <= bn1_a));
  ASSERT(bn1_a <= bn2_c);
  ASSERT(!(bn2_c <= bn1_b));
  ASSERT(bn1_b <= bn2_c);
  ASSERT(!(bn2_c <= bn1_c));
  ASSERT(bn1_c <= bn2_c);
  ASSERT(!(bn2_c <= bn1_d));
  ASSERT(bn1_d <= bn2_c);
  ASSERT(!(bn2_c <= bn1_sum_ab));
  ASSERT(bn1_sum_ab <= bn2_c);
  ASSERT(!(bn2_c <= bn1_sum_dd));
  ASSERT(bn1_sum_dd <= bn2_c);
  ASSERT(!(bn2_d <= bn0_a));
  ASSERT(bn0_a <= bn2_d);
  ASSERT(!(bn2_d <= bn0_b));
  ASSERT(bn0_b <= bn2_d);
  ASSERT(!(bn2_d <= bn0_sum));
  ASSERT(bn0_sum <= bn2_d);
  ASSERT(!(bn2_d <= bn1_z));
  ASSERT(bn1_z <= bn2_d);
  ASSERT(!(bn2_d <= bn1_a));
  ASSERT(bn1_a <= bn2_d);
  ASSERT(!(bn2_d <= bn1_b));
  ASSERT(bn1_b <= bn2_d);
  ASSERT(!(bn2_d <= bn1_c));
  ASSERT(bn1_c <= bn2_d);
  ASSERT(!(bn2_d <= bn1_d));
  ASSERT(bn1_d <= bn2_d);
  ASSERT(!(bn2_d <= bn1_sum_ab));
  ASSERT(bn1_sum_ab <= bn2_d);
  ASSERT(bn2_d <= bn1_sum_dd);
  ASSERT(bn1_sum_dd <= bn2_d);
  ASSERT(!(bn2_e <= bn0_a));
  ASSERT(bn0_a <= bn2_e);
  ASSERT(!(bn2_e <= bn0_b));
  ASSERT(bn0_b <= bn2_e);
  ASSERT(!(bn2_e <= bn0_sum));
  ASSERT(bn0_sum <= bn2_e);
  ASSERT(!(bn2_e <= bn1_z));
  ASSERT(bn1_z <= bn2_e);
  ASSERT(!(bn2_e <= bn1_a));
  ASSERT(bn1_a <= bn2_e);
  ASSERT(!(bn2_e <= bn1_b));
  ASSERT(bn1_b <= bn2_e);
  ASSERT(!(bn2_e <= bn1_c));
  ASSERT(bn1_c <= bn2_e);
  ASSERT(!(bn2_e <= bn1_d));
  ASSERT(bn1_d <= bn2_e);
  ASSERT(!(bn2_e <= bn1_sum_ab));
  ASSERT(bn1_sum_ab <= bn2_e);
  ASSERT(!(bn2_e <= bn1_sum_dd));
  ASSERT(bn1_sum_dd <= bn2_e);
  ASSERT(!(bn2_sum_ee <= bn0_a));
  ASSERT(bn0_a <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn0_b));
  ASSERT(bn0_b <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn0_sum));
  ASSERT(bn0_sum <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn1_z));
  ASSERT(bn1_z <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn1_a));
  ASSERT(bn1_a <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn1_b));
  ASSERT(bn1_b <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn1_c));
  ASSERT(bn1_c <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn1_d));
  ASSERT(bn1_d <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn1_sum_ab));
  ASSERT(bn1_sum_ab <= bn2_sum_ee);
  ASSERT(!(bn2_sum_ee <= bn1_sum_dd));
  ASSERT(bn1_sum_dd <= bn2_sum_ee);
  ASSERT(!(bn3_a <= bn0_a));
  ASSERT(bn0_a <= bn3_a);
  ASSERT(!(bn3_a <= bn0_b));
  ASSERT(bn0_b <= bn3_a);
  ASSERT(!(bn3_a <= bn0_sum));
  ASSERT(bn0_sum <= bn3_a);
  ASSERT(!(bn3_a <= bn1_z));
  ASSERT(bn1_z <= bn3_a);
  ASSERT(!(bn3_a <= bn1_a));
  ASSERT(bn1_a <= bn3_a);
  ASSERT(!(bn3_a <= bn1_b));
  ASSERT(bn1_b <= bn3_a);
  ASSERT(!(bn3_a <= bn1_c));
  ASSERT(bn1_c <= bn3_a);
  ASSERT(!(bn3_a <= bn1_d));
  ASSERT(bn1_d <= bn3_a);
  ASSERT(!(bn3_a <= bn1_sum_ab));
  ASSERT(bn1_sum_ab <= bn3_a);
  ASSERT(!(bn3_a <= bn1_sum_dd));
  ASSERT(bn1_sum_dd <= bn3_a);

  ASSERT(bn2_a <= bn2_a);
  ASSERT(bn2_a <= bn2_b);
  ASSERT(bn2_a <= bn2_c);
  ASSERT(bn2_a <= bn2_d);
  ASSERT(bn2_a <= bn2_e);
  ASSERT(bn2_a <= bn2_sum_ee);
  ASSERT(bn2_a <= bn3_a);
  ASSERT(!(bn2_b <= bn2_a));
  ASSERT(bn2_b <= bn2_b);
  ASSERT(bn2_b <= bn2_c);
  ASSERT(bn2_b <= bn2_d);
  ASSERT(bn2_b <= bn2_e);
  ASSERT(bn2_b <= bn2_sum_ee);
  ASSERT(bn2_b <= bn3_a);
  ASSERT(!(bn2_c <= bn2_a));
  ASSERT(!(bn2_c <= bn2_b));
  ASSERT(bn2_c <= bn2_c);
  ASSERT(!(bn2_c <= bn2_d));
  ASSERT(bn2_c <= bn2_e);
  ASSERT(bn2_c <= bn2_sum_ee);
  ASSERT(bn2_c <= bn3_a);
  ASSERT(!(bn2_d <= bn2_a));
  ASSERT(!(bn2_d <= bn2_b));
  ASSERT(bn2_d <= bn2_c);
  ASSERT(bn2_d <= bn2_d);
  ASSERT(bn2_d <= bn2_e);
  ASSERT(bn2_d <= bn2_sum_ee);
  ASSERT(bn2_d <= bn3_a);
  ASSERT(!(bn2_e <= bn2_a));
  ASSERT(!(bn2_e <= bn2_b));
  ASSERT(!(bn2_e <= bn2_c));
  ASSERT(!(bn2_e <= bn2_d));
  ASSERT(bn2_e <= bn2_e);
  ASSERT(bn2_e <= bn2_sum_ee);
  ASSERT(bn2_e <= bn3_a);
  ASSERT(!(bn2_sum_ee <= bn2_a));
  ASSERT(!(bn2_sum_ee <= bn2_b));
  ASSERT(!(bn2_sum_ee <= bn2_c));
  ASSERT(!(bn2_sum_ee <= bn2_d));
  ASSERT(!(bn2_sum_ee <= bn2_e));
  ASSERT(bn2_sum_ee <= bn2_sum_ee);
  ASSERT(bn2_sum_ee <= bn3_a);
  ASSERT(!(bn3_a <= bn2_a));
  ASSERT(!(bn3_a <= bn2_b));
  ASSERT(!(bn3_a <= bn2_c));
  ASSERT(!(bn3_a <= bn2_d));
  ASSERT(!(bn3_a <= bn2_e));
  ASSERT(bn3_a <= bn2_sum_ee);
  ASSERT(bn3_a <= bn3_a);

  printf("...done\n\n");

  /* long numbers. */

  printf("testing long numbers...\n");

  printf("%d\n", rand());

  printf("...done\n\n");




  BigNumber bn1 = BigNumber((char*)"123456");
  BigNumber bn2 = BigNumber((char*)"12344556674565");
  BigNumber bn4 = BigNumber((char*)"");
  BigNumber bn5 = BigNumber((char*)"11223344556677889900aabbccddeeff");
  BigNumber bn7 = BigNumber((char*)"ffffffff");
  BigNumber bn9 = BigNumber((char*)"12345678");
  BigNumber bna = BigNumber((char*)"100000000");

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
