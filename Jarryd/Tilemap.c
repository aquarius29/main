/*
* Author: Jarryd Hall
* Purpose: Tilemap representation
*/

typedef struct
{
    // Height for the room is 3m 
    
	short mapWidth; // number of tiles | note: not number of pixels
	short mapHeight; // number of tiles | note: not number of pixels
	short tileWidth; // size in pixels
	short tileHeight; // size in pixels
	short numberOfTilesInMap; // number of tiles in tile-map
	short numberOfColumns; // number of columns in map width
	short numberOfRows; // number of rows in map height
	short margin; // pixels to skip for current tile before looking for pixels
	short spacing; // pixels to advance to the next tile data
	short worldHeight; // height for the room
} 
ThreeDWorld;

typedef struct
{
	int xPosition;
	int yPosition;
	
} 
CGPoint;

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