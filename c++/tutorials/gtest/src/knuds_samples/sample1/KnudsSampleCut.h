#ifndef KNUDS_SAMPLE_CUT_H
#define KNUDS_SAMPLE_CUT_H

#include "KnudsSampleSubclass.h"

class KnudsSampleCut {

 protected:
  KnudsSampleSubclass *subObject;

 public:
  KnudsSampleCut(KnudsSampleSubclass *subObject);
  virtual ~KnudsSampleCut(void);

  void method0(void);

};

#endif
