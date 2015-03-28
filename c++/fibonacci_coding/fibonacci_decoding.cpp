#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int decode(char* fibonacci_sequence, int length);

int main() {
  char s[1024];
  int s_length = 0;

  int c;
  while(EOF != (c = fgetc(stdin))) {
    s[s_length] = c;
    s_length++;
    if (s[s_length-1] == '1' && s[s_length-2] == '1') {

      s[s_length] = '\0';

      char* current_number = s;
      int current_number_length = 1;
      
      while(current_number[current_number_length-1] != '\0') {
	do {
	  current_number_length++;
	} while (current_number[current_number_length-1] != '\0' &&
		 !(current_number[current_number_length-1] == '1' &&
		   current_number[current_number_length-2] == '1')
		 );
	if (current_number[current_number_length-1] == '\0') {
	  break;
	}
	printf("%d ", decode(current_number, current_number_length));
	current_number += current_number_length;
	current_number_length = 1;
      }
      
      printf("\n");

      s_length = 0;
    }
  }

  return 0;
}

int decode(char* fibonacci_sequence, int length) {
  if (fibonacci_sequence[length-1] != '1' || fibonacci_sequence[length-2] != '1') {
    throw fibonacci_sequence;
  }

  int decoded = 0;
  
  int previous = 1;
  int current = 1;

  for (int i = 0; i < length-1; i++) {
    if (fibonacci_sequence[i] == '1') {
      decoded += current;
    }
    int temp = current;
    current = current + previous;
    previous = temp;
  }

  return decoded;
}
