#ifndef __PIFMODEL_H__
#define __PIFMODEL_H__

#include <stdint.h>

typedef enum pifStatus_enum {
  SUCCESS,
  FAILURE_TOO_MANY_RX_BYTES,
  FAILURE_TOO_MANY_TX_BYTES
} pifStatus_t;

typedef pifStatus_t (*pifWriteCallback_t)(uint16_t writeByteSize);
typedef pifStatus_t (*pifReadCallback_t)(uint16_t readByteSize);

class PifModel {
 private:
  uint16_t pifRxBufferByteSize;
  uint8_t *pifRxBuffer;
  uint16_t pifTxBufferByteSize;
  uint8_t *pifTxBuffer;
  pifWriteCallback_t pifWriteCallback;
  pifReadCallback_t pifReadCallback;

 public:
  // test interface
  PifModel(uint16_t pifRxBufferSize, uint16_t pifTxBufferSize,
	   pifWriteCallback_t pifWriteCallback,
	   pifReadCallback_t pifReadCallback);

  // bottom interface
  pifStatus_t pifWriteRead(uint16_t writeByteSize, uint8_t *writeData,
			   uint16_t readByteSize,  uint8_t *readData);

  // top interface
};

#endif
