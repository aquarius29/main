/*
* @author Jarryd Hall.
* @brief An XML Parser to parse a tilemap.
* @details This module has been used to parse a tmx file.
* It uses a combination of xpath and DOM tree traversal.
* xpath is using regex to extract certain data.
* DOM is used to traverse the document tree model and extract the data needed.
* CommandLine usage: gcc source.c -I/usr/include/libxml2 -lxml2 -o output
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include "tilemap.h"

//! Retrieve the xml node set.
/*!
* Function that is used to read the xml doc and 
* retrieve the document's xml node set.
*
* @param doc A pointer to the document to be read.
* @param xpath An xml character defined in the libxml library.
*/
xmlXPathObjectPtr retrieveXmlnodeset (xmlDocPtr doc, xmlChar *xpath)
{
	xmlXPathContextPtr context;
	xmlXPathObjectPtr object;

	context = xmlXPathNewContext(doc);
	if (context == NULL) 
	{
		printf("xmlXPathNewContext error\n");
		return NULL;
	}
	object = xmlXPathEvalExpression(xpath, context);
	xmlXPathFreeContext(context);
	
	if (object == NULL) 
	{
		printf("xmlXPathEvalExpression error\n");
		return NULL;
	}
	if (xmlXPathNodeSetIsEmpty(object->nodesetval))
	{
		xmlXPathFreeObject(object);
		printf("xmlXPathObject couldnt be created\n");
		return NULL;
	}
	return object;
}

//! Get the map info from the tmx file.
/*!
* Get the info from the tmx file such as the map's width and height in tile amount
* the size of a single tile in pixel value.
*
* @param doc A pointer to the document to be read.
* @param cur A pointer to the current node in the tree
* @param world A pointer to a world object that is the representation of the map.
*
*/
void getMapDetails (xmlDocPtr doc, xmlNodePtr cur, ThreeDWorld *world)
{
	xmlChar *mapWidth;
	xmlChar *mapHeight;
	xmlChar *tileWidth;
	xmlChar *tileHeight;
	
	if((!xmlStrcmp(cur->name, (const xmlChar *)"map")))
	{
		mapWidth = xmlGetProp(cur, "width");
		int mw = atoi(mapWidth);
		world->mapWidth = mw;
		
		mapHeight = xmlGetProp(cur, "height");
		int mh = atoi(mapHeight);
		world->mapHeight = mh;
		
		tileWidth = xmlGetProp(cur, "tilewidth");
		int tw = atoi(tileWidth);
		world->tileWidth = tw;
		
		tileHeight = xmlGetProp(cur, "tileheight");
		int th = atoi(tileHeight);
		world->tileHeight = th;
	}
	
	int mapH = atoi(mapHeight);
	int mapW = atoi(mapWidth);
	world->representation = malloc(sizeof(int *) * mapH);
	int i;
	for (i = 0; i < mapH; i++ )
	{
		world->representation[i] = malloc(sizeof(int) * mapW);
	}
}

//! Create the 2d array from the extracted data array.
/*!
* Fill a ThreeDWorld with the data extracted from the tmx file.
*
*@param world Pointer to the ThreeDWorld to fill.
*@param w Width of the map.
*@param h Height of the map. 
@param array The array holding all the tiles.
*/
void createTwoDArray(ThreeDWorld *world, int w, int h, int array[])
{
	int one;
	int two;
	int arrayCounter = 0;
	
	for(one = 0; one < h; one++)
	{
		for(two = 0; two < w; two++)
		{
			world->representation[one][two] = array[arrayCounter];
            printf("  %d", world->representation[one][two]);
		
			if(two == 9)
				printf("\n");
					
			arrayCounter++;
		}
	}
}

//! Extract the data for each tile.

/*! A function to return all the tiles and their type. 
* This function creates the tilemap array on the fly
*
* @param doc A pointer to the document to be read.
* @param cur A pointer to the current node in the tree
* @param world A pointer to a world object that is the representation of the map.
*/
void getTileDetails (xmlDocPtr doc, xmlNodePtr cur, ThreeDWorld *world)
{
	xmlChar *xpath = (xmlChar*) "//layer[@name=\"collision\"]/data/tile/@gid";
	xmlNodeSetPtr nodeset;
	xmlXPathObjectPtr result;

	xmlChar *keyword;

	int width = world->mapWidth;
	int height = world->mapHeight;
	int i;
	int numMovableTiles = 0;
	int numCollisionTiles = 0;
	int totalTiles = 0;
	int tileValuesArray [width * height]; 
	int arrayCounter = 0;
	
	result = retrieveXmlnodeset (doc, xpath);
	if (result) 
	{
		nodeset = result->nodesetval;
		for (i=0; i < nodeset->nodeNr; i++) 
		{
			keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
		
			int id = atoi(keyword);
			int index = i;
			
			if (id == 0)
			{
				tileValuesArray[arrayCounter] = 0;
				arrayCounter++;
				numMovableTiles += 1;
			}
			if (id != 0)
			{
				tileValuesArray[arrayCounter] = 1;
				arrayCounter++;
				numCollisionTiles += 1;
			}
			 		
			xmlFree(keyword);
		}
		xmlXPathFreeObject (result);
	}
	
	totalTiles = numMovableTiles + numCollisionTiles;
	
	printf("number of collision tiles : %d\n", numCollisionTiles);
	printf("number of movable tiles : %d\n", numMovableTiles);
	printf("Total tiles : %d\n", totalTiles);
	world->numberOfTilesInMap = totalTiles;
	
	createTwoDArray(world, width, height, tileValuesArray);
	//world->height = 
}

/* Helper function to retrieve a the value for the specfied attribute at a specified node */
//!
/*!
*
*
*
*
*
*/
char* getAttributeValueForNode (xmlDocPtr doc, xmlNodePtr cur, char *node, char *attribute)
{
	xmlChar *attributeValue;
	cur = cur->xmlChildrenNode;
	
	while (cur != NULL)
	{
		if((!xmlStrcmp(cur->name, (const xmlChar *) node)))
		{
			attributeValue = xmlGetProp(cur, attribute);
			printf("node: %s value: %s\n", node, attributeValue);
		}
		cur = cur->next;
	}
	//xmlFree(attributeValue);
	return (char *)attributeValue;
}

/* TODO: Add functions to return all the data in a struct. */
//!
/*!
*
*
*
*
*
*/
void parseDoc(char *docname, ThreeDWorld *world) 
{
	xmlDocPtr doc;
	xmlNodePtr cur;

	doc = xmlParseFile(docname);
	
	if (doc == NULL) 
	{
		fprintf(stderr,"Parsing was unsuccesful \n");
		return;
	}
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) 
	{
		fprintf(stderr,"No XML Data\n");
		xmlFreeDoc(doc);
		return;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "map"))
	{
		fprintf(stderr,"Root node != map, not a tmx file\n");
		xmlFreeDoc(doc);
		return;
	}
	
	getMapDetails(doc, cur, world);
	getTileDetails(doc, cur, world);

	xmlFreeDoc(doc);
	return;
}

//!
/*!
*
*
*
*
*
*/
void fill_map(ThreeDWorld * world) {
	char *doc = "secondYearSquare.xml";
	parseDoc(doc, world);
}