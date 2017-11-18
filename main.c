#include <stdio.h>
#include <stdlib.h>

#include "awk.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	char testDigits[] = "n2n4n6n8n10n12";
	
	AWKCommand awk;
	awk.source = fopen("source.txt", "r");
	awk.dest = fopen("dest.txt", "w");
	
	//S(awk, "L", "%");
	//SmM(awk);
	//SMm(awk);
	
	getDigits(&awk, testDigits);
	//L(awk);
	//C(awk);
	//IC(awk);
	//INC(awk);
	//CC(awk, "informacion");
	//CCsubstring(awk, "as");
	CS(awk, "cion");	
	return 0;
}
