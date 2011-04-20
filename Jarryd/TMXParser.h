/*
* @Author: Jarryd Hall
*/

xmlXPathObjectPtr retrieveXmlnodeset (xmlDocPtr doc, xmlChar *xpath);

void getMapDetails (xmlDocPtr doc, xmlNodePtr cur, ThreeDWorld *world);

void getTileDetails (xmlDocPtr doc, xmlNodePtr cur, ThreeDWorld *world);

char* getAttributeValueForNode 
(xmlDocPtr doc, xmlNodePtr cur, char *node, char *attribute);

void parseDoc(char *docname, ThreeDWorld *world) ;
