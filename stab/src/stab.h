/*
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

