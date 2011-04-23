/*
* @Author: Jarryd Hall
* @Purpose: Tilemap representation
*/

#include <stdlib.h>
#include "tilemap.h"

/* function to take coordinates and determine the tile index */
CGPoint* tileForCoordinates (CGPoint position, short width, short height)
{	
	CGPoint *tileCoordinate = (CGPoint*)malloc(sizeof(CGPoint));
	tileCoordinate->xPosition = (position.xPosition / width);
	tileCoordinate->yPosition = (position.yPosition / height);
	
	return tileCoordinate;
}

/* modify world represnetation set the index to value e.g. 1 or 0 */
void setIndexValue(ThreeDWorld *world, int index, int value)
{
	int first = index / world->mapWidth;
	int second =  index % world->mapWidth;
	world->representation[first][second] = value; 
}

/* check a tile for its contents */
int checkTileValue(ThreeDWorld *world, int index)
{
	int value = NULL; /* value for tile e.g. 0 = free, 1 = collision 2 = destination */
	int first = index / world->mapWidth;
	int second =  index % world->mapWidth;
	
	value = world->representation[first][second];
	
	return value;
}
/* TODO: Create this function to be reusable for adding items to an array */
/*
int AddItemToArray ()
{
	
}
*/

/*
// check diagram on git: filename = tileImage2.png
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

*/