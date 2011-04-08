#include <stdint.h>

/* dummy int16_terface for collision avoidance code */
int16_t caRun(void);

#ifdef STAB
/* stabilization groups header here */
#include "../../stab/src/stab_sched.h"

#else

/* dummy int16_terface for stabilization code */
int16_t stab_init(void);
/* dummy int16_terface for stabilization code */
int16_t stab_run(void);

#endif /* STAB */

/* dummy int16_terface for movement code */
int16_t moveRun(void);

/* dummy int16_terface for motor code */
int16_t motoRun(void);

/* dummy int16_terface for protocol code */
int16_t protoRun(void);

/* dummy int16_terface for filter code */
int16_t filterRun(void);

/* dummy int16_terface for collision avoidance code */
int16_t caInit(void);

/* dummy int16_terface for movement code */
int16_t moveInit(void);

/* dummy int16_terface for motor code */
int16_t motoInit(void);

/* dummy int16_terface for protocol code */
int16_t protoInit(void);

/* dummy int16_terface for filter code */
int16_t filterInit(void);
