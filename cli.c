#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "cli.h"

const char *token_cli = "CILSMmPn";

int *getDigits(AWKCommand *awk, char digits[]){
	char *token;
	awk->n_size = 0;
	awk->n = (int *)malloc(0 * sizeof(int));
	token = strtok(digits, token_cli);
	while(token != NULL){
		awk->n_size++;
		awk->n = (int *)realloc(awk->n, awk->n_size * sizeof(int));
		if(atoi(token) > 0) awk->n[awk->n_size - 1] = atoi(token) - 1;
		token = strtok(NULL, token_cli);
	}
	return awk->n;
}
int containDigit(AWKCommand awk, int digit){
	for(int i=0; i<awk.n_size; i++){
		if(awk.n[i] == digit) return 1;
	}
	return 0;
}
int openSource(AWKCommand *awk, char *filename){
	FILE *source;
	source = fopen(filename, "r");
	if(source == NULL){
		printf("Error: No se pudo abrir el archivo %s.\n", filename);
		exit(1);
	}
	awk->source = source;
	return 0;
}
int openDest(AWKCommand *awk, char *argv[], int argc, int minsize){
	FILE *dest;
	if(argc<minsize)
		dest = stdout;
	else
		dest = fopen(argv[argc-1], "w");
	if(dest == NULL){
		printf("Error: No se pudo abrir el archivo de destino.\n");
		exit(1);
	}
	awk->dest = dest;
	return 0;
}
int destroyCommand(AWKCommand *awk){
	fclose(awk->source);
	if(awk->dest != NULL)
		fclose(awk->dest);
	free(awk->command);
	free(awk->source);
	free(awk->dest);
	free(awk->n);
	return 1;
}
