volatile int a;
volatile int b;
volatile int c;

int add(int a, int b) {
  return a+b;
}

int main() {
    a = 0;
    b = 1;
    c = add(a, b);
    return a;
}
