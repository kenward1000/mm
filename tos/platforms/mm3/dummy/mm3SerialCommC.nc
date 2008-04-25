/**
 * Copyright @ 2008 Eric B. Decker
 * @author Eric B. Decker
 */
 
#include "sensors.h"

configuration mm3SerialCommC {
  provides {
    interface Send[uint8_t id];
    interface AMPacket;
    interface Packet;
    interface SplitControl;
  }
}

implementation {
  components mm3SerialCommP;
  components new SerialAMSenderC(AM_MM3_DATA);
  components new AMQueueImplP(MM3_NUM_SENSORS), SerialActiveMessageC;

  Send = mm3SerialCommP;
  AMPacket = SerialAMSenderC;
  Packet = SerialAMSenderC;
  SplitControl = SerialActiveMessageC;
  
  mm3SerialCommP.SubSend -> AMQueueImplP;
  AMQueueImplP.AMSend[AM_MM3_DATA] -> SerialAMSenderC;
  AMQueueImplP.Packet -> SerialAMSenderC;
  AMQueueImplP.AMPacket -> SerialAMSenderC;
  
  components new NoArbiterC();
  mm3SerialCommP.Resource -> NoArbiterC.Resource;
  
  components LedsC;
  mm3SerialCommP.Leds -> LedsC;
}
