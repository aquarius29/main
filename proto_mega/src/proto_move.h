/*****************************************************************************
* Product: 
* Version: 
* Released: April 8 2011
* Updated: April 28 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* 
*
* <IT University of Goteborg>
*****************************************************************************/

struct move {
        int speed;
        int direction_move;
};


//write from movement to collision avodance  
void proto_write(struct move mv);// proto API 
 
 
//read from movement to collision avodance 
struct move proto_read();// proto API 

