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
void *KnudsSampleCut::method1(unsigned char *route, int routeLength, int offset) {
  return this->subObject->method1(route, routeLength, offset);
}
