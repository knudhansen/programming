#ifndef KNUDSSAMPLESUBCLASSMOCK_H
#define KNUDSSAMPLESUBCLASSMOCK_H

#include "gmock/gmock.h"

#include "KnudsSampleSubclass.h"

class KnudsSampleSubclassMock: public KnudsSampleSubclass {

 public:
  KnudsSampleSubclassMock(void);
  ~KnudsSampleSubclassMock(void);

  MOCK_METHOD(void, method0, ());
  MOCK_METHOD(int, method1, (int *intPtr));

};

#endif
