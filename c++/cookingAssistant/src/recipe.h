#ifndef RECIPE_H
#define RECIPE_H

class Recipe {
 private:
  char *name;
  Step *steps;
 public:
  Recipe(void);
  ~Recipe(void);

  void addStep(Step step);
};

#endif
