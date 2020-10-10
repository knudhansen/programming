#ifndef UTL_H
#define UTL_H

#include "status.h"

class UtlPlug;

class Utl {

 private:
  UtlPlug *serverPlug;
  UtlPlug *clientPlug;

 public:
  Utl(void);

  status_t connectClient(UtlPlug *utlPlug);
  status_t connectServer(UtlPlug *utlPlug);

};

#endif
