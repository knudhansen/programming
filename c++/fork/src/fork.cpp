#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
  pid_t pid;

  pid = fork();
  pid = fork();
  printf("hello world from %d\n", pid);

}
