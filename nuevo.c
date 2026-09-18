#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include "structs.h"
#include <unistd.h>

#define	FILAS 6
#define COLUMNAS 7

int calcularTurno(int turnoInput); 
void ingresarFichas(int tablero[][COLUMNAS], int turno, int pos);
void mascara(int inputMatriz[][COLUMNAS]);
void cargaMatriz(int inputMatriz[][COLUMNAS]); 

int main(void) {


	int tablero[FILAS][COLUMNAS];
	int turno;
	int posicion;

	cargaMatriz(tablero);
	printf("Ordenando tablero");

	for(int i=0;i < 5;i++){

	        printf(".");
		fflush(stdout);
		usleep(300000);
	}
	
	int vueltas = 0;
	mascara(tablero);
	turno = 1;

	// gameloop
	do {
		vueltas++;
		printf("Vuelta numero: %d \n", vueltas);
		printf("------------TURNO DEL JUGADOR: %d ------------- \n", turno);
		printf("Ingrese posicion: ");
		do {
			printf("VALOR DE POSICION ANTES DE LEER: %d \n", posicion);
			scanf("%d", &posicion);
			break;
		}while(posicion < 1 || posicion > COLUMNAS);


		ingresarFichas(tablero, turno, posicion);
				
/*
	for( int i = 0; i<FILAS; i++) {

		
		printf("\n |");

		for(int j = 0; j<COLUMNAS; j++) {
			
			printf("%d", tablero[i][j]);
	
			printf("|");

		}

		printf("\n");
	}
*/
		

		printf("VALOR DE POSICION DESPUES DE LLAMAR A ingresarFichas(): %d \n", posicion);	
		mascara(tablero);
		turno = calcularTurno(turno);

	}while(posicion != 7);

	
	return 0;
}
void ingresarFichas(int tablero[][COLUMNAS], int turno, int pos) {
	int pos2 = pos - 1;
	for (int i = FILAS; i > 0 ; i--) {
		if (tablero[i][pos2] == 0) {
			tablero[i][pos2] = turno;
			i = 0;
		}
	}

	return;
}
int calcularTurno(int turnoInput) {
	int outputTurno;
	if (turnoInput == 1) {
		outputTurno = 2;
	} else {
		outputTurno = 1;
	}	
	return outputTurno;
}
	
void cargaMatriz(int inputMatriz[][COLUMNAS]) {

	int i, j;

	for(i = 0; i<FILAS; i++) {

		for(j = 0; j<COLUMNAS; j++) {

			inputMatriz[i][j] = 0;

		}

	}

	return;
}
void mascara(int inputMatriz[][COLUMNAS]) {

	int i, j;

	for(i = 0; i<FILAS; i++) {

		
		printf("\n |");

		for(j = 0; j<COLUMNAS; j++) {

			if (inputMatriz[i][j] == 0) {
				printf(" ");
			} else if (inputMatriz[i][j] == 1){
				printf("X");
			} else {
				printf("O");
			}
			printf("|");

		}

		printf("\n");
	}

	return;

}


