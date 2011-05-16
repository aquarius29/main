/*
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
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
<<<<<<< HEAD
struct attitude sim_attitude(void);
struct vector sim_vector(void);
int sim_heading();
struct baro_data sim_baro(); 
#elif ARDUINO
float comp_filter(float acc_scal, float gyro_scal, float old_est);
void init_filter();
void init_gyro_hardware();
void init_magn_hardware();
struct vector read_gyro_data();
struct vector readAccel();
struct vector read_magn_data();
void read_stream(byte addr, int bytes_to_read, byte buffer[]);
void write_data(byte addr, byte value, byte sensor_addr);
void init_baro_hardware();
struct baro_data read_baro_data();
#endif	


=======
  Interface for the stabilization code. It allows the different files
  to communicate with each other.
  THIS IS NOT TO BE USED BY OTHER GROUPS 
*/

/*
  Reads data from accelerometer in the form of a vector (x, y, z)
*/
float read_accel();

/*
  Reads the data from the gyroscope in the form of a vector (x, y, z)
*/
float read_gyro();


/*
  Invokes the main function of the filter		
*/
float comp_filter(float acc_scal, float gyro_scal, float old_est);

/*
 Initializes the vector of the filter
 */
void init_filter();


/*
 Initializes the simulator 
*/
struct vector init_sim(void);

>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
#elif ARDUINO
void init_gyro_hardware();
struct vector read_gyro_data();
void readAccel();
void read_stream(byte addr, int bytes_to_read, byte buffer[]);
#endif	


>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
