#include <string.h>
#include <stdlib.h>
#include "cli.h"

int *getDigits(AWKCommand *awk, char digits[]){
	char *token;
	awk->n_size = 0;
	awk->n = (int *)malloc(0 * sizeof(int));
	token = strtok(digits, "n");
	while(token != NULL){
		awk->n_size++;
		awk->n = (int *)realloc(awk->n, awk->n_size * sizeof(int));
		if(atoi(token) > 0) awk->n[awk->n_size - 1] = atoi(token) - 1;
		token = strtok(NULL, "n");
	}
	return awk->n;
}
int containDigit(AWKCommand awk, int digit){
	for(int i=0; i<awk.n_size; i++){
		if(awk.n[i] == digit) return 1;
	}
	return 0;
}
