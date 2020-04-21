#include "step.h"

#include <stdlib.h>
#include <string.h>
#include <iostream>

Step::Step(const char *action) {
  this->action = (char*)malloc((strlen(action) + 1) * sizeof (char));
  strcpy(this->action, action);
  this->previous = NULL;
  this->next = NULL;
}

Step::~Step(void) {
  free(this->action);
}

const char* Step::asString(void) {
  return this->action;
}
