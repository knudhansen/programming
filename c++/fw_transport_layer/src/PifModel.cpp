#include <stdlib.h>
#include <string.h>

#include "PifModel.h"

PifModel::PifModel(uint16_t pifRxBufferByteSize, uint16_t pifTxBufferByteSize,
		   pifWriteCallback_t pifWriteCallback,
		   pifReadCallback_t pifReadCallback) {
  this->pifRxBufferByteSize = pifRxBufferByteSize;
  this->pifTxBufferByteSize = pifTxBufferByteSize;
  this->pifWriteCallback = pifWriteCallback;
  this->pifReadCallback = pifReadCallback;

  // allocating memory for rx and tx buffers
  this->pifRxBuffer = (uint8_t*)malloc(this->pifRxBufferByteSize * sizeof(uint8_t));
  this->pifTxBuffer = (uint8_t*)malloc(this->pifTxBufferByteSize * sizeof(uint8_t));
}

pifStatus_t PifModel::pifWriteRead(uint16_t writeByteSize, uint8_t *writeData,
				   uint16_t readByteSize,  uint8_t *readData) {
  if (writeByteSize > this->pifRxBufferByteSize) {
    return FAILURE_TOO_MANY_RX_BYTES;
  }
  if (readByteSize > this->pifTxBufferByteSize) {
    return FAILURE_TOO_MANY_TX_BYTES;
  }

  memcpy(this->pifRxBuffer, writeData, writeByteSize);
  this->pifWriteCallback(writeByteSize);

  this->pifReadCallback(readByteSize);
  memcpy(readData, this->pifTxBuffer, readByteSize);

  return SUCCESS;
}
