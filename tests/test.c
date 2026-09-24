#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool tieneLetras(char* inputStr) {

	bool contieneLetras = false;

	for(int i = 0 ; i<strlen(inputStr) && !contieneLetras; i++) {

		contieneLetras = isalpha(inputStr[i]) | ispunct(inputStr[i]);

	}

	return contieneLetras;
}

int main(void) {

	char exampleStr[20];
	//strcpy(exampleStr, "21-");
	while(1) {
	fgets(exampleStr, 20, stdin);
	bool contieneLetras = tieneLetras(exampleStr);
	if (contieneLetras) {
		printf("\"%s\" tiene letras adentro! \n", exampleStr);
	} else {
		printf("%s no tiene letras adentro! \n", exampleStr);
	}
}
	return 0;
}
