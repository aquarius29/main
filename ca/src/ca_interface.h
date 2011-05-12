/*!
 * @file:         ca_interface.h
 * @brief:
 * @author:       Yanling Jin, Amber Olsson
 * @date:         2011-04-26
 * @version:      0.1
 * @history       2011-03-30 create the file
 * @detail:
 */
#include <stdint.h> 

/* ca_interface.c */
int16_t ca_init(void);
int16_t ca_run(void);
uint8_t get_dir(void);
void write_to_move(uint8_t direction);

/* ca_logic.c */
#ifdef ARDUINO
uint8_t direction_filter(void);
#elif defined PC
uint8_t direction_filter(uint16_t ir1, uint16_t ir2, uint16_t ir3, uint16_t ir4,
					 uint16_t ir11, uint16_t ir22, uint16_t ir33, uint16_t ir44);
#endif 


 /* ca_filters.c */ 
uint16_t speed_filter( uint16_t speed);
uint8_t * distance_filter( uint16_t dangerzone,
						   uint16_t ir1, uint16_t ir2,
						   uint16_t ir3, uint16_t ir4);
uint8_t * ir_filter(uint8_t *irs);
uint8_t *currentDirection_filter(uint8_t currentDirection,
									  uint8_t*directions);
uint8_t *moving_closer_filter(uint8_t *is_moving, 
									uint8_t*directions);
uint8_t final_direction(uint8_t currentDir, uint8_t *directions);


 /* ca_prints.c */ 
char * translate(uint8_t i);
void outputIR(uint8_t *result);
void outputdirection(uint8_t direction);
void print_result(uint8_t *result);
void print_speed_dangerzone(uint16_t speed, uint16_t dangerzone);
void print_dangerzone_ir(uint8_t *irBooleans);
void print_result_after_dangerzone(uint8_t *result);
void print_result_after_flying_dir(uint8_t dir,uint8_t *result);
void print_movingCloser_ir(uint8_t *moving_close);
void print_result_after_movingCloser(uint8_t *result);
void print_final_result(uint8_t *result);
void print_final_direction(uint8_t finalDir);

/* ca_object_calculations.c */
int16_t *distance_differ(uint16_t ir1, uint16_t ir2, uint16_t ir3, uint16_t ir4,
					 uint16_t ir11, uint16_t ir22, uint16_t ir33, uint16_t ir44);
uint8_t * moving_closer (int16_t * irDistances);



/* ca_sensors.c */ 
uint16_t ir_distance(uint8_t irpin);
