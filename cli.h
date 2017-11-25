#ifndef CLI
#define CLI

#include <stdio.h>

typedef struct{
	char *command;
	FILE *source;
	FILE *dest;
	// Cualquier comando que tenga la estructura nd1nd2nd3... guardara los digitos en el array n
	int *n;
	size_t n_size;
} AWKCommand;

int parseCommand(AWKCommand *awk, char digits[]);
int containDigit(AWKCommand awk, int digit);
AWKCommand createCommand(int argc, char *argv[]);
int *getDigits(AWKCommand *awk, char digits[]);
int destroyCommand(AWKCommand *awk);
int openSource(AWKCommand *awk, char *filename);
int openDest(AWKCommand *awk, char *argv[], int argc, int minsize);
int getFlags(AWKCommand *awk, char *argv[], int argc, int init);

#endif
