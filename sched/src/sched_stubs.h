#include <stdint.h>


#ifdef CA
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t ca_init(void);
/* dummy interface for stabilization code */
int16_t ca_run(void);

#endif /* CA */


#ifdef STAB
/* stabilization groups header here */
#include "../../stab/src/stab_sched.h"

#else

/* dummy interface for stabilization code */
int16_t stab_init(void);
/* dummy interface for stabilization code */
int16_t stab_run(void);

#endif /* STAB */


#ifdef MOVE
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t move_init(void);
/* dummy interface for stabilization code */
int16_t move_run(void);

#endif /* MOVE */


#ifdef MOTO
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t moto_init(void);
/* dummy interface for stabilization code */
int16_t moto_run(void);

#endif /* MOTO */


#ifdef PROTO
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t proto_init(void);
/* dummy interface for stabilization code */
int16_t proto_run(void);

#endif /* PROTO */


#ifdef FILTER
/* stabilization groups header here */
/* #include "../../ca/src/ca_sched.h" */

#else

/* dummy interface for stabilization code */
int16_t filter_init(void);
/* dummy interface for stabilization code */
int16_t filter_run(void);

#endif /* FILTER */


