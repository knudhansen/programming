#include <stdio.h>
#include <stdint.h>

#include "PifModel.h"
#include "FwTransportLayerPdu.h"

pifStatus_t pifWriteCallback(uint16_t writeByteSize);
pifStatus_t pifReadCallback(uint16_t readByteSize);

int main() {
  printf("instantiating pif model...\n");
  PifModel *pifModel = new PifModel(256, 256, &pifWriteCallback, &pifReadCallback);
  printf("...done\n");

  uint16_t availableReadData = 0;

  printf("performing write/read on pif model...\n");
  uint8_t writeData[] = { 1,2,3,4,5,6,7,8 };
  uint8_t readData[256];

  pifModel->pifWriteRead(sizeof(writeData), writeData,
			 FwTransportLayerPdu::pduSize(availableReadData), readData);
  printf("...done\n");
}

// model of pif fw
uint16_t pifFwBytesReady = 0;

pifStatus_t pifWriteCallback(uint16_t writeByteSize) {
  printf("pifWriteCallback called -- write byte size: %d\n", writeByteSize);

  // parse writePdu to get
  // - 
  // schedule execution of operation(s)

  return SUCCESS;
}
pifStatus_t pifReadCallback(uint16_t readByteSize) {
  printf("pifReadCallback called -- read byte size: %d\n", readByteSize);

  // construct readPdu based on
  // - amount of bytes ready for read
  // - room for additional writes for that connection
  // - requested read-data

  // write the pdu in pifTxBuffer

  return SUCCESS;
}

