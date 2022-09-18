#pragma once
#include <stdlib.h>
#include <time.h>

#define KNRM		"\x1B[0m"
#define KBOLD		"\x1B[1m"
#define KFAINT		"\x1B[2m"
#define KITALIC		"\x1B[3m"
#define KUNDERLINE	"\x1B[4m"

//#define KRED		"\x1B[31m"
//#define KGRN		"\x1B[32m"
//#define KYEL		"\x1B[33m"
//#define KBLU		"\x1B[34m"
//#define KMAG		"\x1B[35m"
//#define KCYN		"\x1B[36m"

#define KWHITE		"\x1B[37m"
#define KRED		"\x1B[38;2;255;0;0m"
#define KGREEN		"\x1B[38;2;0;255;0m"
#define KBLUE		"\x1B[36m"

#define KDORANGE	"\x1B[38;2;255;128;0m"
#define KROSE		"\x1B[38;2;255;0;128m"
#define KMINT		"\x1B[38;2;0;255;128m"
#define KGRASS		"\x1B[38;2;128;255;0m"
#define KOCEAN		"\x1B[38;2;0;128;255m"
#define KPLUM		"\x1B[38;2;128;0;128m"

#define KCYAN		"\x1B[38;2;0;255;255m"
#define KMAGENTA	"\x1B[38;2;255;0;255m"
#define KYELLOW		"\x1B[38;2;255;255;0m"

#define KVIOLET		"\x1B[38;2;128;128;255m"
#define KLORANGE	"\x1B[38;2;255;128;128m"
#define KLIME		"\x1B[38;2;128;255;128m"

#define KICE		"\x1B[38;2;128;255;255m"
#define KPINK		"\x1B[38;2;255;128;255m"
#define KBUTTER		"\x1B[38;2;255;255;128m"

// list of custom colors
static char * colors[19] = { KWHITE, 
	KRED, KGREEN, KBLUE, KDORANGE, KROSE, KMINT,
	KGRASS, KOCEAN, KPLUM, KCYAN, KMAGENTA, KYELLOW,
	KVIOLET, KLORANGE, KLIME, KICE, KPINK, KBUTTER
};

// returns a string which represents random color
inline char * randomcolor() {
	int num = rand() % 19;
	return colors[num];
}
