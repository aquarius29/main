/*!
* @author 	Jarryd Hall.
* @brief	Tilemap representation which holds the map of the indoor flight area.
*/

#include <stdlib.h>
#include "nav_tilemap.h"

//! function to take coordinates and determine the tile index
/*! Return the tile for the passed in coordinates.
*
* @param position The (x, y) position of the tile.
* @param width The tile width.
* @param height The tile height.
*
* @return CGPoint tileCoordinate.
*/
CGPoint* tileForCoordinates (CGPoint position, short width, short height)
{	
	CGPoint *tileCoordinate = malloc(sizeof(CGPoint));
	tileCoordinate->xPosition = (position.xPosition / width);
	tileCoordinate->yPosition = (position.yPosition / height);
	
	return tileCoordinate;
}

//! modify world represnetation set the index to value e.g. 1 or 0.
/*! Function to set a tile to a specific value.
* e.g mark a tile as free or collidable.
*
* @param world The ThreeDWorld to search.
* @param index the index of the tile.
*/
void setIndexValue(ThreeDWorld *world, int index, int value)
{
	int first = index / world->mapWidth;
	int second =  index % world->mapWidth;
	world->representation[first][second] = value; 
}

//! check a tile for its contents.
/*! Used to get the value of the requesed tile.
*
* @param world The ThreeDWorld to search.
* @param index the index of the tile.
*/
int checkTileValue(ThreeDWorld *world, int index)
{
	int value = 0; /* value for tile e.g. 0 = free, 1 = collision 2 = destination */
	int first = index / world->mapWidth;
	int second =  index % world->mapWidth;
	
	value = world->representation[first][second];
	
	return value;
}

/*
/* The actual representation of the indoor square */ 
/* check diagram on git: filename = tileImage2.png */
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
*/