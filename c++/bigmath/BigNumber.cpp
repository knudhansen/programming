#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>

#define NUMBER_OF_BITS_IN_INT 32
#define NUMBER_OF_DIGITS_IN_INT (NUMBER_OF_BITS_IN_INT / 4)

BigNumber::BigNumber()
{
}

BigNumber::BigNumber(char *number)
{

  int numberOfIntegersInNumber = strlen(number) / NUMBER_OF_DIGITS_IN_INT;
  if (strlen(number) % NUMBER_OF_DIGITS_IN_INT > 0) {
    numberOfIntegersInNumber++;
  }
  this->number = (unsigned int*) malloc (numberOfIntegersInNumber * sizeof(int));

  int intIndex = -1;
  char intString[NUMBER_OF_DIGITS_IN_INT + 1];

  while ((intIndex + 2) * NUMBER_OF_DIGITS_IN_INT < strlen(number)) {
    intIndex++;
    strncpy(intString, number + strlen(number) - (intIndex+1) * NUMBER_OF_DIGITS_IN_INT, NUMBER_OF_DIGITS_IN_INT);
    intString[NUMBER_OF_DIGITS_IN_INT] = 0;
    this->number[intIndex] = xatoi(intString);
  }

  intIndex++;
  if ((intIndex) * NUMBER_OF_DIGITS_IN_INT < strlen(number)) {
    strncpy(intString, number, strlen(number) - (intIndex) * NUMBER_OF_DIGITS_IN_INT);
    intString[strlen(number) - (intIndex) * NUMBER_OF_DIGITS_IN_INT] = 0;
    this->number[intIndex] = xatoi(intString);
  }

  this->length = intIndex+1;

}


BigNumber BigNumber::operator+(BigNumber& b)
{
  BigNumber sum;

  // worst case, the sum is one larger than the largest operand.
  sum.length = this->length > b.length ? this->length : b.length;
  sum.length++;
  // allocating number array for the sum.
  sum.number = (unsigned int*) malloc (sum.length * sizeof(int));

  // computing the sum. Ripple carry.
  long temp_sum = 0;
  for (int i = 0; i < sum.length; i++) {
    long remainder = (temp_sum & 0xffffffff00000000L) >> NUMBER_OF_BITS_IN_INT;
    temp_sum = 0;
    temp_sum += i >= this->length ? 0 : this->number[i];
    temp_sum += i >= b.length ? 0 : b.number[i];
    temp_sum += remainder;
    sum.number[i] = (temp_sum & 0xffffffff);
  }

  // in case there as no carry for the MSI (most significant int) reducing the length.
  if (sum.number[sum.length - 1] == 0) {
    sum.length--;
  }

  return sum;
}

BigNumber BigNumber::operator*(BigNumber& b)
{
  BigNumber product;

  // worst case, the product has the sum of the operands integers.
  product.length = this->length + b.length;
  // allocating the number array for the product
  product.number = (unsigned int*) malloc (product.length * sizeof(int));
  // initializing the product
  memset(product.number, 0, product.length * sizeof(int));

  // computing the product
  for (int i = 0; i < this->length; i++) {
    long carry = 0;
    for (int j = 0; j < b.length; j++) {
      product.number[i+j] += ((long)this->number[i] * (long)b.number[j] + carry) & 0xffffffffL;
      carry = ((long)this->number[i] * (long)b.number[j] + carry) & 0xffffffff00000000L;
    }
  }

  // in case there as no carry for the MSI (most significant int) reducing the length.
  for (int i = product.length-1; i>= (this->length > b.length? this->length : b.length); i--) {
    if (product.number[i] == 0) {
      product.length--;
    } else {
      break;
    }
  }

  return product;

}

void BigNumber::operator=(BigNumber& a)
{
  free(this->number);
  this->number = (unsigned int*) malloc (a.length * sizeof(int));
  memcpy(this->number, a.number, a.length * sizeof(int));
  this->length = a.length;
}

void BigNumber::print()
{
  for (int i = this->length-1; i >= 0; i--) {
    if (i == this->length-1) {      
      printf("%x", this->number[i]);
    } else {
      printf("%08x", this->number[i]);
    }
  }
  printf("\n");
}

/**
 * converts a hex string to a number
 * no leading 0x
 */
long xatoi(char* number)
{

  long l = 0;

  for (int i=0; i < strlen(number); i++) {
    int digit;
    if ( (number[i] & 0x30) == 0x30) {
      // printf("dec digit\n");
      digit = number[i] & 0x0f;
    } else if ( (number[i] & 0x40) == 0x40 || (number[i] & 0x60) == 0x60) {
      // printf("hex digit\n");
      digit = (number[i] & 0x0f) + 9;
    } else {
      // printf("illegal digit\n");
      digit = 0;
    }
    
    l += pow(16,strlen(number)-1-i) * digit;
  }
  return l;

}
