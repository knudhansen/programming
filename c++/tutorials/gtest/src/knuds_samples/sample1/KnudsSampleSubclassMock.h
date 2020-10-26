#ifndef KNUDSSAMPLESUBCLASSMOCK_H
#define KNUDSSAMPLESUBCLASSMOCK_H

#include "gmock/gmock.h"

#include "KnudsSampleSubclass.h"
#include "Route.h"

class KnudsSampleSubclassMock: public KnudsSampleSubclass {

 public:
  KnudsSampleSubclassMock(void);
  ~KnudsSampleSubclassMock(void);
  void registerRoute(unsigned char *route, int routeLength, void *registerPtr);


  MOCK_METHOD(void, method0, ());
  MOCK_METHOD(void*, method1, (unsigned char *route, int routeLength, int offset));

 private:
  std::map<Route, void*> routes;

  void *_getRegisterPointer(unsigned char *route, int routeLength);
  void *_route(unsigned char *route, int routeLength, int offset);
};

#endif
