#include "BigNumber.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

BigNumber::BigNumber()
{
}

BigNumber::BigNumber(char *number)
{
  this->number = (char*) malloc (strlen(number) * sizeof(char));
  strcpy(this->number, number);
}

BigNumber BigNumber::add(BigNumber& b)
{
  BigNumber bigNumber = BigNumber("1");
  return bigNumber;
}


BigNumber BigNumber::operator+(BigNumber& b)
{

  long na = atoi(this->number);
  long nb = atoi(b.number);
  long nsum = na + nb;
  BigNumber sum;
  long sumstrlen = strlen(this->number);
  if (strlen(b.number) > sumstrlen) {
    sumstrlen = strlen(b.number);
  }
  sum.number = (char*) malloc (sumstrlen);
  sprintf(sum.number, "%ld", nsum);
  return sum;

}


void BigNumber::operator=(BigNumber& a)
{
  free(this->number);
  this->number = (char*) malloc (strlen(a.number) * sizeof(char));
  strcpy(this->number, a.number);
}

void BigNumber::print()
{
  printf("%s\n",this->number);
}
