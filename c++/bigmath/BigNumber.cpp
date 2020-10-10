#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>

#define NUMBER_OF_BITS_IN_INT 32
#define NUMBER_OF_DIGITS_IN_INT (NUMBER_OF_BITS_IN_INT / 4)

BigNumber::BigNumber(void)
{
}

BigNumber::~BigNumber(void)
{
  #warning "destructor not implemented yet."
}

BigNumber::BigNumber(char *numberAsString)
{

  // determining number of integers in number
  int numberOfIntegersInNumber = strlen(numberAsString) / NUMBER_OF_DIGITS_IN_INT;
  if (strlen(numberAsString) % NUMBER_OF_DIGITS_IN_INT > 0) {
    // unless number exactly fits in a number of int, we have to increment the number of ints to have the reminder
    numberOfIntegersInNumber++;
  }
  this->number = (unsigned int*) malloc (numberOfIntegersInNumber * sizeof(int));

  int intIndex = -1;
  char intString[NUMBER_OF_DIGITS_IN_INT + 1];

  while ((intIndex + 2) * NUMBER_OF_DIGITS_IN_INT < strlen(numberAsString)) {
    intIndex++;
    strncpy(intString, numberAsString + strlen(numberAsString) - (intIndex+1) * NUMBER_OF_DIGITS_IN_INT, NUMBER_OF_DIGITS_IN_INT);
    intString[NUMBER_OF_DIGITS_IN_INT] = 0;
    this->number[intIndex] = xatoi(intString);
  }

  intIndex++;
  if ((intIndex) * NUMBER_OF_DIGITS_IN_INT < strlen(numberAsString)) {
    strncpy(intString, numberAsString, strlen(numberAsString) - (intIndex) * NUMBER_OF_DIGITS_IN_INT);
    intString[strlen(numberAsString) - (intIndex) * NUMBER_OF_DIGITS_IN_INT] = 0;
    this->number[intIndex] = xatoi(intString);
  }

  this->length = intIndex+1;

}

BigNumber::BigNumber(unsigned char *numberAsByteArray, int byteCount)
{
  #warning "constructor from byte array not implemented yet."
}

BigNumber BigNumber::operator+(BigNumber& b)
{
  #warning "is it legal to return a local variable?"
  BigNumber sum;

  // worst case, the sum is one larger than the largest operand.
  sum.length = this->length > b.length ? this->length : b.length;
  sum.length++;
  // allocating number array for the sum.
  sum.number = (unsigned int*) malloc (sum.length * sizeof(unsigned int));

  // computing the sum. Ripple carry.
  long temp_sum = 0;
  for (int i = 0; i < sum.length; i++) {
    const long remainder = (temp_sum & 0xffffffff00000000L) >> NUMBER_OF_BITS_IN_INT;
    temp_sum = 0;
    temp_sum += i >= this->length ? 0 : this->number[i];
    temp_sum += i >= b.length ? 0 : b.number[i];
    temp_sum += remainder;
    sum.number[i] = (temp_sum & 0xffffffff);
  }

  // in case there is no carry for the MSI (most significant int) reducing the length.
  if (sum.number[sum.length - 1] == 0) {
    sum.length--;
  }

  return sum;
}

BigNumber BigNumber::operator*(BigNumber& b)
{
  #warning "is it legal to return a local variable?"
  BigNumber product;

  // worst case, the product has the sum of the operands integers.
  product.length = this->length + b.length;
  // allocating the number array for the product
  product.number = (unsigned int*) malloc (product.length * sizeof(unsigned int));
  // initializing the product
  memset(product.number, 0, product.length * sizeof(unsigned int));

  // computing the product
  for (int i = 0; i < this->length; i++) {
    long carry = 0;
    for (int j = 0; j < b.length; j++) {
      product.number[i+j] += ((long)this->number[i] * (long)b.number[j] + carry) & 0xffffffffL;
      carry = ((long)this->number[i] * (long)b.number[j] + carry) & 0xffffffff00000000L;
    }
  }

  // in case there as no carryxs for the MSI (most significant int) reducing the length.
  for (int i = product.length-1; i>= (this->length > b.length? this->length : b.length); i--) {
    if (product.number[i] == 0) {
      product.length--;
    } else {
      break;
    }
  }

  return product;

}

//BigNumber BigNumber::operator/(BigNumber& b)
//{
//}
//
//BigNumber BigNumber::operator%(BigNumber& b)
//{
//}

void BigNumber::operator=(BigNumber& b)
{
  free(this->number);
  this->number = (unsigned int*) malloc (b.length * sizeof(int));
  memcpy(this->number, b.number, b.length * sizeof(int));
  this->length = b.length;
}

bool BigNumber::operator==(BigNumber& b)
{
  for (int i = 0; i < (this->length > b.length ? this->length : b.length); i++) {
    const unsigned int anumber = i >= this->length ? 0 : this->number[i];
    const unsigned int bnumber = i >= b.length ? 0 : b.number[i];
    if (anumber != bnumber) {
      return false;
    }
  }
  return true;
}

bool BigNumber::operator!=(BigNumber& b)
{
  return !(*this == b);
}

bool BigNumber::operator<=(BigNumber& b)
{
  const int maxlength = this->length > b.length ? this->length : b.length;
  for (int i = maxlength - 1; i >= 0; i--) {
    const unsigned int anumber = i >= this->length ? 0 : this->number[i];
    const unsigned int bnumber = i >= b.length ? 0 : b.number[i];
    if (anumber > bnumber) {
      return false;
    } else if (anumber < bnumber) {
      return true;
    }
  }
  return true;
}

bool BigNumber::isPrime(void) {
  return false;
}

void BigNumber::print(void)
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
    if ( (number[i] & 0xf0) == 0x30) {
      digit = number[i] & 0x0f;
      if (digit > 9) {
	throw number;
      }
    } else if ( (number[i] & 0xf0) == 0x40 || (number[i] & 0xf0) == 0x60) {
      digit = (number[i] & 0x0f) + 9;
      if (digit < 10 || digit > 15) {
	throw number;
      }
    } else {
      throw number;
    }
    
    l += pow(16,strlen(number)-1-i) * digit;
  }
  return l;

}

#warning "Figure out what the difference is between the declaration of an object, new and malloc."
