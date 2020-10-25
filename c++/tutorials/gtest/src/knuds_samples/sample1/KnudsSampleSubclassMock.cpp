#include "KnudsSampleSubclassMock.h"
#include <stdio.h>

KnudsSampleSubclassMock::KnudsSampleSubclassMock(void) {
  printf("constructing mock\n");
  ON_CALL(*this, method1).WillByDefault([this](unsigned char *route, int routeLength, int offset) {
      printf("method1 called:\n");
      printf("  ");
      for (int i = 0; i < routeLength; i++) {
	printf("0x%02x ", route[i]);
      }
      printf("offset=%d\n", offset);
      return (void*)NULL;
    });
}
KnudsSampleSubclassMock::~KnudsSampleSubclassMock(void) {
  printf("destructing mock\n");
}
