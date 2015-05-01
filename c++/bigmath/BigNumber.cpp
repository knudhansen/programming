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
  this->number = (int*) malloc (numberOfIntegersInNumber * sizeof(int));

  printf("allocated %d integers for number %s\n", numberOfIntegersInNumber, number);

  int intIndex = -1;
  char intString[NUMBER_OF_DIGITS_IN_INT + 1];

  while ((intIndex + 2) * NUMBER_OF_DIGITS_IN_INT <= strlen(number)) {
    intIndex++;
    strncpy(intString, number + strlen(number) - (intIndex+1) * NUMBER_OF_DIGITS_IN_INT, NUMBER_OF_DIGITS_IN_INT);
    intString[NUMBER_OF_DIGITS_IN_INT] = 0;
    printf("%d>> %s\n", intIndex, intString);
    this->number[intIndex] = xatoi(intString);
  }

  intIndex++;
  if ((intIndex) * NUMBER_OF_DIGITS_IN_INT < strlen(number)) {
    strncpy(intString, number, strlen(number) - (intIndex) * NUMBER_OF_DIGITS_IN_INT);
    intString[strlen(number) - (intIndex) * NUMBER_OF_DIGITS_IN_INT] = 0;
    printf("gfs%d>> %s\n", intIndex, intString);
    this->number[intIndex] = xatoi(intString);
  }

  this->length = intIndex+1;
}


BigNumber BigNumber::operator+(BigNumber& b)
{

//  long na = atoi(this->number);
//  long nb = atoi(b.number);
//  long nsum = na + nb;
//  BigNumber sum;
//  long sumstrlen = strlen(this->number);
//  if (strlen(b.number) > sumstrlen) {
//    sumstrlen = strlen(b.number);
//  }
//  sum.number = (char*) malloc (sumstrlen);
//  sprintf(sum.number, "%ld", nsum);
//  return sum;

  BigNumber bigNumber = BigNumber();
  return bigNumber;
}


void BigNumber::operator=(BigNumber& a)
{
//  free(this->number);
//  this->number = (char*) malloc (strlen(a.number) * sizeof(char));
//  strcpy(this->number, a.number);
}

void BigNumber::print()
{
  for (int i = 0; i < this->length; i++) {
    printf("%d ", this->number[i]);
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
    // printf("-- %c(%d) -> %d\n", number[i], number[i], digit);
    
    l += pow(16,strlen(number)-1-i) * digit;
  }
  return l;

}
