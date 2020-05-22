#ifndef STEP_H
#define STEP_H

#include <stddef.h>
#include <time.h>

class Step;

class Step {
 private:
  char *action;
  time_t duration;
  Step *previous;
  Step *next;

 public:
  Step(const char *action);
  ~Step();
  const char *asString(void);
};

#endif
