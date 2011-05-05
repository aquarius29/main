#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

#define INT_TO_BITFIELD(a) *(msg_pointer)a
#define BITFIELD_TO_CHAR(a) *(unsigned char*)a

//Big endian control message
typedef struct control_message{
  //unsigned char may not be portable
  //if that is the case, try just unsigned
  //also, endianess may be different on arduino
  unsigned char rear :1;
  unsigned char front :1;
  unsigned char left :1;
  unsigned char right :1;
  unsigned char panic :1;
  unsigned char increase :1;
  unsigned char ID :2;
} msg, *msg_pointer;

//Little endian control message
/* struct control_message{ */
/*   unsigned char ID :2; */
/*   unsigned char increase :1; */
/*   unsigned char panic :1; */
/*   unsigned char right :1; */
/*   unsigned char left :1; */
/*   unsigned char front :1; */
/*   unsigned char rear :1; */

/* } msg; */

void printMsg(msg_pointer mp);
