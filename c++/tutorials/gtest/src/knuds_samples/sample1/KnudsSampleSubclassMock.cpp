#include "KnudsSampleSubclassMock.h"
#include <stdio.h>

KnudsSampleSubclassMock::KnudsSampleSubclassMock(void) {
  printf("constructing mock\n");
  ON_CALL(*this, method1).WillByDefault([this](int *n) {
    printf("method1 called\n");
    return 0;
    });
}
KnudsSampleSubclassMock::~KnudsSampleSubclassMock(void) {
  printf("destructing mock\n");
}
