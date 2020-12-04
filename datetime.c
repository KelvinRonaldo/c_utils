#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "./utils.h"
#include "./datetime.h"

const char months[12][2][11] = {
	{"january"	, "Janeiro"		},
	{"february"	, "Fevereiro"	},
	{"march"	, "Marco"		},
	{"april"	, "Abril"		},
	{"maio"		, "Maio"		},
	{"june"		, "Junho"		},
	{"july"		, "Julho"		},
	{"august"	, "Agosto"		},
	{"september", "Setembro"	},
	{"october"	, "Outubro"		},
	{"november"	, "Novembro"	},
	{"december"	, "Dezembro"	}
};

const char weekDays[7][2][20] = { 
	{"Monday"	, "Segunda-Feira"	},
	{"Tuesday"	, "Terca-Feira"		},
	{"Wednesday", "Quarta-Feira"	},
	{"Thursday"	, "Quinta-Feira"	},
	{"Friday"	, "Sexta-Feira"		},
	{"Saturday"	, "Sábado"			},
	{"Sunday"	, "Domingo"			}
};


/* ********** REVISAR CALCULO DE DIA SEMANA *************
 * FUNÇÃO QUE RETORNAR UM TIMESTAMP SEGUNDO FORMATO DETERMINADO PELA SUA CHAMADA
 * SEGUINDO OS SEGUINTES PARÂMETROS:
 * =========================================================================================
 * = DD	=> Retorna, em numeral, o DIA atual(do mês)		- (de 01 à 31)						=
 * = MM	=> Retorna, em numeral, o MÊS atual				- (de 01 à 12)						=
 * = YY	=> Retorna os 2 últimos caractéries do ANO		- (2019 > 19; 2020 > 20...)			=
 * = YYYY	=> Retorna o valor cheio do ANO				- (2019, 2020...)					=
 * = hh	=> Retorna a HORA do hoŕario atual				- (15:21:55 > 15)					=
 * = mm	=> Retorna os MINUTOS do hoŕario atual			- (15:21:55 > 21)					=
 * = ss	=> Retorna os SEGUNDOS do hoŕario atual			- (15:21:55 > 55)					=
 * = W		=> Returno o NOME inteiro do DIA atual		- (Segunda-Feira, Terça-Feira...)	=
 * = w		=> Returno o NOME contractado do DIA atual	- (Seg, Ter, Qua...)				=
 * = L		=> Returno o NOME inteiro do MÊS atual		- (Janeiro, Fevereiro...)			=
 * = l		=> Returno o NOME contractado do MÊS atual	- (Jan, Fev...)			            =
 * =========================================================================================
 * 
 * =+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
 * =	 QUALQUER CARACTÉR ENVIADO, DIFERENTE DOS DESCRITOS À CIMA SERÁ ENCARADOS COMO		=
 * =	  SEPARADOR, SENDO INCLUÍDOS NA STRING output QUE SERÁ O RETORNO DA FUNÇÃO		=
 * =+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
 * = OS CARACTÉRES ENVIADOS EM format, DEVEM SER ESCRITOS EXATAMENTE COMO DESCRITOS ACIMA  =
 * =   VALORES COMO: D, MMM, mmm, h, sssss[...], FARAM COM QUE A FUNÇÃO RETORNE UM ERRO    =
 * =+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
 * = O PARÂMETROS format DEVE CONTER PELO MENOS UM DOS CARACTÉRES DESCRITOS, NÃO TENDO UM  =
 * =   RETORNO PADRÃO, OU SEJA, O PARÂMETRO TEM DE SER ENVIADOS COM UM DOS VALORES ACIMA   =
 * =+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
 * = OS CARACTÉRES PODEM SER ENVIADOS EM CONJUNTO FORMAR ASSIM MÁSCARAS DE DATAS E HORAŔIO =
 * =				JUNTAMENTE COM OUTROS CARACTÉRES QUE SERAM SEPARADORES					=
 * =  Ex: DD/MM/YYYY | YYYY/MM/DD | DD de L de YYYY | DD/MM hh:mm | l, DDth of YYYY [...]  =
 * =+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
 * =+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
 * = O PARAMETRO input_data_time DEVERÁ CONTER UMA DATA NO FORMATO YYYYMMDDhhmmss ou " "   =
 * = CASO O PARAMETRO SEJA IGUAL A " " A DATA A SER FORMATADA SERÁ A DATA E HORAL ATUAL DO =
 * = SISTEMA.                                                                      		=
 * = O PARAMETRO DEVERÁ TER 0 OU 14 CARACTERES:                                            =
 * = CASO EU QUEIRA FORMATAR SOMENTE A DATA A HORA DEVERÁ VIR ZERADA                       =
 * =  Ex: 20191205000000 formatando somente data                                           =
 * = CASO EU QUEIRA FORMATAR SOMENTE A HORA A DATA DEVERÁ VIR ZERADA                       =
 * =  Ex: 00000000152208 formatando somente hora                                           =
 * =+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
 */




/**
 * @brief Get the Date On Format object
 * 
 * @param format 
 * @param output 
 * @param actualDate 
 * @param lang 
 * @return int 
 */
int getDateOnFormat(char *format, char *output, char *actualDate, int lang){

	time_t timer = time(NULL);
	struct tm* tm;

	char result [256] 	= {0x00};
	char date   [50]	= {0x00};
	char aux    [128]	= {0x00};
	char weekDay[128]	= {0x00};
	char month  [128]	= {0x00};

	int limit 	= strlen(format);
	int YCount	= 0;
	int DCount	= 0;
	int MCount	= 0;
	int hCount	= 0;
	int mCount	= 0;
	int sCount	= 0;
	int WCount	= 0;
	int LCount	= 0;
	int wCount	= 0;
	int lCount	= 0;
	int i		= 0;
	int j		= 0;

	tm->tm_wday	= 0;
	tm->tm_year	= 0;
	tm->tm_mon	= 0;
	tm->tm_mday	= 0;
	tm->tm_hour	= 0;
	tm->tm_min	= 0;
	tm->tm_sec	= 0;

	// testa a validade do parametro data a ser formatada = actualDate
	if (strlen(actualDate) != 0 && strlen(actualDate) != 14){
		strcpy(output, "ERRO DATA ENVIADA É INVALIDA");
		return ERR;
	}

	// seta a estrutura com os valores corretos de YYYYMMDDhhmmss
	if (strlen(actualDate) == 0){
		tm = localtime(&timer);
		tm->tm_mon++;
	} else {
		memset(aux, 0 ,sizeof(aux));
		subString(actualDate, aux, 0, 4);
		tm->tm_year = atoi(aux) - 1900;

		memset(aux, 0 ,sizeof(aux));
		subString(actualDate, aux, 4, 2);
		tm->tm_mon = atoi(aux);

		memset(aux, 0 ,sizeof(aux));
		subString(actualDate, aux, 6, 2);
		tm->tm_mday = atoi(aux);

		memset(aux, 0 ,sizeof(aux));
		subString(actualDate, aux, 8, 2);
		tm->tm_hour = atoi(aux);

		memset(aux, 0 ,sizeof(aux));
		subString(actualDate, aux, 10, 2);
		tm->tm_min = atoi(aux);

		memset(aux, 0 ,sizeof(aux));
		subString(actualDate, aux, 12, 2);
		tm->tm_sec = atoi(aux);

		memset(aux, 0 ,sizeof(aux));
	}

	// testa os valores de cada variavel da estrutura de data YYYYMMDD
	if(tm->tm_year != 0){
		if(tm->tm_mon < 0 || tm->tm_mon > 12){
			strcpy(output, "ERRO MES INVALIDO");
			return ERR;
		}

		switch (tm->tm_mon){
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				 if(tm->tm_mday < 1 || tm->tm_mday > 31){
					strcpy(output, "ERRO DIA INVALIDO");
					return ERR;
				 }
				 break;

			case 4: case 6: case 9: case 11:
				 if(tm->tm_mday < 1 || tm->tm_mday > 30){
					strcpy(output, "ERRO DIA INVALIDO");
					return ERR;
				 }
				 break;
				 
			case 2:
				 if(tm->tm_year % 4 == 0){
					 if(tm->tm_mday < 1 || tm->tm_mday > 29){
						strcpy(output, "ERRO DIA INVALIDO");
						return ERR;
					 }
				 }else{
					 if(tm->tm_mday < 1 || tm->tm_mday > 28){
						strcpy(output, "ERRO DIA INVALIDO");
						return ERR;
					 }

				 }
				 break;
		}
	}

	// testa os valores de cada variavel da estrutura de hora hhmmss
	 if(tm->tm_hour < 0 || tm->tm_hour > 24){
		strcpy(output, "ERRO HORA INVALIDA");
		return ERR;
	 }

	 if(tm->tm_min < 0 || tm->tm_min > 59){
		strcpy(output, "ERRO MINUTOS INVALIDOS");
		return ERR;
	 }

	 if(tm->tm_sec < 0 || tm->tm_sec > 59){
		strcpy(output, "ERRO SEGUNDOS INVALIDOS");
		return ERR;
	 }

	// CRIA A STRING YYYYMMDDhhmmss COM ZEROS A ESQUERDA CASO NECESSÁRIO
	memset(date, 0x00, sizeof(date));

	if(strlen(actualDate) == 14){
		sprintf(date, actualDate);
	}else{
		sprintf(date, "%d%02d%02d%02d%02d%02d",
				tm->tm_year + 1900,
				tm->tm_mon	,
				tm->tm_mday,
				tm->tm_hour,
				tm->tm_min	,
				tm->tm_sec);
	}

	for(i = 0; i < limit; i++){
		switch (format[i]){
			case 'Y': YCount++; break;
			case 'D': DCount++; break;
			case 'M': MCount++; break;
			case 'h': hCount++; break;
			case 'm': mCount++; break;
			case 's': sCount++; break;
			case 'W': WCount++; break;
			case 'w': wCount++; break;
			case 'L': LCount++; break;
			case 'l': lCount++; break;
		}
	}


	if(
		YCount == 0 
		&& DCount == 0 
		&& MCount == 0 
		&& hCount == 0 
		&& mCount == 0 
		&& sCount == 0 
		&& WCount == 0 
		&& wCount == 0 
		&& LCount == 0 
		&& lCount == 0
	){
		strcpy(output, "NÃO HÁ CARACTÉRES RESERVADOS PARA MÁSCARA DE DATA");
		return ERR;
	}

	if(DCount != 2 && DCount != 0){
		DCount = 0;
	}
	if(MCount != 2 && MCount != 0){
		MCount = 0;
	}
	if(hCount != 2 && hCount != 0){
		hCount = 0;
	}
	if(mCount != 2 && mCount != 0){
		mCount = 0;
	}
	if(sCount != 2 && sCount != 0){
		sCount = 0;
	}
	if(WCount != 1 && WCount != 0){
		WCount = 0;
	}
	if(wCount != 1 && wCount != 0){
		wCount = 0;
	}
	if(LCount != 1 && LCount != 0){
		LCount = 0;
	}
	if(lCount != 1 && lCount != 0){
		lCount = 0;
	}

	if(YCount != 0){
		if(YCount != 2 && YCount != 4){
			strcpy(output, "QUANTIDADE DE CARACTÉRES RESERVADOS INVÁLIDA");
			return ERR;
		}
	}

	if(limit > 128){
		strcpy(output, "NÚMERO MÁXIMO EXCEDIDO NA MÁSCARA");
		return ERR;
	}

	for(i = 0; i < limit; i++, j++){
		switch (format[i]){
			case 'Y':
				if(YCount > 2){
					switch (YCount){
						case 4: result[j] = date[0]; YCount--; break;
						case 3: result[j] = date[1]; YCount--; break;
						case 2: result[j] = date[2]; YCount--; break;
						case 1: result[j] = date[3]; YCount--; break;
					}
				}else if (YCount <= 2){
					switch (YCount){
						case 2: result[j] = date[2]; YCount--; break;
						case 1: result[j] = date[3]; YCount--; break;
					}
				} else{
					result[j] = format[i];
				}
				break;

			case 'M':
				if(MCount > 0){
					switch (MCount){
						case 2: result[j] = date[4]; MCount--; break;
						case 1: result[j] = date[5]; MCount--; break;
					}
				} else{
					result[j] = format[i];
				}
				break;

			case 'D':
				if(DCount > 0){
					switch (DCount){
						case 2: result[j] = date[6]; DCount--; break;
						case 1: result[j] = date[7]; DCount--; break;
					}
				} else{
					result[j] = format[i];
				}
				break;

			case 'h':
				if(hCount > 0){
					switch (hCount){
						case 2: result[j] = date[8]; hCount--; break;
						case 1: result[j] = date[9]; hCount--; break;
					}
				} else{
					result[j] = format[i];
				}
				break;

			case 'm':
				if(mCount > 0){
					switch (mCount){
						case 2: result[j] = date[10]; mCount--; break;
						case 1: result[j] = date[11]; mCount--; break;
					}
				} else{
					result[j] = format[i];
				}
				break;

			case 's':
				if(sCount > 0){
					switch (sCount){
						case 2: result[j] = date[12]; sCount--; break;
						case 1: result[j] = date[13]; sCount--; break;
					}
				} else{
					result[j] = format[i];
				}
				break;

			case 'W':
			case 'w':
				if(wCount > 0 || WCount > 0){
					memset(aux, 0x00, sizeof(aux));
					subString(date, aux, 2, strlen(date));
					if(format[i] == 'W'){
						getDayOfWeek(aux, weekDay, false, lang);
					}else{
						getDayOfWeek(aux, weekDay, true, lang);
					}
					strcat(result, weekDay);
					j += strlen(weekDay) - 1;
				} else{
					result[j] = format[i];
				}
				break;

			case 'L':
			case 'l':
				if(lCount > 0 || LCount > 0){
					memset(aux, 0x00, sizeof(aux));
					subString(date, aux, 2, strlen(date));
					if(format[i] == 'L'){
						getMonth(aux, month, false, lang);
					}else{
						getMonth(aux, month, true, lang);
					}
					strcat(result, month);
					j += strlen(month) - 1;
				} else{
					result[j] = format[i];
				}
				break;

			default : result[j] = format[i]; break;
		}
	}

	strcpy(output, result);

	return OK;
}


/** ********* REVISAR CALCULO DE DIA SEMANA *************
 * @brief RETORNA O DIA ATUAL DA SEMANA POR EXTENSO
 * EX:
 * getDayOfWeek("150423", result, false, LANG_ENUS);
 * => result: "Thursday"
 * @param inputDate String da data cujo dia será o obtido no formato YYMMDD.
 * @param output String de retorno, onde o dia da semana será retornado.
 * @param contract Boolean que define se o a escrita do dia será contractada .
 * Se for true, retorna contractada, se false, retorna nome completo.
 * @param lang Define do idioma em que o dia deve ser escrito.
 */
void getDayOfWeek(char *inputDate, char *output, const int contract, int lang)
{
	char zAux[128] = {0x00};
	int day 	= 0;
	int month	= 0;
	int year	= 0;

	sprintf(zAux, "%c%c"  , inputDate[4], inputDate[5]);
	day = atoi(zAux);

	sprintf(zAux, "%c%c"  , inputDate[2], inputDate[3]);
	month = atoi(zAux);

	sprintf(zAux, "%c%c", inputDate[0], inputDate[1]);
	year = atoi(zAux) + 2000;

    switch(month)
    {
        case  1: break;
        case  2: day +=  31; break;
        case  3: day +=  59; break;
        case  4: day +=  90; break;
        case  5: day += 120; break;
        case  6: day += 151; break;
        case  7: day += 181; break;
        case  8: day += 212; break;
        case  9: day += 243; break;
        case 10: day += 273; break;
        case 11: day += 304; break;
        case 12: day += 334; break;
    }

   /* Se o ano é um ano-bisexto E
   Se o mes de fevereiro ja passou entao acrescente um dia ao deslocamento*/
	if (((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0)) && (month > 2)){
		day += 1;
	}
	day += -1 + (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;


	memset(zAux, 0x00, sizeof(zAux));

	switch(day % 7)
	{
		case MONDAY		: strcpy(zAux, weekDays[MONDAY][lang])		; break;
		case TUESDAY	: strcpy(zAux, weekDays[TUESDAY][lang])		; break;
		case WEDNESDAY	: strcpy(zAux, weekDays[WEDNESDAY][lang])	; break;
		case THURSDAY	: strcpy(zAux, weekDays[THURSDAY][lang]) 	; break;
		case FRIDAY		: strcpy(zAux, weekDays[FRIDAY][lang])		; break;
		case SATURDAY	: strcpy(zAux, weekDays[SATURDAY][lang])	; break;
		case SUNDAY		: strcpy(zAux, weekDays[SUNDAY][lang])		; break;
	}


	if(!contract){
		strncpy(output, zAux, strlen(zAux));
	}else{
		strncpy(output, zAux, 3);
	}
}

/**
 * @brief RETORNA O MÊS ATUAL POR EXTENSO
 * EX:
 * getMonth("191201", result, true, LANG_PTBR);
 * -> result: "Jan"
 * @param inputDate String da data cujo mês será o obtido no formato YYMMDD.
 * @param output String de retorno, onde o mês será retornado.
 * @param contract Boolean que define se o a escrita do mês será contractada.
 * Se for true, retorna contractada, se false, retorna nome completo.
 * @param lang Define do idioma em que o mês deve ser escrito.
 */
void getMonth(char *inputDate, char *output, const int contract, int lang){

	int  monthNum;
	char monthStr[3]	= {0x00};
	char zAux[128] 		= {0x00};

	subString(inputDate, monthStr, 2, 2);
	monthNum = atoi(monthStr);

	switch(monthNum - 1){
		case JANUARY	: 	strcpy(zAux, months[JANUARY][lang])		;	break;
		case FEBRUARY	: 	strcpy(zAux, months[FEBRUARY][lang])	; 	break;
		case MARCH		: 	strcpy(zAux, months[MARCH][lang])		;	break;
		case APRIL		: 	strcpy(zAux, months[APRIL][lang])		;	break;
		case MAIO		: 	strcpy(zAux, months[MAIO][lang])		;	break;
		case JUNE		: 	strcpy(zAux, months[JUNE][lang])		;	break;
		case JULY		: 	strcpy(zAux, months[JULY][lang])		;	break;
		case AUGUST		: 	strcpy(zAux, months[AUGUST][lang])		;	break;
		case SEPTEMBER	: 	strcpy(zAux, months[SEPTEMBER][lang])	;	break;
		case OCTOBER	: 	strcpy(zAux, months[OCTOBER][lang])		;	break;
		case NOVEMBER	: 	strcpy(zAux, months[NOVEMBER][lang])	;	break;
		case DECEMBER	: 	strcpy(zAux, months[DECEMBER][lang])	;	break;
	}

	if(!contract){
		strncpy(output, zAux, strlen(zAux));
	}else{
		strncpy(output, zAux, 3);
	}

}