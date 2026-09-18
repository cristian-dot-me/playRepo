#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int main(void) {


	// do-while del nombre
	do {

		fgets(player[i].nombre, 11, stdin);
	
		invalido = validarVacio(player[i].nombre);

		if (invalido) {
			printf("Se ha ingresado un nombre vacio, ingresa de vuelta! \n");
		}

	}while(invalido);

	// do-while de la clave
	do {

		fgets(player[i].clave, 11, stdin);
	
		invalido = validarVacio(player[i].clave);

		if (invalido) {
			printf("Se ha ingresado una clave vacia, ingresa de vuelta! \n");
		}

	}while(invalido);



	return 0;
}
