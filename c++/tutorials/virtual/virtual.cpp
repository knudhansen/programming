#include <stdio.h>

class Base {
public:
  void method1();
  virtual void method2();
  
};

class Subclass: public Base {
public:
  void method1();
  void method2();
};

void callMethods(Base *base) {
  base->method1();
  base->method2();
}

int main(int argc, char *argv[]) {
  Base base;
  Subclass subclass;

  printf("calling methods from main on Base object\n");
  base.method1();
  base.method2();
  printf("calling methods from main on Subclass object\n");
  subclass.method1();
  subclass.method2();
  printf("\n");

  printf("calling methods via function on Base object\n");
  callMethods(&base);
  printf("calling methods via function on Subclass object\n");
  callMethods(&subclass);
}

void Base::method1(void) {
  printf("Base.method1\n");
}
void Base::method2(void) {
  printf("Base.method2\n");
}
void Subclass::method1(void) {
  printf("Subclass.method1\n");
}
void Subclass::method2(void) {
  printf("Subclass.method2\n");
}
