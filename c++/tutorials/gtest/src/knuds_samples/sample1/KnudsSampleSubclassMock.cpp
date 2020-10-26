#include "KnudsSampleSubclassMock.h"
#include <map>
#include <stdio.h>

KnudsSampleSubclassMock::KnudsSampleSubclassMock(void) {
  // updating default action on call.
  ON_CALL(*this, method1).WillByDefault([this](unsigned char *route, int routeLength, int offset) {
      return this->_route(route, routeLength, offset);
    });
}
KnudsSampleSubclassMock::~KnudsSampleSubclassMock(void) {
}

void KnudsSampleSubclassMock::registerRoute(unsigned char *route, int routeLength, void *registerPtr) {
  routes.insert(std::pair<Route,void*>(Route(route, routeLength), registerPtr));
}

void *KnudsSampleSubclassMock::_getRegisterPointer(unsigned char *route, int routeLength) {
  return routes.at(Route(route, routeLength));
}

void *KnudsSampleSubclassMock::_route(unsigned char *route, int routeLength, int offset) {
  return _getRegisterPointer(route, routeLength);
}
