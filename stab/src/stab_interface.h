#include <stdint.h>
/*
 *  @brief Header file used as an interface for the scheduler
 *  @history Adam Debbiche
 */


/*
 * Called by the scheduler to init the hardware and filter of
 * the stabilization module
 */

int16_t stab_init(void);

/*
 * Called by the scheduler to run the code of stabilization 	
 */
int16_t stab_run(void);
