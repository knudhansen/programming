#include "Utl.h"
#include "UtlPlug.h"

Utl::Utl(void) {
  this->serverPlug = new UtlPlug(this);
  this->clientPlug = new UtlPlug(this);
}
