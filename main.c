#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "awk.h"
#include "cli.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	if(argc<=1){
		puts("Error: comando no especificado.");
		return 1;
	}
	if(strcmp(argv[1], "--help") == 0){
		help(argv[0]);
		return 0;
	}
	AWKCommand awk;
	openSource(&awk, argv[1]);
	
	if(strcmp(argv[2], "SmM") == 0){
		awk.command = "SmM";
		openDest(&awk, argv, argc, 4);
		SmM(awk);
	}
	else if(strcmp(argv[2], "SMm") == 0){
		awk.command = "SMm";
		openDest(&awk, argv, argc, 4);
		SMm(awk);
	}
	else if(substring(argv[2], "IL")){
		awk.command = "IL";
		openDest(&awk, argv, argc, 4);
		getDigits(&awk, argv[2]);
		IL(awk);
	}
	else if(substring(argv[2], "IC")){
		awk.command = "IC";
		openDest(&awk, argv, argc, 4);
		getDigits(&awk, argv[2]);
		IC(awk);
	}
	else if(strcmp(argv[2], "INC") == 0){
		awk.command = "INC";
		openDest(&awk, argv, argc, 4);
		INC(awk);
	}
	else if(strcmp(argv[2], "CC") == 0){
		awk.command = "CC";
		if(argc<4){
			printf("\"%s\" esperaba mas argumentos.\nPara mas ayuda ejecuta '%s --help'\n", argv[2], argv[0]);
			return 1;
		}
		CC(awk, argv[3]);
	}
	else if(strcmp(argv[2], "CP") == 0){
		awk.command = "CP";
		if(argc<4){
			printf("\"%s\" esperaba mas argumentos.\nPara mas ayuda ejecuta '%s --help'\n", argv[2], argv[0]);
			return 1;
		}
		CP(awk, argv[3]);
	}
	else if(strcmp(argv[2], "CS") == 0){
		awk.command = "CS";
		if(argc<4){
			printf("\"%s\" esperaba mas argumentos.\nPara mas ayuda ejecuta '%s --help'\n", argv[2], argv[0]);
			return 1;
		}
		CS(awk, argv[3]);
	}
	else if(substring(argv[2], "L")){
		awk.command = "L";
		openDest(&awk, argv, argc, 4);
		getDigits(&awk, argv[2]);
		L(awk);
	}
	else if(substring(argv[2], "C")){
		awk.command = "C";
		openDest(&awk, argv, argc, 4);
		getDigits(&awk, argv[2]);
		C(awk);
	}
	else if(strcmp(argv[2], "S") == 0){
		awk.command = "S";
		if(argc<5){
			printf("\"%s\" esperaba mas argumentos.\nPara mas ayuda ejecuta '%s --help'\n", argv[2], argv[0]);
			return 1;
		}
		openDest(&awk, argv, argc, 6);
		S(awk, argv[3], argv[4]);
	}
	else{
		printf("\"%s\" no se reconoce como un comando.\nPara mas ayuda ejecuta '%s --help'\n", argv[2], argv[0]);
		destroyCommand(&awk);
		return 1;
	}
	destroyCommand(&awk);
	return 0;
}
