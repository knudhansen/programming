#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {

  if (argc < 2) {
    return 1;
  }

  for (int k = 0; k < argc - 1; k++) {

    int argv_int = atoi(argv[k+1]);

    int fibonacci_sequence[10000];
    char fibonacci_encoding[1000];

    fibonacci_sequence[0] = 0;
    fibonacci_sequence[1] = 1;
    int i = 2;
    
    do {
      fibonacci_sequence[i] = fibonacci_sequence[i-2] + fibonacci_sequence[i-1];
      i++;
    } while (argv_int >= fibonacci_sequence[i-1]);
    i--;
    
    
    fibonacci_encoding[i-1] = (char)0;
    fibonacci_encoding[i-2] = '1';
    for (int j = i; j > 1; j--) {
      if (fibonacci_sequence[j] > argv_int && fibonacci_sequence[j-1] <= argv_int) {
	fibonacci_encoding[j-3] = '1';
	argv_int -= fibonacci_sequence[j-1];
      } else {
	fibonacci_encoding[j-3] = '0';
      }
    }
    
    printf("%s", fibonacci_encoding);
  }

  printf("\n");

}
