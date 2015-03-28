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

      char fibonacci_encoding[1000];
      
      int fibonacci_previous = 0;
      int fibonacci_current  = 1;
      int fibonacci_index    = 2;
      
      do {
	int temp = fibonacci_current;
	fibonacci_current = fibonacci_current + fibonacci_previous;
	fibonacci_previous = temp;
	fibonacci_index++;
      } while (argv_int >= fibonacci_current);


      int temp = fibonacci_previous;
      fibonacci_previous = fibonacci_current - fibonacci_previous;
      fibonacci_current = temp;
      fibonacci_index--;
      
      fibonacci_encoding[fibonacci_index - 1] = (char)0;
      fibonacci_encoding[fibonacci_index - 2] = '1';

      for (int j = fibonacci_index; j > 1; j--) {
	if (fibonacci_current <= argv_int) {

	  fibonacci_encoding[j-3] = '1';
	  argv_int -= fibonacci_current;
	        
	} else {

	  fibonacci_encoding[j-3] = '0';

	}
	
	int temp = fibonacci_previous;
	fibonacci_previous = fibonacci_current - fibonacci_previous;
	fibonacci_current = temp;
	fibonacci_index--;
	
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
