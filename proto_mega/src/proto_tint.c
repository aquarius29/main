/*!
* @file proto_mov_motor.c
* @brief Message queue for Quickcheck integration
* @author Mihail Anton
*/
#ifdef PC

#include <stdlib.h>
#include <stdio.h>
#include "proto_lib.h"

struct Message * mPtr, * mTailPtr;

void storeForTint(int16_t operation, int16_t source, int16_t meaning, double value)
{	
    struct Message * curPtr;
	curPtr = (struct Message *) malloc(sizeof(struct Message));
	curPtr->operation = operation;
	curPtr->source = source;
	curPtr->meaning = meaning;
	curPtr->value = value;
	curPtr->next = NULL;
	if (mPtr == NULL){
		mPtr = curPtr;
    } else {
    	mTailPtr->next = curPtr;
    }
	mTailPtr = curPtr;
}

struct Message * retrieve(void)
{
	return mPtr;
}

void flush_messages(void)
{
	struct Message * buff;
	int i = 0;
	while(mPtr != NULL)
	{
	    i++;
		buff = mPtr;	
		mPtr = mPtr->next;
		free(buff);
	}
	printf("cleared %d\n", i);
}
#endif
