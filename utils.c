#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils.h"


void clearVar(void *element) {
	memset(element, 0x00, sizeof(element));
}

int subString(char *input, char *output, int initIndex, int size) {

	int i = 0;

	if (size > strlen(input)) {
		return ERR;
	}

	for (i = 0; i < size; i++) {
		output[i] = input[initIndex + i];
	}
	output[i] = '\0';

	return OK;
}

/**
 * TRANFORMA STRING EM ARRAY, DIVIDINDO /input/ PELO
 * SEPARADO ENVIADO EM divider
 * EX:
 * char str[] = "Example of#split funcion in#C lang"
 * char *result[64];
 * split(str, result, " ", 3);
 * -> result[0] = "Example of"
 * -> result[1] = "split funcion in"
 * -> result[2] = "C lang"
 **/
int split(char *input, char *output[], char *divider, int sentences) {

	int i = 0;
	char str[strlen(input) + 1];
	char *aux;

	if (strlen(input) <= 2) {
		return ERR;
	}

	strcpy(str, input);

	aux = strtok(str, divider);
	while (aux) {
		output[i] = aux;
		aux = strtok(NULL, divider);
		i++;
		if (i > sentences) break;
	}

	return OK;
}

/**
 * QUEBRA LINHAS DE UMA STRING POR UM DETERMINADO CARACTER
 * EX:
 * char str[] = "Example of@breakLineByCharacter@function"
 * breakLineByCharacter('@', str);
 * -> str = "Example of\nbreakLineByCharacter\nfunction"
 * @param character Separador que determina a quebra de linha
 * @param str String de entrada
 **/
void breakLineByCharacter(char character, char *str) {

	int i = 0;

	for (i = 0; i < strlen(str); i++) {
		if (str[i] == character) {
			str[i] = '\n';
		} else {
			str[i] = str[i];
		}
	}
}

/**
 * SEPARA UM DATA ENVIADA EM /date/
 * EX:
 * separateDate("150212", year, month, day);
 * -> year = 15
 * -> month = 02
 * -> day = 12
 * EX:
 * separateDate("19590518", year, month, day);
 * -> year = 1959
 * -> month = 05
 * -> day = 18
 * @param year Recebe o ano da data enviada em /date/
 * Deve ter o seu formato em AAAAMMDD ou AAMMDD, 
 * qualquer outro formato não é aceito
 * @param month Recebe o mês da data enviada em /date/
 * @param day Recebe o ano da data enviada em /date/
 * @return OK se valor enviado em /date/ estiver no formato
 * correto, do contrário retorn ERR 
 */
int separateDate(char *date, char *year, char *month, char *day) {
	char sPassword[64] = { 0x00 };
	char sSerial[64] = { 0x00 };
	char sDate[64] = { 0x00 };
	char sAux[64] = { 0x00 };

	int i = 0;
	int dateOffset = 0;
	int dateSize = 0;
	int iMonth = 0;
	int iYear = 0;
	int iDay = 0;
	int iAux = 0;
	int *arrDate[3];

	arrDate[2] = &iDay;
	arrDate[1] = &iMonth;
	arrDate[0] = &iYear;

	// GET ACTUAL DATE
	strcpy(sDate, date);
	dateSize = strlen(sDate);

	if(dateSize != 6 && dateSize != 8){
		return ERR;
	}

	for (dateOffset = 0, i = 0; i < 3; i++) {
		if(dateSize > 6 && i == 0){
			subString(sDate, sAux, dateOffset, 4);
			dateOffset += 4;
		}else{
			subString(sDate, sAux, dateOffset, 2);
			dateOffset += 2;
		}

		*arrDate[i] = atoi(sAux);
		clearVar(sAux);
	}

	sprintf(day, "%02d", iDay);
	sprintf(month, "%02d", iMonth);
	sprintf(year, "%02d", iYear);

	return OK;
}

/**
 * TRANFORMA UM NÚMERO INTEIRO EM UM NÚEMRO DE 2 CASAS DECIMAIS
 * RECOMENDADO PARA VALORES MONETÁRIOS
 * EX:
 * char str[] = "15658";
 * putCurrencyDecimals(str, result);
 * -> result == "156,58"
 * @param input Valor inteiro a ser transformado
 * @param output /input/ transformado com 2 casas decimais
 **/
void putCurrencyDecimals(char *input, char *output) {

	int i = 0;
	int j = 0;
	int inputSize = 0;

	char value[128] = { 0x00 };
	char aux[128] = { 0x00 };

	memset(value, 0, sizeof(value));
	inputSize = strlen(input);

	if (inputSize < 4) {
		memset(aux, 0, sizeof(aux));
		for (i = 4 - inputSize; i > 0; i--) {
			strcat(aux, "0");
		}
		sprintf(aux, "%s%s", aux, input);
		strcpy(input, aux);
		inputSize = strlen(input);
	}

	for (i = 0, j = 0; i < inputSize; i++, j++) {
		if (i == inputSize - 2) {
			value[j] = ',';
			value[++j] = input[i];
			continue;
		}
		value[j] = input[i];
	}

	strcpy(output, value);
}

/**
 * FAZ O ARREDONDAMENTO MATEMATICO PARA O NUMERO DE CASAS DECIMAIS DESEJADO
 * EX:
 * mathRound(10.32965, 3);
 * -> 10.330000
 * @param value Valor a ser arredondado
 * @param decimals Número de casas decimais
 * @return /value/ arredondado em /decimals/ casas decimais
*/
long double mathRound(long double value, int decimals) {

	int i = 0;
	int j = 0;
	int iValue = 0;	// PARTE INTEIRA DE value
	int size = 0;

	long double dValue = 0;	// PARTE DECIMAL DE value
	double sum = 0;

	char sValue[20] = { 0x00 };
	char sDecimal[20] = { 0x00 };
	char rounded[20] = { 0x00 };

	iValue = (int)value;
	dValue = value - iValue;

	sprintf(sValue, "%LF", value);
	sprintf(sDecimal, "%LF", dValue);

	size = strlen(sDecimal);

	if (decimals <= 0) {
		if (sDecimal[2] >= '5') {
			iValue += 1;
		}

		return iValue;
	}

	if ((size - 2) <= decimals) {
		return value;
	}

	for (i = 0; i < size; i++) {
		if ((i - 1) == decimals) {
			if (sDecimal[i + 1] >= '5') {
				rounded[i] = sDecimal[i];
				sum = 1;

				for (j = 0; j < decimals; j++) {
					sum = (sum * 10);   // elevando 10 a enésima potencia
				}

				sum = (1 / sum);
				dValue = atof(rounded) + sum;
			} else {
				rounded[i] = sDecimal[i];
				dValue = atof(rounded);
			}
			break;
		} else {
			rounded[i] = sDecimal[i];
		}
	}

	dValue = iValue + dValue;

	return dValue;

}

/**
 * RETORNA EM ouput TODO O CONTEÚDO DE input COM TODOS os
 * CARACTÉRES ENVIADOS EM /toExclude/ REMOVIDOS
 * EX:
 * char str[] = "Example for the excludeFromStr function"
 * excludeFromStr(str, result, "aeiou");
 * -> "Exmpl fr th xcldFrmStr fnctn"
 * @param input String do qual os chars de /toExclude/ serão retirados
 * @param output String de retorno
 * @param toExclude Conjunto de chars que serma removidos de /input/
 **/
void excludeFromStr(char *input, char *output, char *toExclude) {

	int i = 0;
	int j = 0;
	int k = 0;
	int size = 0;
	int searchTimes = 0;
	int invalid = 0;

	searchTimes = strlen(toExclude);
	size = strlen(input);

	for (i = 0, k = 0; i < size; i++, k++) {
		for (j = 0; j < searchTimes; j++) {
			if (input[i] == toExclude[j]) {
				invalid = true;
				break;
			}
		}
		if (!invalid) {
			output[k] = input[i];
		} else {
			k--;
		}
		invalid = false;
	}
}

/**
 * FORMATA UMA STRING (GERALMENTE NUMÉRICA) SEGUINDO O FORMATA
 * ENVIADO EM /format/
 * EX: formatByMask("1405", str, "##h ##m")
 * -> str == "14h 05m"
 * @param input String que se encaixara no formato desejado.
 * @param output String formatada.
 * @param format Formado no qual a /input/ será formatado.  
 * O formato deve ser feito com o carácter #, qualquer outros
 * será usado como separador
 **/
int formatByMask(char *input, char *output, char *format) {

	char aux[128];
	char cpy[128];
	int  i = 0;
	int  len = 0;
	int  count = 0;

	strcpy(cpy, input);
	len = strlen(cpy);

	while (count <= len) {
		if (format[i] != '#') {
			aux[i] = format[i];
			i++;
		} else {
			aux[i] = cpy[count];
			count++;
			i++;
		}
	}
	aux[i] = '\0';

	strcpy(output, aux);

	return(0);
}

/**
 * SUBSTITUIDO UM CARACTÉRES DE SUMA STRING, POR UM CARACTER DETERMINADO
 * EX: 
 * char str[] = "X.P-T*O";
 * replaceAll(str, "*-.", '+');
 * -> str == "X+P+T+O"
 * @param input String on os caracteres seram substituidos.
 * @param search String com todos os caractéres a serem subtituídos.
 * @param new Caracter que servirá como substituto.
 **/
void replaceAll(char *input, char *search, char new) {

	int i = 0;
	int j = 0;
	int size = 0;
	int searchTimes = 0;

	searchTimes = strlen(search);
	size = strlen(input);

	for (i = 0; i < size; i++, j = 0) {
		for (j = 0; j < searchTimes; j++) {
			if (input[i] == search[j]) {
				input[i] = new;
			}
		}
	}
}

/**
 * QUEBRA E MOSTRA OS CAMPOS DE VALORES DE UMA STRING NO FORMATO TLV
 * E RETORNA VALOR DO CAMPO DESEJADO
 * EX: 
 * breakTlv("001005abcdef002003ghi003006jklmno", 2, str);
 * -> str == "ghi"
 * @param input String em formato TLV.
 * @param targetTag Tag cujo valor deseja que retorne.
 * @param output Valor da da tag escolhida.
 * @return OK se String tiver tamanho mínimo para o formato TLV
 * (7 caracteres), se não, retorna ERR.
 **/
int breakTlv(char *input, int targetTag, char *output){

	int i = 0;
	int size = 0;
	int tag;
	int length;
	char aux[1024] = {0x00};
	char value[512] ={0x00};

	printf(">> [%s]\n", input);
	printf("ID  TAM FILL\n", input);
	strcpy(output, "\0");
	if(!strlen(input) < 7){
		while(i < strlen(input)){
			clearVar(aux);
			subString(input, aux, i, 3);			// ID DA TAG
			tag = atoi(aux);

			subString(input, aux, i += 3, 3);		// TAMANHO DO CONTEÚDO DA TAG
			size = atoi(aux);
			length = atoi(aux);
			clearVar(aux);


			subString(input, aux, i += 3, size);	// CONTEÚDO DA TAG
			strcpy(value, aux);
			i += size;

			printf("%03d ", tag);
			printf("%03d", length);
			printf(" %s\n", value);

			if(tag == targetTag){
				strcpy(output, value);
				break;
			}
		}
	}else{
		return ERR;
	}

	return OK;
}

/**
 * FAZ A LEITURA DA TABELA DE TAXAS A JUROS DA MENSAGERIA - ISO 8583
 **/
int breakClient(char *input){

	FILE *exp;

	int i = 0;
	int size = 0;

	char table[512] = {0x00};
	char aux[2048] = {0x00};
	char index[512] = {0x00};
	char first[512] = {0x00};
	char second[512] = {0x00};
	char third[512] = {0x00};
	char line[2048] = {0x00};
	
	
	printf(">> [%s]\n", input);

	if(strlen(input) >= 16){
		while(i < strlen(input)){
			subString(input, table, i, 3);			// COD. DA TABELA
			i += 3;

			subString(input, index, i, 3);			// INDEX A SER LIDO
			i += 3;
			sprintf(line, "%s %s ", line, index);

			if(strcmp(index, "999") == 0){
				goto INIT_READ;
			}

			subString(input, first, i, 2);			// POSIÇÃO 1
			i += 2;
			sprintf(line, "%s %s ", line, first);

			subString(input, second, i, 5);			// POSIÇÃO 2
			i += 5;
			sprintf(line, "%s %s ", line, second);

			subString(input, third, i, 3);			// POSIÇÃO 3
			i += 3;
			sprintf(line, "%s %s\n", line, third);


			if(strcmp(table, "000") == 0){
				exp = fopen(".//juros.txt", "ab");				
			}else if(strcmp(table, "001") == 0){
				exp = fopen(".//taxas.txt", "ab");				
			}

			fputs(line, exp);
			fclose(exp);

			printf("\n%s ", table);
			printf("%s", line);
			// printf("%3s\n", table);
			// printf("%3s ", index);
			// printf("%2s ", first);
			// printf("%5s ", second);
			// printf("%3s\n", third);

			INIT_READ:
			clearVar(index);
			clearVar(first);
			clearVar(second);
			clearVar(third);
			clearVar(line);
			clearVar(exp);
		}
	}else{
		return ERR;
	}
	return OK;
}

/**
 * LÊ, EM PORÇÕES, O CONTEÚDO DE UM ARQUIVO
 * USO RECOMENDADO EM ARQUIVO COM MUITOS DADOS
 * @param filePath Caminho do arquivo a ser lido.
 * @param output String de 1024 bytes(max) lida do arquivo.
 * @param position Posição em bytes do início da leitura do arquivo.
 * Se for 0 ou menor, o arquivo será lido do início, do contrário, 
 * a leitura se iniciará apartir do byte especificado.
 * @param portion Quantidade de bytes a serem lidos (e retornardos), 
 * se valor enviado for < 0, o padrão será o máximo de 1024.
 * @return Número de bytes lidos.
 **/
int readHugeFile(char *filePath, char *output, int position, int portion){

	FILE *pFile;
	int rc = 0;
	char name[64] = {0x00};
	char read[1024] = {0x00};

	pFile = fopen(filePath, "r");

	if(pFile == NULL){
		return ERR;
	}

	if(position > 0) fseek(pFile, position, SEEK_SET);
	if(portion <= 0) portion = 1024;

	rc = fread(read, sizeof(char), portion, pFile);

	strcpy(output, read);

	fclose(pFile);
	
	return rc;
}

/**
 * REMOVE UMA PORÇÃO DE /str/ E COLOCA EM output
 * EX: 
 * char str[] = "Testing splice function in C lang" 
 * splice(str, strlen(str), 7, 7, result); 
 * -> str = "Testing function in C lang" 
 * -> result = "splice"
 * @param str String de onde será removido o conteúdo
 * @param strSize Tamanho total de /str/
 * @param init Ìndice do início de onde será pego o conteúdo de /str/
 * @param length Quantidade e índice seguintes à serem pegos
 * @param output Porção removida de /str/
 **/
void splice(char *str, int strSize, int init, int length, char *output){

	int i = 0;
	int j = 0;
	int k = 0;
	
	str[strSize] = 0;

	for (i = init; i < length + init; i++, j++){
		output[j] = str[i];
	}

	trim(output);

	for (j = 0; j < length; j++){
		for (i = init; i < strSize; i++){
			str[i] = str[i + 1];
		}
	}
}

/**
 * REMOVE ESPAÇO DO INÍCIO E DO FINAL DA STRING
 * @param str String de onde os espaços seram removidos.
 **/
void trim(char *str){

	int strSize = strlen(str);
	int i = 0;

	if(str[0] == ' '){
		for (i = 0; i < strSize; i++){
			str[i] = str[i + 1];
		}
		strSize = strlen(str);
	}
	
	if(str[strSize - 1] == ' '){
		str[strSize - 1] = '\0';
	}

}

/**
 * FUNÇÃO QUE RETORNA O NúMERO DE CARACTERES DE UMA STRING
 * DESPRESANDO A DUPLICIDADE DOS CARACTERES ESPECIAIS
 * @param input String que terá sua quantidade de caractéres contada
 * @return Número de caractéres da string; tamanho de /input/
 **/
int strlen2(char *input) {

	int i = 0;
	int inputSize = 0;
	int inputAsciiChar = 0;
	int size = 0;

	inputSize = strlen(input);
	for (i = 0; i < inputSize; i++){
		inputAsciiChar = input[i];

		// CARACTER ASCI AUXILIAR DE CARCTERES AUXILIARES DEPENDE DO COMPILADOR
		if (inputAsciiChar != 195 && inputAsciiChar != -61)
			size++;
	}

	return size;
}

/**
 * REALIZADA A VALIDAÇÃO DO DÍGITO VERIFICADOR DO CPF
 * @param cpf CPF a ser verificado.
 * @return True se o /cpf/ for válido e false se for inválido.
 **/
int verifyCpf(char *cpf){
	
	int i = 0;
	int j = 0;
	int multiplier = 10;						// NÚMERO QUE MULTIPLICARÁ CADA DIGITO DO CPF DECREMENTALMENTE
	int sum = 0;								// ARMAZENA A SOMA FINAL DOS NUMEROS DO CPF MULTIPLICADOS

	char cpfWithoutDigit[20] = {0x00};
	char originalDigit[4] = {0x00};
	char finalDigit[4] = {0x00};

	int numChars[32];							// ARRAY QUE RECEBE OS CARACTÉRES DO CPF EM int
	int multiplied[32];
	int sums[30];

	double divRemainder = 0.0;

	if(strcmp(cpf, "00000000000") == 0){
		return false;
	}

	
	subString(cpf, originalDigit, 9, 2);
	subString(cpf, cpfWithoutDigit, 0, strlen(cpf) - 2);

	for(i = 0; i < 2; i++){
		for(j = 0; j < strlen(cpfWithoutDigit); j++){
			numChars[j] = cpf[j] - '0'; // char PARA int CALCULANDO PELO CÓDIGO ASCII
			multiplied[j] = numChars[j] * multiplier;
			multiplier--;
			sum += multiplied[j];

		}

		divRemainder = sum % 11;
		if(divRemainder < 2){
			if(strlen(finalDigit) < 1){
				strcpy(finalDigit, "0");
			}else{
				strcat(finalDigit, "0");
			}
		}else{
			sprintf(finalDigit, "%s%d", finalDigit, (int)(11 - divRemainder));
		}

		sum = 0;
		memset(numChars, 0x00, sizeof(numChars));
		memset(multiplied, 0x00, sizeof(multiplied));
		sprintf(cpfWithoutDigit, "%s%s", cpfWithoutDigit, finalDigit);
		multiplier = 11;


	}

	if(strcmp(finalDigit, originalDigit) != 0){
		return false;
	}

	return true;
}

/** 
 * **** DEVE SER REVISADA ****
 * REALIZADA A VALIDAÇÃO DO DÍGITO VERIFICADOR DO CNPJ
 * @param cnpj CNPJ a ser verificado.
 * @return True se o /cnpj/ for válido e false se for inválido.
 **/
int verifyCnpj(char *cnpj){
	
	int i = 0;
	int j = 0;
	int k = 0;
	int multiplier = 2;							// NÚMERO QUE MULTIPLICARÁ CADA DIGITO DO CNPJ INCREMENTALMENTE DE 2 A 9
	int sum = 0;								// ARMAZENA A SOMA FINAL DOS NUMEROS DO CNPJ MULTIPLICADOS

	int numChars[32];							// ARRAY QUE RECEBE OS CARACTÉRES DO CNPJ EM int
	int multiplied[32];

	char cnpjWithoutDigit[32];
	char originalDigit[4] = {0x00};
	char finalDigit[4] = {0x00};
	double divRemainder = 0.0;

	if(strcmp(cnpj, "00000000000000") == 0){
		return false;
	}

	subString(cnpj, originalDigit, strlen(cnpj) - 2, 2);
	subString(cnpj, cnpjWithoutDigit, 0, strlen(cnpj) - 2);

	for(i = 0; i < 2; i++){
		for(j = strlen(cnpjWithoutDigit) - 2, k = 0; j >= 0; j--, k++){
			numChars[k] = cnpj[j] - '0'; // char PARA int CALCULANDO PELO CÓDIGO ASCII
			multiplied[k] = numChars[k] * multiplier;
			multiplier++;
			if(multiplier > 9){
				multiplier = 2;
			}
			sum += multiplied[k];			
		}

		divRemainder = sum % 11;
		if(divRemainder < 2){
			if(strlen(finalDigit) < 1){
				strcpy(finalDigit, "0");
			}else{
				strcat(finalDigit, "0");
			}
		}else{
			sprintf(finalDigit, "%s%d", finalDigit, (int)(11 - divRemainder));
		}

		sum = 0;
		memset(numChars, 0x00, sizeof(numChars));
		memset(multiplied, 0x00, sizeof(multiplied));
		sprintf(cnpjWithoutDigit, "%s%s", cnpjWithoutDigit, finalDigit);
		multiplier = 2;
	}

	if(strcmp(finalDigit, originalDigit) != 0){
		return false;
	}

	return true;
}

/**
 * VERIFICA SE CARACTÉR /element/ É UM NÚMERO
 **/
int isNumber(char element){

	if((int)element >= 48 && (int)element <= 57){
		return true;
	}

    return false;
}

/**
 * VERIFICA SE CARACTÉR /element/ ESTÁ EM /characters/
 **/
int isLikeChar(char element, char *characters){

    int i;

    for(i = 0; i < 10; i++){
        if(element == characters[i]){
            return true;
        }
    }

    return false;
}