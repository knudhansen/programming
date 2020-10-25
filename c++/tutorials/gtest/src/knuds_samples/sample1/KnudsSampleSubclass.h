#ifndef KNUDSSAMPLESUBCLASS_H
#define KNUDSSAMPLESUBCLASS_H

class KnudsSampleSubclass {
 public:
  KnudsSampleSubclass(void) {}
  virtual ~KnudsSampleSubclass(void) {}
  virtual void method0(void) {}
  virtual int method1(int *intPtr) {return 0;}
};

#endif
