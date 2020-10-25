#include "KnudsSampleCut.h"
#include <stdio.h>

KnudsSampleCut::KnudsSampleCut(KnudsSampleSubclass *subObject) {
  this->subObject = subObject;
}

KnudsSampleCut::~KnudsSampleCut(void) {
}



void KnudsSampleCut::method0(void) {
  this->subObject->method0();
}
