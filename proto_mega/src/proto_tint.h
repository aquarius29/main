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

#define READ 0
#define WRITE 1

#define STAB 3
#define COLLISION 4
#define NAV 5
#define MOTOR 6
#define MOVEMENT 7
#define CONNECTIVITY 8
#define CAMERA 9
#define FILTER 10
#define UI 10
#define UNKNOWN -1

struct Message {
	int operation;
	int source;
	int meaning;
	double value;
	struct Message *next;
} * mPtr;

void storeForTint(int operation, int source, int meaning, double value);

struct Message * retrieve(void);

void flush(void);

#endif
