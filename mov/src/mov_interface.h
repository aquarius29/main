/*!
 * @file:         mov_interface.h
 * @brief:
 * @author:       Yanling Jin, Amber Olsson
 * @date:         2011-05-10
 * @version:      0.1
 * @history      
 *
 * @detail:
 */

#include <stdio.h>
#include <stdint.h>

struct nav
{
	uint8_t type;
	uint8_t order; 
	int16_t height;
	int16_t distance;
	int16_t yaw;
};

struct sensor
{
	uint16_t pitch;
	int16_t roll;
	int16_t yaw;
	int16_t height;
};

/*mov_logic.c*/
void command_logic(void);
void hoverCommand(void);
void moveCommand (void);
void landCommand(void);
void check_height(void);
void check_heading(void);
void check_pitch_roll(uint8_t isHovering);
void updateDistanceToTravel(void);
void check_changingAltitude(void);
void doCa(void);
void printOrientation(void);
void convertCommand(void);

/*mov_motor.c*/
void start_motors(void);
void stop_motors(void);
void increase_rear_motor(void);
void decrease_rear_motor(void);
void increase_front_motor(void);
void decrease_front_motor(void);
void increase_left_motor(void);
void decrease_left_motor(void);
void increase_right_motor(void);
void decrease_right_motor(void);
void increase_rear_decrease_front(void);
void increase_front_decrease_rear(void);
void increase_left_decrease_right(void);
void increase_right_decrease_left(void);
void increase_all(void);
void decrease_all(void);
void hover(void);
void go_forwards(void);
void go_backwards(void);
void strafe_left(void);
void strafe_right(void);
void turn_left(void);
void turn_right(void);
void land(void);

uint8_t to_MotorMessage(uint8_t ID0, uint8_t ID1, uint8_t increasing,uint8_t panicMode, 
						uint8_t motor1,uint8_t motor2, uint8_t motor3, uint8_t motor4);
void pWrite(uint8_t msg);
void print_uint8_t_to_Binary(uint8_t bin);



/*mov_simulator.c*/
uint8_t read_command(void);
uint8_t get_loc(char line[],char c,uint8_t indexOfColumn);
void assignValue(uint8_t index,char *temp);
int16_t do_sensor_simulation(int16_t currentSensorValue, uint8_t command);


/*mov_interface.c*/
int16_t mov_init(void);
int16_t mov_run(void);
void read_navCommand(void);
void read_caCommand(void);
void write_to_motor(uint8_t msg);
void send_dir_to_ca(uint8_t dir);
void read_sensorCommand(void);
void clear_message_array(void);
void write_array(void);

/*mov_sensor.c*/
uint16_t sonar_distance(uint8_t sonarPin);
