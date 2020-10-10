#include <stdint.h>

#include "FwTransportLayerPdu.h"

uint16_t FwTransportLayerPdu::pduSize(uint16_t payloadSize) {
  return payloadSize;
}
