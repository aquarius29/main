struct point
{
	char name;
	double lat;
	double lon;
};

struct link
{
	char from;
	char to;
	double distance;
	struct link *last;
};

struct trac
{
	char p;
	struct trac *last;
};


struct dist
{
	char name;
	double distance;
};


