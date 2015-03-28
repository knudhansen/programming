#include <stdlib.h>
#include <stdio.h>

int main() {

  char s[1024];
  int s_length = 0;

  int c;

  while (EOF != (c = fgetc(stdin))) {
    if (c == 10) {
      s[s_length] = '\0';

      int argv_int = atoi(s);

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

      s_length = 0;
    } else {
      s[s_length] = c;
      s_length++;
    }
  }
  
  printf("\n");

}
