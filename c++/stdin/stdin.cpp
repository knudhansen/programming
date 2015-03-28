#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  char s[128];
  int length = 0;

  int c;
  while (EOF != (c = fgetc(stdin))) {
    if (c == 10) {
      s[length] = '\0';
      printf("%s ", s);
      length = 0;
    } else {
      s[length] = c;
      length++;
    }
  }
}
