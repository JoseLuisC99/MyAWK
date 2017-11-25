#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "awk.h"
#include "cli.h"


const char tokens_text[] = " 	,.;:-_()[]{}<>'¡!¿?/\"\\";

int indexOf(char *string, char c){
	char *ptr;
	for(int i=0; i<strlen(string); i++)
		if(string[i] == c) return i;
	return -1;
}
int substring(char *string, char *substr){
	int coincidences = 0;
	for(int i=0; i<strlen(string); i++){
		if(string[i] == substr[0]){
			int isSubstring = 1;
			for(int j=0,k=i; j<strlen(substr); j++, k++){
				if(string[k] != substr[j]){
					isSubstring = 0;
					break;
				}
			}
			if(isSubstring) coincidences++;
		}
	}
	return coincidences;
}
int prefix(char *string, char *pre){
	for(; *pre!='\0'; string++, pre++)
		if(*pre!=*string) return 0;
	return 1;
}
int suffix(char *string, char *suf){
	for(int i=(strlen(string)-1), j=(strlen(suf)-1); j>=0; i--, j--)
		if(string[i] != suf[j]) return 0;
	return 1;
}

int S(AWKCommand awk, char *search, char *replace){
	if((strlen(search) == 1) && (strlen(replace) == 1)){
		return Schar(awk, search[0], replace[0]);
	}else{
		return Sstring(awk, search, replace);
	}
}
int Schar(AWKCommand awk, char search, char replace){
	char c;
	while((c = getc(awk.source)) != EOF){
		if(c == search)
			putc(replace, awk.dest);
		else
			putc(c, awk.dest);
	}
	return 1;
}
int Sstring(AWKCommand awk, char *search, char *replace){
	char buffer[BUFSIZ];
	
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		int size = 0;
		char *token;
		token = strtok(buffer, " ");
		while(token != NULL){
			if(indexOf(token, '\n') != -1)token[indexOf(token, '\n')] = '\0';
			if(strcmp(search, token) == 0){
				fprintf(awk.dest, "%s ", replace);
			}else{
				fprintf(awk.dest, "%s ", token);
			}
			token = strtok(NULL, " ");
		}
		fprintf(awk.dest, "\n");
	}
}

int SMm(AWKCommand awk){
	char c;
	while((c = getc(awk.source)) != EOF){
		if(c>='A' && c<='Z')
			putc(c+32, awk.dest);
		else
			putc(c, awk.dest);
	}
	return 1;
}
int SmM(AWKCommand awk){
	char c;
	while((c = getc(awk.source)) != EOF){
		if(c>='a' && c<='z')
			putc(c-32, awk.dest);
		else
			putc(c, awk.dest);
	}
	return 1;
}
int L(AWKCommand awk){
	char buffer[BUFSIZ];
	int i = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		if(containDigit(awk, i)) fputs(buffer, awk.dest);
		i++;
	}
}
int C(AWKCommand awk){
	char buffer[BUFSIZ];
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		char *token;
		int i = 0, print_newline = 1;
		token = strtok(buffer, " ");
		while(token != NULL){
			if(containDigit(awk, i)){
				if(indexOf(token, '\n') != -1)token[indexOf(token, '\n')] = '\0';
				fprintf(awk.dest, "%s ", token);
			}
			i++;
			token = strtok(NULL, " ");
		}
		fprintf(awk.dest, "\n");
	}
}
int IL(AWKCommand awk){
	char buffer[BUFSIZ];
	int i = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		if(containDigit(awk, i)) fprintf(awk.dest, "\n%s", buffer);
		else fputs(buffer, awk.dest);
		i++;
	}
	return 1;
}
int IC(AWKCommand awk){
	char buffer[BUFSIZ];
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		char *token;
		int i = 0, print_newline = 1;
		token = strtok(buffer, " ");
		while(token != NULL){
			if(indexOf(token, '\n') != -1)token[indexOf(token, '\n')] = '\0';
			if(containDigit(awk, i)){
				fprintf(awk.dest, "\t%s ", token);
			}else{
				fprintf(awk.dest, "%s ", token);
			}
			i++;
			token = strtok(NULL, " ");
		}
		fprintf(awk.dest, "\n");
	}
	return 1;
}
int INC(AWKCommand awk){
	char buffer[BUFSIZ];
	int i=1;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		fprintf(awk.dest, "%d\t%s", i, buffer);
		i++;
	}
	return 1;
}
int CC(AWKCommand awk, char *string){	
	char buffer[BUFSIZ];
	int linea = 0, total = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		int i = 0;
		linea++;
		char *token;
		token = strtok(buffer, tokens_text);
		while(token != NULL){
			if(indexOf(token, '\n') != -1)token[indexOf(token, '\n')] = '\0';
			if(strcmp(token,string) == 0){
				i++;
				total++;
			}
			token = strtok(NULL, tokens_text);
		}
		printf("Ocurrencias en la linea %3d: %d.\n", linea, i);
	}
	printf("\nEl numero total de ocurrencias es %d.", total);
	return 0;
}
int CCsubstring(AWKCommand awk, char *string){
	char buffer[BUFSIZ];
	int linea = 0, total = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		linea++;
		int coincidences;
		coincidences = substring(buffer, string);
		total += coincidences;
		printf("Ocurrencias en la linea %3d: %d.\n", linea, coincidences);
	}
	printf("\nEl numero total de ocurrencias es %d.", total);
	return 0;
}
int CP(AWKCommand awk, char *pre){
	char buffer[BUFSIZ];
	int linea = 0, total = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		char *token;
		int i = 0;
		linea++;
		token = strtok(buffer, tokens_text);
		while(token != NULL){
			i += prefix(token, pre);
			token = strtok(NULL, tokens_text);
		}
		total += i;
		printf("Ocurrencias en la linea %3d: %d.\n", linea, i);
	}
	printf("\nEl numero total de ocurrencias es %d.", total);
	return 0;
}
int CS(AWKCommand awk, char *suf){
	char buffer[BUFSIZ];
	int linea = 0, total = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		char *token;
		int i = 0;
		linea++;
		token = strtok(buffer, tokens_text);
		while(token != NULL){
			if(indexOf(token, '\n') != -1)token[indexOf(token, '\n')] = '\0';
			i += suffix(token, suf);
			token = strtok(NULL, tokens_text);
		}
		total += i;
		printf("Ocurrencias en la linea %3d: %d.\n", linea, i);
	}
	printf("\nEl numero total de ocurrencias es %d.", total);
	return 0;
}
int help(char *program){
	puts("MyAWK [Version 1.0.0]");
	puts("2017 Jose Luis Castro Garcia.");
	printf("\nSintaxis: %s <archivo-fuente> <comando> <parametros> [archivo-destino]\n\n", program);
	
	puts("El comando puede ser algunos de los siguientes:");
	puts("    S str1 str2		Remplaza la cadena str1 por la cadena str2 a lo largo de todo el archivo.");
	puts("    SmM			Remplaza todas las letras minusculas por mayusculas.");
	puts("    SMm			Remplaza todas las letras mayusculas por minusculas.");
	puts("    Lnd1nd2nd3n...	(n es el separador de digitos) Imprime las lineas indicadas por d1, d2 d3, ...");
	puts("    Cnd1nd2nd3n...	(n es el separador de digitos) Imprime las columnas indicadas por d1, d2 d3, ...");
	puts("    ILnd1nd2nd3n...	(n es el separador de digitos) Mete un salto de linea en las lineas ");
	puts("			indicadas por d1, d2 d3, ...");
	puts("    ICnd1nd2nd3n...	(n es el separador de digitos) Mete un tabulador las en columnas ");
	puts("			indicadas por d1, d2 d3, ...");
	puts("    INC			Imprime una columna indicando el numero de linea de cada renglon.");
	puts("    CC str		Cuenta e imprime el numero de currencias de la cadena str por linea.");
	puts("    CP str		Cuenta e imprime el numero de currencias del prefijo str por linea.");
	puts("    CS str		Cuenta e imprime el numero de currencias del sufijo str por linea.");
}
