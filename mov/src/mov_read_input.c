#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data {
	char *type;
	char *order;
	int height;
	int distance;
	int yaw;
	int pitch;
	int roll;
	int speed;
//	int gyro[3];
	int gyrox;
	int gyroy;
	int gyroz;
};

int main (int argc, char **argv) {
	FILE *output;
	char line[50];
	char *label;
	char *name;
	char *z;
	int x[3];
	struct data *d = (struct data*) malloc(sizeof(struct data));

  while(fgets(line, sizeof(line), stdin) != NULL ) {
	label = strtok(line, ": ");
	name = strtok(NULL, "\n");
	
	if((strcmp(label, "TYPE")) == 0){
		d->type = (char *)malloc(20);
		strcpy(d->type, name);
		printf("\n%s: %s\n", label, d->type);
	}
	else if((strcmp(label, "ORDER")) == 0){
		d->order = (char *)malloc(20);
		strcpy(d->order, name);
		printf("%s: %s\n", label, d->order);
	}
	else if((strcmp(label, "HEIGHT")) == 0){
			d->height = atoi(name);
			printf("%s: %d\n", label, d->height);
	}
	else if((strcmp(label, "DISTANCE")) == 0){
			d->distance = atoi(name);
			printf("%s: %d\n", label, d->distance);
	}
	else if((strcmp(label, "YAW")) == 0){
			d->yaw = atoi(name);
			printf("%s: %d\n", label, d->yaw);
	}
	else if((strcmp(label, "PITCH")) == 0){
			d->pitch = atoi(name);
			printf("%s: %d\n", label, d->pitch);
	}
	else if((strcmp(label, "ROLL")) == 0){
			d->roll = atoi(name);
			printf("%s: %d\n", label, d->roll);
	}
	else if((strcmp(label, "SPEED")) == 0){
			d->speed = atoi(name);
			printf("%s: %d\n", label, d->speed);
	}
	else if((strcmp(label, "GYROx")) == 0){
			d->gyrox = atoi(name);
			printf("%s: %d\n", label, d->gyrox);
	}
	else if((strcmp(label, "GYROy")) == 0){
			d->gyroy = atoi(name);
			printf("%s: %d\n", label, d->gyroy);
	}
	else if((strcmp(label, "GYROz")) == 0){
			d->gyroz = atoi(name);
			printf("%s: %d\n", label, d->gyroz);
	}
/*
	else if((strcmp(label, "GYRO")) == 0){
		d->gyro = (char *)malloc(20);
		strcpy(d->gyro, name);
		x = atoi(strtok(d->gyro, ","));
		z = strtok(NULL, "\n");
		printf("\n%s: %s\n our crap: %d %d %s\n", label, d->gyro, x[0], x[1], z);
//			d->gyro[0] = atoi(name);
//			xyz = strtok(line, ",");
//			d->gyro[1] = atoi(xyz);
//			printf("%s: %d %d %d\n", label, d->gyro[0], d->gyro[1], d->gyro[2]);
	}*/
}
	free((void *)d);
	return 0;
}
