/*

	Author: Qiushi Wang
	Date:   2011.3.30

*/

#include "signal_simulator.h"


int get_random(){
	int i;
	srand((unsigned)time(NULL)); 
	i = rand()%10; 
	return i;
}





char* get_gll(char *buf){
	
	Num_info = 2;

	char* lat [10] =	{"5742.6090,","5742.6120,","5742.6150,","5742.6170,","5742.6190,","5742.6210,","5745.6230,","5742.6250,","5742.6270,","5742.6330,"};
	
	char* lon [10] = {"1155.2010,","1155.2021,","1155.2030,","1155.2040,","1155.2050,","1155.2060,","1155.2070,","1155.202080,","1155.2090,","1155.2100,"};

	char* UTC = "053740.000,";

	char N_S,E_W;

	char *A_V = "A,",*Mode = "A";

	char *checksum = "*52";

	buf = strcpy(buf,GLL);

	buf = strcat(buf,lat [get_random()]);

	buf = strcat(buf,"N,");

	buf = strcat(buf,lon [get_random()]);

	buf = strcat(buf,"E,");

	buf = strcat(buf,UTC);

	buf = strcat(buf,A_V);

	buf = strcat(buf,Mode);

	buf = strcat(buf,checksum);

	printf("got one GLL output\n");

	return buf;
}





char *get_rmc(char *buf){

	Num_info = 5;

	char* lat [10] =	{"5742.6090,","5742.6120,","5742.6150,","5742.6170,","5742.6190,","5742.6210,","5745.6230,","5742.6250,","5742.6270,","5742.6330,"};
	
	char* lon [10] = {"1155.2010,","1155.2021,","1155.2030,","1155.2040,","1155.2050,","1155.2060,","1155.2070,","1155.202080,","1155.2090,","1155.2100,"};

	char* gspeed [10] = {"0.01,","1.12,","2.04,","3.22,","4.45,","5.57,","6.13,","7.99,","25.48,","32.11,"};

	char* cog [10] = {"12.45,","33.33,","226.22,","11.11,","123.22,","455.56,","889.88,","1.01,","66.78,","122.55,"}; 

	char* UTC = "053740.000,";

	char *A_V = "A,";

	char *date = "110401,";

	char *MV = ",";

	char *VS = ",";

	char *Mode = "A";

	char *checksum = "*53";

	buf = strcpy(buf,RMC);

	buf = strcat(buf,UTC);

	buf = strcat(buf,A_V);

	buf = strcat(buf,lat [get_random()]);
	
	buf = strcat(buf,"N,");

	buf = strcat(buf,lon [get_random()]);

	buf = strcat(buf,"E,");

	buf = strcat(buf,gspeed [get_random()]);

	buf = strcat(buf,cog [get_random()]);

	buf = strcat(buf,date);

	buf = strcat(buf,MV);

	buf = strcat(buf,VS);

	buf = strcat(buf,Mode);

	buf = strcat(buf,checksum);

	printf("got one RMC output : ");

	return buf;
	
}







char *get_gga(char *buf){

	Num_info = 1;

	buf = strcpy(buf,"$GPGGA,053740.000,2503.6319,N,12136.0099,E,1,08,1.1,63.8,M,15.2,M,,0000*64");

	printf("got one GGA output\n");

	return buf;	

}







char *get_gsa(char *buf){

	Num_info = 3;

	buf = strcpy(buf,"$GPGSA,A,3,24,07,17,11,28,08,20,04,,,,,2.0,1.1,1.7*35");

	printf("got one GSA output\n");

	return buf;	
}






char *get_gsv(char *buf){

	Num_info = 4;

	buf = strcpy(buf,"$GPGSV,3,2,12,17,41,328,45,07,32,315,45,04,31,250,40,11,25,046,41*75");

	printf("got one GSV output\n");

	return buf;	
}





char *get_vtg(char *buf){

	Num_info = 0;

	buf = strcpy(buf,"$GPVTG,79.65,T,,M,2.69,N,5.0,K,A*38");

	printf("got one VTG output\n");

	return buf;	
}






char *read_info(char *buf){

	if(Num_info == 0)
	return get_gga(buf);

	if(Num_info == 1)
	return get_gll(buf);

	if(Num_info == 2)
	return get_gsa(buf);

	if(Num_info == 3)
	return get_gsv(buf);

	if(Num_info == 4)
	return get_rmc(buf);

	if(Num_info == 5)
	return get_vtg(buf);
}



/*
int main(){

	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());

	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());
	printf("%s\n",read_info());

	return 0;

} */
