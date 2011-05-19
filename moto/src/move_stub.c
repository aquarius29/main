#include <stdint.h>
#include "move_stub.h"
#include <stdio.h>
msg binMsg;
msg_pointer mpo;
unsigned int input;
int move_init()
{
#ifdef ARDUINO
    #ifdef DEBUG
    Serial.println("inside move_init");
    #endif
#endif
    return 0;
}

int move_run(){
  binMsg = scanHexMsgSTDIN();
  mpo = &binMsg;
/* To simulate movement sending just one message use the following line*/
/*----------------------------------------------------*/
/*proto_write_motor(BITFIELD_TO_CHAR(mpo));*/
/*----------------------------------------------------*/


/* To simulate movement sending a struct of messages use the following lines*/
/*----------------------------------------------------*/
    uint8_t msg1 = BITFIELD_TO_CHAR(mpo);
    uint8_t msg2 = 0xB;
    uint8_t msg3 = 0xB;
    uint8_t msg4 = 0xB;
    uint8_t msg5 = 0xB;
    uint8_t msg6 = 0xB;
    uint8_t msg7 = 0xB;
    uint8_t msg8 = 0xB;
    proto_write_motor2(msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8);


/*----------------------------------------------------*/
  return 0;
}

msg scanHexMsgSTDIN(void){

#ifdef ARDUINO
    #ifdef DEBUG    
    uint8_t input;
    Serial.println("Enter the message in hexadecimal!");

    input = serReadUnsignedChar();

    Serial.print("Number entered: ");
    Serial.println(input, HEX);

    if (input > -1 || input < 256){
        return INT_TO_BITFIELD(&input);
    }
    else
        return INT_TO_BITFIELD(0xf); //returns BAD_MSG
    #endif
#elif defined PC 
/*    unsigned int input; */
    #ifdef DEBUG
    printf("Enter the message in hexadecimal: ");
    #endif
    scanf("%x", &input);
    if (input > -1 || input < 256){
        return INT_TO_BITFIELD(&input);
    }
    else{
        input = 0xF;
        return INT_TO_BITFIELD(&input); //returns BAD_MSG
    }
#endif
}

/**
 * Function:     uint8_t serReadUnsignedChar()
 * Author(s):    Kristofer Hansson Aspman
 *
 * Description: Reads and stores what's currently in
 *              Serial.available() in an array.
 *              If there is something in the serial in
 *              then this is converted to an uint8_t
 *              with the help of sscanf() and returned.
 *              Otherwise 0xf is returned which is
 *              considered a bad message.
 *              Only used when compiled to ARDUINO.
 *              
 * Inspired by reply number 3 in this thread:
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1191880368
 */
#ifdef ARDUINO
        #ifdef DEBUG 
uint8_t serReadUnsignedChar(void)
{
    int8_t i;
    int8_t numberOfAvailableInputs;
    uint8_t returnValue;

    /* Array to hold input bytes*/
    char inputBytes [7];                     
    char * inputBytesPtr = &inputBytes[0];
    //delay(3000);
    /* Check to see if there are any serial input*/
   
        if (Serial.available()>0){
            Serial.println("serial available");

            /* Delay for terminal to finish transmitted, 5ms work great*/
            /* for 9600 baud (increase this number for slower baud)*/
            //delay(5);                              
            numberOfAvailableInputs = Serial.available();
        
            /* Load input bytes into array*/
            for (i=0; i<numberOfAvailableInputs; i++){
                inputBytes[i] = Serial.read();
            }
        
            /* Adding a NULL character at the end */
            inputBytes[i] =  '\0';
      
            /*Scans the character string and stores it as a hexadecimal*/
            sscanf(inputBytes, "%x", &returnValue);
            return returnValue;
        }
    
    else
        /* Returns BAD_MSG 0xf (0000 1111) if there is no input*/
        return 0xf;
}
    #endif
#endif
