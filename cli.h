#ifndef CLI
#define CLI

#include <stdio.h>

typedef struct{
	FILE *source;
	FILE *dest;
	// Cualquier comando que tenga la estructura nd1nd2nd3... guardara los digitos en el array n
	int *n;
	size_t n_size;
} AWKCommand;

int *getDigits(AWKCommand *awk, char digits[]);
int containDigit(AWKCommand awk, int digit);

#endif
