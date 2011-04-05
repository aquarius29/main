/*
* Author: Jarryd Hall
* Purpose: Tilemap representation
*/

#include "Tilemap.h"

CGPoint* tileForCoordinates (CGPoint position, short width, short height)
{	
	CGPoint *tileCoordinate = (CGPoint*)malloc(sizeof(CGPoint));
	tileCoordinate->xPosition = (position.xPosition / width);
	tileCoordinate->yPosition = (position.yPosition / height);
	
	return tileCoordinate;
}



// TODO: Create this function to be reusable for adding items to an array
/*
int AddItemToArray ()
{
	
}
*/

// Correct data structure for the 2nd year square tilemap
// TODO: Create this dynamically from the parsed xml file

/*
int representation[12][10] = 
{
	{1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 0, 1, 1, 0, 1, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 1, 0, 0, 0, 0, 1, 1, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 1, 0, 1, 1, 1},
	{0, 0, 1, 0, 1, 1, 0, 1, 1, 1}
};

int one;
int two;
for(one = 0; one < 12; one++)
{
	for(two = 0; two < 10; two++)
	{
		printf(" %d", representation[one][two]);
		if(two == 9)
			printf("\n");	
	}
}

*/