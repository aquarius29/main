/*
 * @brief Interface for the stabilization code. It allows the \n 
 * different files to communicate with each other. \n
 * THIS IS NOT TO BE USED BY OTHER GROUPS 
 * @author Adam Debbiche
 */


/*
 * Different functions are included depending on the mode 
 * (pc or arduino)
 */
#if defined(PC) || defined(STAB)
float comp_filter(float acc_scal, float gyro_scal, float old_est);
float read_gyro();
float read_accel();
struct vector init_sim(void);
#elif ARDUINO
void init_gyro_hardware();
void read_gyro_data();
void readAccel();
#endif	


