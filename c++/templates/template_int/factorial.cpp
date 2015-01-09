#include <iostream>

template<int N>
struct Factorial {
  enum {value = N * Factorial<N-1>::value};
};

template <>
struct Factorial<0> {
  enum {value = 1};
};

template <>
struct Factorial<3> {
  enum {value = 1};
};

int main() {
  std::cout << Factorial<1>::value << "\n";
  std::cout << Factorial<2>::value << "\n";
  std::cout << Factorial<3>::value << "\n";
  std::cout << Factorial<4>::value << "\n";
  std::cout << Factorial<5>::value << "\n";
}
