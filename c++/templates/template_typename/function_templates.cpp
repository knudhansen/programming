#include <iostream>

long add (long a, long b) {
  return a-b;
}

template <typename T>
T add (T a, T b) {
  return a+b;
}

int main() {
  int int_a, int_b;
  int_a = 10;
  int_b = 5;

  std::cout << add(int_a,int_b) << "\n";

  long long_a, long_b;
  long_a = 10;
  long_b = 5;

  std:: cout << add(long_a, long_b) << "\n";
}
