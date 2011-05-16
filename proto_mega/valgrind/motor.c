#include <stdio.h>
#include "proto_lib.h"

int motor(void){
	printf("Motor read #%d#\n", proto_read_motor2()->message1);
	createDefaultmove();
	printf("Motor wrote\n");
	return 1;
	}

