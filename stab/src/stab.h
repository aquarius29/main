/*
 * @brief Interface for the stabilization code. It allows the \n 
 * different files to communicate with each other. \n
 * THIS IS NOT TO BE USED BY OTHER GROUPS 
 * @author Adam Debbiche
 */
#ifdef ARDUINO
#include "WProgram.h"
#endif
/*
 * Different functions are included depending on the mode 
 * (pc or arduino)
 */
#ifdef PC
float comp_filter(float acc_scal, float gyro_scal, float old_est);
float read_gyro();
float read_accel();
struct vector init_sim(void);
#elif ARDUINO
void init_gyro_hardware();
struct vector read_gyro_data();
void readAccel();
void read_stream(byte addr, int bytes_to_read, byte buffer[]);
#endif	


