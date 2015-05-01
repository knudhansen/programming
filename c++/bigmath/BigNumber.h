#ifndef __BIGNUMBER_H__
#define __BIGNUMBER_H__

class BigNumber {

 private:
  char* number;

 public:
  BigNumber();
  BigNumber(char* number);

  BigNumber add(BigNumber& b);
  void operator=(BigNumber& a);
  BigNumber operator+(BigNumber& b);

  void print();
};

#endif
