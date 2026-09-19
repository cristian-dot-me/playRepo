#include <stdio.h>
#include <ctype.h>
#include <string.h>
int main(void) {

	char input1[11];
	char input2[11];

	do { 
		printf("Ingresar input1: ");
		fgets(input1, 11, stdin);
		printf("Contenido de input1: %s \n", input1);
		printf("Longitud de input1: %ld \n", strlen(input1));

		getchar(); // <- ???
		// funcion para limpiar buffer del stdin
		while(getchar() != '\n');
		printf("Ingresar input2: ");
		fgets(input2, 11, stdin);
		printf("Contenido de input2: %s \n", input2);
		printf("Longitud de input2: %ld \n", strlen(input2));


	}while(1);

}
