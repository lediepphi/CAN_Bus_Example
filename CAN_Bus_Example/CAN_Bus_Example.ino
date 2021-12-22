#include <stdio.h>
#include "Can.h"
#include "mcp2515.h"


MCP2515 Mcp2515(10);
Can_MsgBufferType *Can_MsgSend, *Can_MsgReceive;


char Can_SerialBufferOut[33];
uint32_t Task1_Millis, Task1_LastMillis = 0;


void setup() {
  Can_MsgSend = Can_MsgBuffer_Create();
  Can_MsgReceive = Can_MsgBuffer_Create();

  Can_MsgSend->ID  = 0x06F;
  Can_MsgSend->dlc = 8;
  Can_MsgSend->data[0] = 0x8E;
  Can_MsgSend->data[1] = 0x87;
  Can_MsgSend->data[2] = 0x32;
  Can_MsgSend->data[3] = 0xFA;
  Can_MsgSend->data[4] = 0x26;
  Can_MsgSend->data[5] = 0x8E;
  Can_MsgSend->data[6] = 0xBE;
  Can_MsgSend->data[7] = 0x00;

  while (!Serial);
  Serial.begin(38400);

  Mcp2515.reset();

  Mcp2515.setBitrate(CAN_500KBPS);
  Mcp2515.setNormalMode();

  Serial.println("Example: Write to CAN");
}

void loop() {
  Task1_Millis = millis();
  if (Mcp2515.checkReceive()) {
    if (MCP2515::ERROR_OK == Mcp2515.readMessage(Can_MsgReceive)) {
      Serial.print("Messages Received: ");
      Can_MsgCompress(Can_MsgReceive, Can_SerialBufferOut);
      Serial.println(Can_SerialBufferOut);
    } else {
      Serial.println("Error on receing");
    }
  }

  if ((Task1_Millis - Task1_LastMillis) > 500) {
    Mcp2515.sendMessage(Can_MsgSend);
    Serial.print("Messages Sent: ");
    Can_MsgCompress(Can_MsgSend, Can_SerialBufferOut);
    Serial.println(Can_SerialBufferOut);
    Can_MsgSend->data[7]++;
    Task1_LastMillis = Task1_Millis;
  }
}
