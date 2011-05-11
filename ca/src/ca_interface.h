/*
 * file:         ca_interface.h
 * brief:
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-30 create the file
 * detail:
 */
#include <stdint.h> 

/* ca_interface.c */
#ifdef ARDUINO
int16_t ca_init(void);
int16_t ca_run(void);
#elif defined PC
int16_t ca_init(void);
int16_t ca_run(void);
#endif 

int8_t get_dir(void);
void write_to_move(int direction);

/* ca_logic.c */
#ifdef ARDUINO
int direction_filter(void);
#elif defined PC
int direction_filter(int ir1, int ir2, int ir3, int ir4,
					 int ir11, int ir22, int ir33, int ir44);
#endif 

 /* ca_filters.c */ 
int speed_filter(int speed);
unsigned char* distance_filter(int dangerzone,int ir1, int ir2, int ir3,int ir4);
unsigned char* ir_filter(unsigned char *irs);
unsigned char *currentDirection_filter(int currentDirection,unsigned char *directions);
unsigned char *moving_closer_filter(unsigned char *is_moving, unsigned char*directions);
int final_direction(int currentDir, unsigned char *directions);

 /* ca_prints.c */ 
char * translate(int i);
void outputIR(unsigned char *result);
void outputdirection(int direction);
void print_result(unsigned char *result);

/* ca_object_calculations.c */
int *distance_differ(int ir1, int ir2, int ir3, int ir4, 
					 int ir11, int ir22, int ir33, int ir44);
unsigned char* moving_closer (int * irDistances);

/* ca_sensors.c */ 
#ifdef ARDUINO
int ir_distance(int irpin);
#endif
