/*****************************************************************************
* Product: 
* Version: 
* Released: April 28 2011
* Updated: April 28 2011
*
* Copyright (C) 2011 Petre Mihail Anton
*
* <IT University of Goteborg>
*****************************************************************************/
#ifdef PC

#include <stdlib.h>
#include <stdio.h>
#include "proto_lib.h"


struct Message * mPtr;


void storeForTint(int operation, int source, int meaning, double value)
{	
	struct Message * curPtr;
	curPtr = (struct Message *) malloc(sizeof(struct Message));
	curPtr->operation = operation;
	curPtr->source = source;
	curPtr->meaning = meaning;
	curPtr->value = value;
	curPtr->next = NULL;
	if (mPtr == NULL)
		mPtr = curPtr;
	else
		mPtr->next = curPtr;
}

struct Message * retrieve(void)
{
	return mPtr;
}

void flush(void)
{
	struct Message * buff;
	while(mPtr != NULL)
	{
		buff = mPtr;	
		mPtr = mPtr->next;
		free(buff);
	}
}
#endif
