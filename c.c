#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils.h"
#include "./datetime.h"


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
	puts("-----------------------------");
	puts("| Uso da funcao subString() |");
	puts("-----------------------------");

	strcpy(str, "Preenchendo variável para realizar teste de subString()");

	puts("ENTRADA:");
	printf("str: [%s]\n", str);
	printf("restult: [%s]\n", result);

	ret = subString(str, result, 45, 11);
	if(!ret){
		puts("Erro na funcao subString()");
		return ret;
	}

	puts("\nSAÍDA:");
	printf("str: [%s]\n", str);
	printf("restult: [%s]\n\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("-------------------------");
	puts("| Uso da funcao split() |");
	puts("-------------------------");

	puts("ENTRADA:");
	strcpy(str, "Preenchendo*variável para*realizar teste*de split()");
	printf("str: [%s]\n", str);

	ret = split(str, strArr, "*", 4);
	if(!ret){
		puts("Erro na funcao split()");
		return ret;
	}

	puts("\nSAÍDA:");
	printf("strArr[0] [%s]\n", strArr[0]);
	printf("strArr[1] [%s]\n", strArr[1]);
	printf("strArr[2] [%s]\n", strArr[2]);
	printf("strArr[3] [%s]\n", strArr[3]);


	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(strArr[0], 0x00, sizeof(strArr[0]));
	memset(strArr[1], 0x00, sizeof(strArr[1]));
	memset(strArr[2], 0x00, sizeof(strArr[2]));
	memset(strArr[3], 0x00, sizeof(strArr[3]));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("----------------------------------------");
	puts("| Uso da funcao breakLineByCharacter() |");
	puts("----------------------------------------");

	strcpy(str, "Preenchendo str para&testar&funcao breakLineByCharacter&!");

	puts("ENTRADA:");
	printf("str: [%s]\n", str);
	breakLineByCharacter('&', str);

	puts("\nSAÍDA:");
	printf("str:\n[%s]\n", str);

	// Zera variável para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("--------------------------------");
	puts("| Uso da funcao separateDate() |");
	puts("--------------------------------");

	puts("ENTRADA:");
	strcpy(str, "20201203");
	printf("str: [%s]\n", str);

	ret = separateDate(str, year, month, day);
	if(!ret){
		puts("Erro na funcao separateDate()");
		return ret;
	}

	puts("\nSAÍDA:");
	printf("year: [%s]\n", year);
	printf("month: [%s]\n", month);
	printf("day: [%s]\n", day);
	
	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(year, 0x00, sizeof(year));
	memset(month, 0x00, sizeof(month));
	memset(day, 0x00, sizeof(day));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("---------------------------------------");
	puts("| Uso da funcao putCurrencyDecimals() |");
	puts("---------------------------------------");

	puts("ENTRADA:");
	strcpy(str, "500026");
	printf("str: [%s]\n", str);

	putCurrencyDecimals(str, result);

	puts("\nSAÍDA:");
	printf("result: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("-----------------------------");
	puts("| Uso da funcao mathRound() |");
	puts("-----------------------------");

	puts("ENTRADA:");
	puts("8974.61651");
	dbVar = mathRound(8974.61651, 1);

	puts("\nSAÍDA:");
	printf("[%lf]\n", dbVar);

	// Zera variável para usa-la nos próximos teste
	dbVar = 0.0;

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("----------------------------------");
	puts("- Uso da funcao excludeFromStr() -");
	puts("----------------------------------");

	puts("ENTRADA:");
	strcpy(str, "Preenchendo variável str para teste da funcao excludeFromStr()");
	printf("str: [%s]\n", str);

	puts("\nSAÍDA:");
	excludeFromStr(str, result, "ará");
	printf("result: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("--------------------------------");
	puts("| Uso da funcao formatByMask() |");
	puts("--------------------------------");

	puts("ENTRADA:");
	puts("031220201334 com máscara ##/##/#### ##h##m");
	formatByMask("031220201334", result, "##/##/#### ##h##m");

	puts("\nSAÍDA:");
	printf("result: [%s]\n", result);
	
	// Zera variáveç para usa-la nos próximos testes
	memset(result, 0x00, sizeof(result));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("------------------------------");
	puts("| Uso da funcao replaceAll() |");
	puts("------------------------------");

	puts("ENTRADA:");
	strcpy(str, "Preenchendo variável str para teste da funcao replaceAll()");
	printf("str: [%s]\n", str);

	replaceAll(str, ") (", ':');

	puts("\nSAÍDA:");
	printf("str: [%s]\n", str);

	// Zera variável para usa-la nos próximos testes
	memset(str, 0x00, sizeof(str));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("--------------------------------");
	puts("| Uso da funcao readHugeFile() |");
	puts("--------------------------------");

	/* LER APENAR UM TRECHO DO ARQUIVO */
	ret = readHugeFile(".//example.txt", result, 3573, 13);
	if(ret == ERR){
		puts("Erro na funcao readHugeFile()");
		return ret;
	}

	puts("SAÍDA (TRECHO):");
	printf("result: [%s]\n", result);

	ret = 0;
	intVar = 0;

	/* LER ARQUIVO INTEIRO EM PARTES */
	puts("\nSAÍDA (COMPLETO):");
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
	puts("------------------------");
	puts("| Uso da funcao trim() |");
	puts("------------------------");

	puts("ENTRADA:");
	strcpy(str, "   Preenchendo variável str para teste da funcao trim()       ");
	printf("str: [%s]\n", str);

	trim(str);

	puts("\nSAÍDA:");
	printf("str: [%s]\n", str);

	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("--------------------------");
	puts("| Uso da funcao splice() |");
	puts("--------------------------");

	puts("ENTRADA:");
	strcpy(str, "Preenchendo variável str para teste da funcao splice()");
	printf("str: [%s]\n", str);

	splice(str, strlen(str), 11, 25, result);

	puts("\nSAÍDA:");
	printf("str: [%s]\n", str);
	printf("result: [%s]\n", result);
	
	// Zera variáveis para usa-las nos próximos testes
	memset(str, 0x00, sizeof(str));
	memset(result, 0x00, sizeof(result));
	
	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("-----------------------------------");
	puts("| Uso da funcao getDateOnFormat() |");
	puts("-----------------------------------");

	getDateOnFormat("W, dia DD de MM(L) de YYYY, hh:mm:ss", result, "", LANG_PTBR);
	puts("SAÍDA:");
	printf("result: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(result, 0x00, sizeof(result));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("--------------------------------");
	puts("| Uso da funcao getDayOfWeek() |");
	puts("--------------------------------");

	puts("ENTRADA:");
	getDateOnFormat("YYYYMMDD", str, "19200120000000", LANG_PTBR);
	printf("str: [%s]\n", str);

	getDayOfWeek(str, result, false, LANG_PTBR);

	puts("\nSAÍDA:");
	printf("result: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(result, 0x00, sizeof(result));

	// ========================================================================
	// ========================================================================
	// ========================================================================
	puts("\n");
	puts("----------------------------");
	puts("| Uso da funcao getMonth() |");
	puts("----------------------------");

	puts("ENTRADA:");
	getDateOnFormat("YYYYMMDD", str, "17420620000000", LANG_PTBR);
	printf("str: [%s]\n", str);

	getMonth(str, result, false, LANG_PTBR);

	puts("\nSAÍDA:");
	printf("result: [%s]\n", result);

	// Zera variáveis para usa-las nos próximos testes
	memset(result, 0x00, sizeof(result));

	return 0;
}