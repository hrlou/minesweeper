#include "random.h"

#ifdef _WIN32

#define _CRT_RAND_S

#include <stdlib.h>
#include <limits.h>

unsigned int random_generate(unsigned int max) {
	unsigned int val;
	rand_s(&val);
	val = (unsigned int) (double) val / ((double) UINT_MAX + 1) * (double) (max + 1);
	return val;
}

#else

#include <stdio.h>

unsigned int random_generate(unsigned int max) {
	unsigned int val;
	FILE* f = fopen("/dev/urandom", "r");
	fread(&val, sizeof(unsigned int), 1, f);
	fclose(f);
	val = val % max;
	return val;
}

#endif