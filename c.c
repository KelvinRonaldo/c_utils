#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./utils.h"


int main(void){


	char str[56] = "Example of#split funcion in#C lang";
	char *result[64] = {0x00};
	int rc = 0;

	rc = isLikeChar('e', "Kelvin");

	rc ? puts("true") : puts("false");


	return 0;
}