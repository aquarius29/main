#include <stdint.h>
/*
 *  Header file used as an interface for the scheduler
 *  Author: Adam Debbiche
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
