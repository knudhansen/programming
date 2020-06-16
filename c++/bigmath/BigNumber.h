#ifndef __BIGNUMBER_H__
#define __BIGNUMBER_H__

class BigNumber {

 private:
  // number of ints used to represent the number
  unsigned int  length;
  // array of ints for holding the number
  unsigned int* number;

 public:
  BigNumber(void);
  BigNumber(char* number);

  void operator=(BigNumber& a);
  BigNumber operator+(BigNumber& b);
  BigNumber operator*(BigNumber& b);
//  BigNumber operator/(BigNumber& b);
//  BigNumber operator%(BigNumber& b);
  bool operator==(BigNumber& b);
  bool operator!=(BigNumber& b);
  bool operator<=(BigNumber& b);

  bool isPrime(void);

  void print(void);
};

long xatoi(char* number);

#endif
