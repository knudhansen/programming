#include <stdio.h>
#include "step.h"

int main(int argc, char *argv[]) {
  Step *step = new Step("do this");
  printf("step: %s\n", step->asString());
}
