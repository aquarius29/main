/*
  Interface for the stabilization code. It allows the different files
  to communicate with each other.
  THIS IS NOT TO BE USED BY OTHER GROUPS 
*/


/*
 Different functions are included depending on the mode 
 (pc or arduino)
*/
#ifdef ARDUINO
void init_gyro_hardware();
void read_gyro_data();
void readAccel();
#elif PC 
float comp_filter(float acc_scal, float gyro_scal, float old_est);
float read_gyro();
float read_accel();
struct vector init_sim(void);
#endif	


