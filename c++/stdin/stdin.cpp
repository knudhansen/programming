#include <stdio.h>
#include <stdlib.h>

typedef void (*argument_callback_t)(int argi, char *argv);

void parse_input(argument_callback_t callback, int argc, char **argv);

void argument_handler(int argi, char *argv) {
  printf("argument number %d is %s\n", argi, argv);
}

int main(int argc, char **argv) {
  parse_input(&argument_handler, argc, argv);
}

void parse_input(argument_callback_t callback, int argc, char **argv) {
  /*** arguments from command line ***/
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      callback(i, argv[i]);
    }

  /*** arguments from standard input ***/
  } else {
    char s[1024];
    int length = 0;
    int i = 1;

    int c;
    while (EOF != (c = fgetc(stdin))) {
      if (c == 10 || c == 32) {
	s[length] = '\0';
	callback(i, s);
	i++;
	length = 0;
      } else {
	s[length] = c;
	length++;
      }
    }

  }
}
