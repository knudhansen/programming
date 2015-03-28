#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int decode(char* fibonacci_sequence, int length);

int main(int argc, char **argv) {

  if (argc < 2) {
    return 1;
  }
  if (argc > 2) {
    return 1;
  }

  char* current_number = argv[1];
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

//  char* number = argv;
//
//  printf("%d\n", decode(argv[1], strlen(argv[1])));
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
    current = current + previous;
  }

  return decoded;
}
