#define NO_PROCESSES 4

typedef int16_t(*sched_Fun_t)(void);

int16_t profile_mov(void);
int16_t profile_stab(void);
int16_t profile_ca(void);
int16_t profile_moto(void);

int16_t profile_init(void);
int16_t profile_main(void);
