#ifndef ROUTE_H
#define ROUTE_H

class Route {
private:
  unsigned char *route;
  int routeLength;
public:
  Route(unsigned char *route, int routeLength) {
    this->route = route;
    this->routeLength = routeLength;
  }
  bool operator <(const Route &b) const {
    if (routeLength != b.routeLength) {
      return (routeLength < b.routeLength);
    } else {
      for (int i = 0; i < routeLength; i++) {
	if (route[i] != b.route[i]) {
	  return (route[i] < b.route[i]);
	}
      }
      return false;
    }
  }
};

#endif
