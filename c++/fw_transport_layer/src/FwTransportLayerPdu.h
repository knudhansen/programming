#ifndef __FWTRANSPORTLAYERPDU_H__
#define __FWTRANSPORTLAYERPDU_H__

//typedef enum fwTransportLayerPdu_connectionControl {
//  OPEN,
//  CLOSE,
//  TRANSPORT
//} fwTransportLayerPdu_connectionControl_t;
//
//typedef enum fwTransportLayerPdu_serviceId {
//  S0,
//  S1,
//  S2,
//  S3,
//  S4,
//  S5,
//  S6,
//  S7,
//  S8,
//  S9,
//  SA,
//  SB,
//  SC,
//  SD,
//  SE,
//  SF
//} fwTransportLayerPdu_serviceId_t;
//
//typedef enum fwTransportLayerPdu_mode {
//  CLIENT_PULL,
//  SERVER_PUSH,
//} fwTransportLayerPdu_mode_t;
//
//typedef uint16_t fwTransportLayerPdu_readLength_t;
//typedef uint16_t fwTransportLayerPdu_payloadLength_t;
//typedef uint8_t *fwTransportLayerPdu_payload_t;

class FwTransportLayerPdu {
// private:
//  fwTransportLayerPdu_connectionControl_t connCtrl;
//  fwTransportLayerPdu_serviceId_t serviceId;
//  fwTransportLayerPdu_mode_t mode;
//  fwTransportLayerPdu_readLength_t readLength;
//  fwTransportLayerPdu_payloadLength_t payloadLength;
//  fwTransportLayerPdu_paylaod_t payload;
 public:
  static uint16_t pduSize(uint16_t payloadSize);
};


#endif
