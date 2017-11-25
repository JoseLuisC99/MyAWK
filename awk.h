#ifndef AWK
#define AWK

#include "cli.h"

int substring(char *string, char *substr);

int S(AWKCommand awk, char *search, char *replace);
int Schar(AWKCommand awk, char search, char replace);
int Sstring(AWKCommand awk, char *search, char *replace);
int SMm(AWKCommand awk);
int SmM(AWKCommand awk);
int L(AWKCommand awk);
int C(AWKCommand awk);
int IL(AWKCommand awk);
int IC(AWKCommand awk);
int INC(AWKCommand awk);
int CC(AWKCommand awk, char *string);
int CCsubstring(AWKCommand awk, char *substring);
int CP(AWKCommand awk, char *prefix);
int CS(AWKCommand awk, char *suf);
int help(char *program);

#endif
