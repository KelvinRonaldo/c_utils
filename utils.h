#ifndef UTILS_H
#define UTILS_H

#define OK		1
#define LIMIT	100

#define true 	1;
#define false 	0;

#define ERR					0
#define NOT_REAL_ROOTS      -10

typedef unsigned char uChar;

long double mathRound		(long double value, int decimals);

void breakLineByCharacter	(char character, char *output);
void putCurrencyDecimals	(char *input, char *output);
void excludeFromStr			(char *input, char *output, char *toExclude);
void formatByMask			(char *input, char *output, char *format);
void replaceAll				(char *input, char *search, char new);
void clearVar				(void *element);
void splice					(char *str, int strSize, int init, int length, char *output);
void trim					(char *str);

int separateDate			(char *date, char *year, char *month, char *day);
int readHugeFile			(char *filePath, char *output, int position, int portion);
int verifyCnpj				(char *cnpj);
int isLikeChar				(char element, char *characters);
int subString				(char *input, char *output, int initIndex, int size);
int verifyCpf				(char *cpf);
int isNumber				(char element);
int breakTlv				(char *input, int targetTag, char *output);
int strlen2					(char *input);
int split					(char *input, char output[][128], char *divider, int numWords);



#endif