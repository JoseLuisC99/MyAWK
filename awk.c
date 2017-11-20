#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "awk.h"
#include "cli.h"


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
int Sstring(AWKCommand awk, const char *search, const char *replace){
	char buffer[BUFSIZ];
	int siz_search = strlen(search), siz_replace = strlen(replace);
	
	while(!feof(awk.source)){
		
		fgets(buffer, BUFSIZ, awk.source);
		int sizcad = strlen(buffer), ocurrence_index, is_subcad = 0;
		char *result;
		result = (char *)malloc(0 * sizeof(char));
		
		for(int i=0; i<sizcad; i++){
			/*if(buffer[i] == search[0]){
				ocurrence_index = i;
				for(int j = 0, k = i; j < siz_search; j++, k++){
					if(buffer[k] == search[j]){
						//printf("%c", buffer[k]);
						is_subcad = 1;
					}
					else{
						is_subcad = 0;
						break;
					}
				}
				if(is_subcad){
					
				}
				//printf("%d\n", is_subcad);
			}*/
			result = (char *)realloc(result, (i+1) * sizeof(char));
			result[i] = buffer[i];
			//printf("%d:%d:%c ", i, result[i], result[i]);
		}
		//result = (char *)realloc(result, (strlen(result)) * sizeof(char));
		//result[strlen(result)-1] = '\0';
		//printf("%s", result);
		//fputs(result, dest);
		printf("%d:%s\n", strlen(result), result);
		free(result);
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
		if(containDigit(awk, i)) fprintf(awk.dest, "%s\n", buffer);
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
				fprintf(awk.dest, "%s\t", token);
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
	int linea = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		int i = 0;
		linea++;
		char *token;
		token = strtok(buffer, " ");
		while(token != NULL){
			if(strcmp(token,string) == 0) i++;
			token = strtok(NULL, " ");
		}
		printf("Ocurrencias en la linea %3d: %d.\n", linea, i);
	}
	return 0;
}
int CCsubstring(AWKCommand awk, char *string){
	char buffer[BUFSIZ];
	int linea = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		linea++;
		int coincidences;
		coincidences = substring(buffer, string);
		printf("Ocurrencias en la linea %3d: %d.\n", linea, coincidences);
	}
	return 0;
}
int CP(AWKCommand awk, char *pre){
	char buffer[BUFSIZ];
	int linea = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		char *token;
		int i = 0;
		linea++;
		token = strtok(buffer, " ");
		while(token != NULL){
			if(indexOf(token, '\t') != -1)token[indexOf(token, '\n')] = '\0';
			i += prefix(token, pre);
			token = strtok(NULL, " ");
		}
		printf("Ocurrencias en la linea %3d: %d.\n", linea, i);
	}
	return 0;
}
int CS(AWKCommand awk, char *suf){
	char buffer[BUFSIZ];
	int linea = 0;
	while(!feof(awk.source)){
		fgets(buffer, BUFSIZ, awk.source);
		char *token;
		int i = 0;
		linea++;
		token = strtok(buffer, " ");
		while(token != NULL){
			if(indexOf(token, '\n') != -1)token[indexOf(token, '\n')] = '\0';
			i += suffix(token, suf);
			token = strtok(NULL, " ");
		}
		printf("Ocurrencias en la linea %3d: %d.\n", linea, i);
	}
	return 0;
}
