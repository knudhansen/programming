#ifndef __BIGNUMBER_H__
#define __BIGNUMBER_H__

class BigNumber {

 private:
  unsigned int  length;
  unsigned int* number;

 public:
  BigNumber();
  BigNumber(char* number);

  void operator=(BigNumber& a);
  BigNumber operator+(BigNumber& b);
  BigNumber operator*(BigNumber& b);

  void print();
};

long xatoi(char* number);

#endif
