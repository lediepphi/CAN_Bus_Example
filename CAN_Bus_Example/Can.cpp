/****************************************************************************************
   File name:       Can.cpp
   Description:     Implementation for Can module
   Version:         1.0
   Date:            22/12/2021: New
 ****************************************************************************************/

/****************************************************************************************
        Inclusion
 ****************************************************************************************/
#include "Can.h"

/****************************************************************************************
        Local Variable Definition
 ****************************************************************************************/

/****************************************************************************************
        Global Variable Definition
 ****************************************************************************************/

/****************************************************************************************
        Local Function Definition
 ****************************************************************************************/

/****************************************************************************************
        Global Function Definition
 ****************************************************************************************/

/****************************************************************************************
   @FunctionName:   Can_MsgBuffer_Create
   @Description:    Create a message buffer for transceiving
   @Param:          None
   @Return:         Can_MsgBufferType
 ****************************************************************************************/
Can_MsgBufferType * Can_MsgBuffer_Create(void) {
  Can_MsgBufferType * Can_MsgBuffer = (Can_MsgBufferType *) malloc(sizeof(Can_MsgBufferType));
  if (Can_MsgBuffer != NULL) {
    Can_MsgBuffer->ID = 0;
    Can_MsgBuffer->dlc = 0;
    for (uint8_t ind = 0; ind < CAN_MAX_DLC; ind++) {
      Can_MsgBuffer->data[ind] = 0;
    }
  }
  return Can_MsgBuffer;
}

void Can_MsgBuffer_Destroy(Can_MsgBufferType* const Can_MsgBuffer) {
  free(Can_MsgBuffer);
}

void Can_MsgCompress(const Can_MsgBufferType *Can_MsgBuffer, char * Char_Buffer) {
  sprintf(Char_Buffer, "%03lX %X %02X %02X %02X %02X %02X %02X %02X %02X",
          Can_MsgBuffer->ID, Can_MsgBuffer->dlc,
          Can_MsgBuffer->data[0], Can_MsgBuffer->data[1],
          Can_MsgBuffer->data[2], Can_MsgBuffer->data[3],
          Can_MsgBuffer->data[4], Can_MsgBuffer->data[5],
          Can_MsgBuffer->data[6], Can_MsgBuffer->data[7]);

  uint8_t ind = 5 + 3 * (Can_MsgBuffer->dlc);
  do {
    Char_Buffer[ind++] = '\0';
  } while (ind < MAX_CHAR_BUFFER_MSG);
}

void Can_MsgExtract(const Can_MsgBufferType *Can_MsgBuffer, char * Char_Buffer) {

}
/** End of file *************************************************************************/
