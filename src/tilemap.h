/*
* @Author: Jarryd Hall
*/

#ifndef TILEMAP_H
#define TILEMAP_H

typedef struct
{
    /* Height for the room is 3m */
    
	short mapWidth; /* number of tiles | note: not number of pixels */
	short mapHeight; /* number of tiles | note: not number of pixels */
	short tileWidth; /* size in pixels */
	short tileHeight; /* size in pixels */
	short numberOfTilesInMap; /* number of tiles in tile-map */
	short worldHeight; /* height for the room */
	int **representation; /* 2d array of the representation */
} 
ThreeDWorld;

typedef struct
{
	int xPosition;
	int yPosition;
	
} 
CGPoint;

CGPoint* tileForCoordinates (CGPoint position, short width, short height); /* determine the tile index */

void setIndexValue(ThreeDWorld *world, int index, int value); /* modify world represnetation set the index to value e.g. 1 or 0 */
int checkTileValue(ThreeDWorld *world, int index); /* check a tile for its contents e.g. 0 = free, 1 = collision, 2 = destination */
void fill_map(ThreeDWorld * world);

#endif /* TILEMAP_H */
