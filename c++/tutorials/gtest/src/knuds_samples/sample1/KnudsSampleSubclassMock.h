#ifndef KNUDSSAMPLESUBCLASSMOCK_H
#define KNUDSSAMPLESUBCLASSMOCK_H

#include "gmock/gmock.h"

class KnudsSampleSubclassMock: public KnudsSampleSubclass {

 public:
  MOCK_METHOD(void, method0, ());

};

#endif
