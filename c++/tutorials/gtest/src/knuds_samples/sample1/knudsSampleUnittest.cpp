#include "gtest/gtest.h"
#include "KnudsSampleCut.h"
#include "KnudsSampleSubclassMock.h"

using namespace testing;

TEST(knudsFirstTestcase, helloWorld) {
  KnudsSampleSubclassMock subObjectMock;
  KnudsSampleCut *kscut = new KnudsSampleCut(&subObjectMock); // FIXME: is there a way to not have to pass the mock in the construction of the CUT?

  EXPECT_CALL(subObjectMock, method0());
  kscut->method0();
}

TEST(knudsFirstTestcase, playingMoreWithTheMock) {
  KnudsSampleSubclassMock subObjectMock;
  KnudsSampleCut *kscut = new KnudsSampleCut(&subObjectMock); // FIXME: is there a way to not have to pass the mock in the construction of the CUT?

  unsigned char route[] = {1,2,3};
  unsigned int reg[10];
  subObjectMock.registerRoute(route, sizeof(route), &reg);

  // no action defined on the expected call, so using the default action.
  // the default action has been defined in the mock.
  EXPECT_CALL(subObjectMock, method1(_,_,_));
  void *ret1 = kscut->method1(route, sizeof(route), 0);
  EXPECT_EQ(ret1, &reg);

  // defining an action on the expected call. This action replaces the
  // default action defined in the mock.
  EXPECT_CALL(subObjectMock, method1(_,_,_)).WillOnce(Return((void*)5));
  void *ret2 = kscut->method1(route, sizeof(route), 0);
  EXPECT_EQ(ret2, (void*)5);
}

MATCHER_P(routeCompare, route, "equality matcher for routes") {
}

TEST(knudsFirstTestcase, DefiningComplexMockBehviorFromTest) {
  KnudsSampleSubclassMock subObjectMock;
  KnudsSampleCut *kscut = new KnudsSampleCut(&subObjectMock); // FIXME: is there a way to not have to pass the mock in the construction of the CUT?

  unsigned char route[] = {1,2,3};
  unsigned int reg[10];

  EXPECT_CALL(subObjectMock, method1(_,_,_)).WillOnce(Return((void*)6));
  void *ret1 = kscut->method1(route, sizeof(route), 0);
  EXPECT_EQ(ret1, (void*)6);
}
