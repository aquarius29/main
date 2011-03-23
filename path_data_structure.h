#define MAX_PATH_LENGTH 100

typedef struct {
	double lat;
	double lon;
} position;
	
typedef struct {
	position starting_point;
	position destination_point;
	position current_point;
	position *turns;
} path;
