#ifndef UTLPLUG_H
#define UTLPLUG_H

#include <stdint.h>
#include <string.h>

#include "status.h"

typedef status_t (*rcvCallback_t)(uint8_t *data, size_t length);

class Utl;

class UtlPlug {
 private:
  Utl *utl;

 public:
  UtlPlug(Utl *utl);

  status_t snd(const uint8_t *data, size_t length);
};

#endif
