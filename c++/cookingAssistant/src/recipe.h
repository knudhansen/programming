#ifndef RECIPE_H
#define RECIPE_H

#include "linked_list.h"
#include "step.h"

class Recipe {
 private:
  char *name;
  LinkedList<Step*> *steps;
 public:
  Recipe(void);
  ~Recipe(void);

  void addStep(Step step);
};

#endif
