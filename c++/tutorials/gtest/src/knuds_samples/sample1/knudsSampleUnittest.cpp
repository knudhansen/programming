#include "gtest/gtest.h"
#include "KnudsSampleCut.h"
#include "KnudsSampleSubclassMock.h"

TEST(knudsFirstTestcase, knudsFirstTestcase) {
  KnudsSampleSubclassMock subObjectMock;
  KnudsSampleCut *kscut = new KnudsSampleCut(&subObjectMock);

  EXPECT_CALL(subObjectMock, method0());
  kscut->method0();
}
