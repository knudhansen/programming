#ifndef KNUDSSAMPLESUBCLASS_H
#define KNUDSSAMPLESUBCLASS_H

class KnudsSampleSubclass {
 public:
  KnudsSampleSubclass(void) {}
  virtual ~KnudsSampleSubclass(void) {}
  virtual void method0(void) {}
  virtual void *method1(unsigned char *route, int routeLength, int offset) {return 0;}
};

#endif
