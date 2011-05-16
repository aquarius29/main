#include <stdio.h>
#include "proto_lib.h"

int stab(void){
    printf("stab wrote \n");
	proto_write_motor2(0xB, 0xB, 0xB, 0xB, 0xB, 0xB, 0xB, 0xB);
	return 1;
	}

