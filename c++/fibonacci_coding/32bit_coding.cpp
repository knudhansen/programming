#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {

  char s[1024];
  int s_length = 0;

  int c;

  while (EOF != (c = fgetc(stdin))) {
    if (c == 10) {
      char encoding_32bit[33];

      s[s_length] = '\0';
      encoding_32bit[32] = '\0';

      int argv_int = atoi(s);

      for (int i = 31; i >=0; i--) {
	if (argv_int >= pow(2,i)) {
	  encoding_32bit[i] = '1';
	  argv_int = argv_int - pow(2,i);
	} else {
	  encoding_32bit[i] = '0';
	}
      }

      printf("%s",encoding_32bit);

      s_length = 0;

    } else {
      s[s_length] = c;
      s_length++;
    }
  }

  printf("\n");
  
}
