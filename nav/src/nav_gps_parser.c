/*
 *@File:parser.c
 *
 *@Date:Created on: Mar 28, 2011
 *
 *@Author: Jianfeng Xie
 *
 *@Description: Decode NEMA data stream(RMC) from GPS receiver and filter them, only lat and lon
 *are returned, since other information is not needed
 *
 *
 */
#include "nav_gps_parser.h"


/* This function is to split data stream(RMC), and get different parts of them. we can
 * get utc_time, gps_status,lat N/S indicator,lon, E/W indicator and etc.
 *
 *@param char* buffer(RMC stream)
 *
 *@return struct rmc*,it stores all information getting from stream.
 *
 *
 */
struct rmc* split(char* buffer){
    char* parseptr;
    double temp;
    /*define and allocate structure for storing data*/
    struct rmc* data = malloc(sizeof(struct rmc));
    if (strncmp(buffer, "$GPRMC",6) == 0) {               /*confirm stream is RMC */
        data->id = "GPRMC";
        parseptr = buffer+7;
        temp=parse_decimal(parseptr);
        data->utc_time = temp;                            /* get time*/
        parseptr = strchr(parseptr, ',') + 1;
        data->status = parseptr[0];                       /*get status*/
        parseptr= parseptr+ 2;
        data->lat = parse_decimal(parseptr);              /*get latitude*/
        if (data->lat != 0) {
            parseptr = strchr(parseptr, '.')+1;
            data->lat += parse_decimal(parseptr)/10000;
        }
        parseptr = strchr(parseptr, ',') + 1;
        if (parseptr[0] != ',') {
            data->ns_indicator = parseptr[0];             /*get latitude N/S data*/
        }
        parseptr = parseptr+2;
        data->lon = parse_decimal(parseptr);
        if (data->lon != 0) {
            parseptr = strchr(parseptr, '.')+1;
	        data->lon += parse_decimal(parseptr)/10000;  /*get longitude*/
        }
        parseptr = strchr(parseptr, ',') + 1;
        if(parseptr[0] != ','){
            data->ew_indicator = parseptr[0];            /*get longitude E/W data*/
        }
        parseptr = strchr(parseptr, ',') + 1;
        data->speed = parse_decimal(parseptr);
        if (data->speed != 0) {                          /*get speed*/
            parseptr = strchr(parseptr, '.')+1;
            data->speed += parse_decimal(parseptr)/100;
        }

        parseptr = strchr(parseptr, ',') + 1;
        data->course = parse_decimal(parseptr);
        if (data->course != 0) {                         /*get angle/course*/
            parseptr = strchr(parseptr, '.')+1;
            data->course += parse_decimal(parseptr)/100;
        }

        parseptr = strchr(parseptr, ',') + 1;
        data->date = parse_decimal(parseptr);            /*get date*/

	}
	return data;
}

/* parse string of numbers into decimal, if string does not contain numbers, it returned 0;
 *
 *@param char* string
 *
 *@return decimal or 0;
 *
 */
double parse_decimal(char *str) {


  double d = 0;
  while (str[0] != 0) {
   /*if string does not contain numbers, reutrn 0*/
   if ((str[0] > '9') || (str[0] < '0'))
     return d;
   d *= 10;
   d += str[0] - '0';
   str++;
  }
  return d;
}

/* This fucntion can be directly called to parse NEMA RMC stream, and it returns
 * a pointer including lat and lon.
 *
 *@param: char* string
 *
 *@return: a position structure
 */
struct point* parser(char* buffer){
	/*define and allocate a pointer to store the splited information*/
	struct rmc* data = split(buffer);
	/*define and allocate a pointer to store lat and lon*/
	struct point* position = malloc(sizeof(struct point));

	position->name = 0;
	position->lat = data->lat;
    position->lon = data->lon;
    free(data);
    return position;

}

