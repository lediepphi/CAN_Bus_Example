/****************************************************************************************
   File name:       Can.h
   Description:     Implementation for Can module
   Version:         1.0
   Date:            22/12/2021: New
 ****************************************************************************************/

#ifndef CAN_H_
#define CAN_H_

/****************************************************************************************
        Inclusion
 ****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/****************************************************************************************
        Local Macro Definition
 ****************************************************************************************/

/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000UL                   /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000UL                   /* Remote transmission request */
#define CAN_ERR_FLAG 0x20000000UL                   /* Error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFUL                   /* Standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFUL                   /* Extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFUL                   /* Omit EFF, RTR, ERR flags */

#define CAN_SFF_ID_BITS     11                      /* Number of ID bits in SFF */
#define CAN_EFF_ID_BITS     29                      /* Number of ID bits in EFF */

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC 8
/* Maximum number of char when compress CAN frame to string */
#define MAX_CHAR_BUFFER_MSG 30


/****************************************************************************************
        Typedef Definition
 ****************************************************************************************/
typedef uint32_t Can_IdType;
struct Can_MsgBufferType {
  Can_IdType ID;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
  uint8_t    dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
  uint8_t    data[CAN_MAX_DLC] __attribute__((aligned(CAN_MAX_DLC)));
};

/****************************************************************************************
        Local Function Prototype Definition
 ****************************************************************************************/

/****************************************************************************************
        Global Function Prototype Definition
 ****************************************************************************************/
Can_MsgBufferType * Can_MsgBuffer_Create(void);
void Can_MsgBuffer_Destroy(Can_MsgBufferType* const Can_MsgBuffer);
void Can_MsgCompress(const Can_MsgBufferType *Can_MsgBuffer, char * Char_Buffer);
void Can_MsgExtract(const Can_MsgBufferType *Can_MsgBuffer, char * Char_Buffer);

#endif /* CAN_H_ */

/** End of file *************************************************************************/
