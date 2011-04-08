/*

	Author: Qiushi Wang
	Date:   2011.3.30

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NS 1	/* north = 0, south = 1 */
#define EW 1	/* east = 0, west = 1*/	

#define GLL "$GPGLL,"
#define RMC "$GPRMC,"

static int Num_info = 0 ;

int get_random();

char* get_gll(char *buf);

char *get_rmc(char *buf);

char *get_gga(char *buf);

char *get_gsa(char *buf);

char *get_gsv(char *buf);

char *get_vtg(char *buf);

char *read_info(char *buf);
