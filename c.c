#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils.h"


int main(void){

	int ret;
	int intVar;

	char str[128] = "Variáveis que serão usadas para testes das funções.";
	char strArr[10][128];
	char result[128] = {0x00};

	char day[5] = {0x00};
	char month[5] = {0x00};
	char year[5] = {0x00};

	double dbVar = 0.0;

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("*****************************");
	puts("* Uso da funcao subString() *");
	puts("*****************************");

	strcpy(str, "Preenchendo variável para realizar teste de subString()");

	printf("< str: [%s]\n", str);
	printf("< restult: [%s]\n", result);

	ret = subString(str, result, 45, 11);
	if(!ret){
		puts("Erro na funcao subString()");
		return ret;
	}

	puts("↓↓↓↓↓↓↓");
	printf("=> str: [%s]\n", str);
	printf("=> restult: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("*************************");
	puts("* Uso da funcao split() *");
	puts("*************************");

	strcpy(str, "Preenchendo*variável para*realizar teste*de split()");
	printf("< str: [%s]\n", str);

	ret = split(str, strArr, "*", 4);
	if(!ret){
		puts("Erro na funcao split()");
		return ret;
	}

	puts("↓↓↓↓↓↓↓");
	printf("=> strArr[0] [%s]\n", strArr[0]);
	printf("=> strArr[1] [%s]\n", strArr[1]);
	printf("=> strArr[2] [%s]\n", strArr[2]);
	printf("=> strArr[3] [%s]\n", strArr[3]);


	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(strArr, 0x00, sizeof(strArr));
	memset(strArr, 0x00, sizeof(strArr));
	memset(strArr, 0x00, sizeof(strArr));
	memset(strArr, 0x00, sizeof(strArr));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("****************************************");
	puts("* Uso da funcao breakLineByCharacter() *");
	puts("****************************************");

	strcpy(str, "Preenchendo str para&testar&funcao breakLineByCharacter&!");

	printf("< str: [%s]\n", str);
	breakLineByCharacter('&', str);
	puts("↓↓↓↓↓↓↓");
	printf("=> str:\n[%s]\n", str);

	// Zera variável para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("********************************");
	puts("* Uso da funcao separateDate() *");
	puts("********************************");

	strcpy(str, "20201203");
	printf("< str: [%s]\n", str);

	ret = separateDate(str, year, month, day);
	if(!ret){
		puts("Erro na funcao separateDate()");
		return ret;
	}
	puts("↓↓↓↓↓↓↓");
	printf("=> year: [%s]\n", year);
	printf("=> month: [%s]\n", month);
	printf("=> day: [%s]\n", day);
	
	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(year, 0x00, sizeof(year));
	memset(month, 0x00, sizeof(month));
	memset(day, 0x00, sizeof(day));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("***************************************");
	puts("* Uso da funcao putCurrencyDecimals() *");
	puts("***************************************");

	strcpy(str, "500026");
	printf("< str: [%s]\n", str);

	putCurrencyDecimals(str, result);

	puts("↓↓↓↓↓↓↓");
	printf("=> result: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("*****************************");
	puts("* Uso da funcao mathRound() *");
	puts("*****************************");

	dbVar = mathRound(8974.61651, 1);

	printf("=> [%lf]\n", dbVar);

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("**********************************");
	puts("* Uso da funcao excludeFromStr() *");
	puts("**********************************");

	strcpy(str, "Preenchendo variável str para teste da funcao excludeFromStr()");
	printf("< str: [%s]\n", str);

	puts("↓↓↓↓↓↓↓");
	excludeFromStr(str, result, "ará");
	printf("=> result: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("********************************");
	puts("* Uso da funcao formatByMask() *");
	puts("********************************");

	formatByMask("031220201334", result, "##/##/#### ##h##m");

	puts("↓↓↓↓↓↓↓");
	printf("=> result: [%s]\n", result);
	
	// Zera variáveç para usa-la nos próximos testes
	memset(result, 0x00, sizeof(result));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("******************************");
	puts("* Uso da funcao replaceAll() *");
	puts("******************************");

	strcpy(str, "Preenchendo variável str para teste da funcao replaceAll()");
	printf("< str: [%s]\n", str);

	replaceAll(str, ") (", ':');

	puts("↓↓↓↓↓↓↓");
	printf("=> str: [%s]\n", str);

	// Zera variável para usa-la nos próximos testes
	memset(str, 0x00, sizeof(str));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("********************************");
	puts("* Uso da funcao readHugeFile() *");
	puts("********************************");

	/* LER APENAR UM TRECHO DO ARQUIVO */
	ret = readHugeFile(".//example.txt", result, 3573, 13);
	if(ret == ERR){
		puts("Erro na funcao readHugeFile()");
		return ret;
	}
	puts("↓↓↓↓↓↓↓");
	printf("=> result: [%s]\n", result);

	ret = 0;
	intVar = 0;

	/* LER ARQUIVO INTEIRO EM PARTES */
	do{
		ret = readHugeFile(".//example.txt", result, intVar, sizeof(result));
		printf("%s", result);
		memset(result, 0x00, sizeof(result));
		intVar += ret;
	}while(ret != 0);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));
	ret = 0;
	intVar = 0;

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("************************");
	puts("* Uso da funcao trim() *");
	puts("************************");

	strcpy(str, "   Preenchendo variável str para teste da funcao trim()       ");
	printf("< str: [%s]\n", str);

	trim(str);
	puts("↓↓↓↓↓↓↓");
	printf("=> str: [%s]\n", str);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("**************************");
	puts("* Uso da funcao splice() *");
	puts("**************************");

	strcpy(str, "Preenchendo variável str para teste da funcao splice()");
	printf("< str: [%s]\n", str);

	splice(str, strlen(str), 11, 25, result);
	puts("↓↓↓↓↓↓↓");
	printf("=> str: [%s]\n", str);
	printf("=> result: [%s]\n", result);
	
	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));

	return 0;
}