#ifndef STEP_H
#define STEP_H

#include <stddef.h>

class Step;

class Step {
 private:
  char *action;
  Step *previous;
  Step *next;

 public:
  Step(const char *action);
  ~Step();
  const char *asString(void);
};

#endif
