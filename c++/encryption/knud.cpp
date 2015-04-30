#include <stdio.h>
#include <math.h>

typedef struct key {
  long modulus;
  long exponent;
} key_t;

long phi(long p, long q);
long encode(long data, key_t *key);
long decode(long data, key_t *key);
long powmod(long data, long exponent, long modulus);

int main(int argc, char **argv) {

  long p = 61;
  long q = 53;

  long n = p * q;

  long phi_n = phi(p,q);

  long e;

  for (e = 2; e < phi_n; e++) {
    bool found = true;
    for (long j = 2; j < phi_n; j++) {
      if (e%j == 0 && phi_n%j == 0) {
	found = false;
	break;
      }
    }

    if (found) {
      break;
    }
  }

  printf("found e = %ld\n", e);

  //  long e = 17;

  /*
    finding d
    2> 2*5 % 8 = 10 % 8 = 2
    3> 3*5 % 8 = 15 % 8 = 7
    4> 4*5 % 8 = 20 % 8 = 4
    5> 5*5 % 8 = 25 % 8 = 1
   */

  long d = 2;

  while ( ((d * e) % phi_n) != 1 ) {
    d++;
  }

  printf("found d = %ld\n", d);

  //  long d = 2753;

  key_t publickey;
  publickey.modulus = n;
  publickey.exponent = e;

  key_t privatekey;
  privatekey.modulus = n;
  privatekey.exponent = d;

  for (long i = 0; i < n; i++) {
    long encoded;
    long decoded;

    encoded = encode(i, &publickey);
    decoded = decode(encoded, &privatekey);
    printf("data> %8ld  |  encoded> %8ld  |  decoded> %8ld\n", i, encoded, decoded);
    if (decoded != i) return -1;

    encoded = encode(i, &privatekey);
    decoded = decode(encoded, &publickey);
    printf("data> %8ld  |  encoded> %8ld  |  decoded> %8ld\n", i, encoded, decoded);
    if (decoded != i) return -1;
  }

}

long phi(long p, long q) {
  
  return (p-1) * (q-1);

}

long encode(long data, key_t *key) {
  
  return powmod(data, key->exponent, key->modulus);

}

long decode(long data, key_t *key) {

  return powmod(data, key->exponent, key->modulus);

}

long powmod(long data, long exponent, long modulus) {
  long temp = 1;
  for (long i = 0; i < exponent; i++) {
    temp = temp * data;
    temp = temp % modulus;
  }
  return temp;
}



// data>       41  |  encoded>      525  |  decoded>      31e
