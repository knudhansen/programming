#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void encode_32bits(int a);

int main(int argc, char **argv) {

  char s[1024];
  int s_length = 0;

  int c;

  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      encode_32bits(atoi(argv[i]));
    }
  } else {
    while (EOF != (c = fgetc(stdin))) {
      if (c == 10) {
	s[s_length] = '\0';

	encode_32bits(atoi(s));
  	
	s_length = 0;
	
      } else {
	s[s_length] = c;
	s_length++;
      }
    }
  }

  printf("\n");
  
}

void encode_32bits(int a) {
  char encoding_32bit[33];
	
  encoding_32bit[32] = '\0';
  
  for (int i = 31; i >=0; i--) {
    if (a >= pow(2,i)) {
      encoding_32bit[i] = '1';
      a = a - pow(2,i);
    } else {
      encoding_32bit[i] = '0';
    }
  }
  
  printf("%s",encoding_32bit);
}
