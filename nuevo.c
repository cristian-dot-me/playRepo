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
	

	mascara(tablero);
	turno = 1;

	printf("\n");
	// gameloop
	do {
		printf("\n -------TURNO DEL JUGADOR: %d ------- \n", turno);
		printf("Ingrese posicion: ");

		do {
			scanf("%d", &posicion);
			if (posicion < 1 || posicion > COLUMNAS) {

			}

		}while(posicion < 1 || posicion > COLUMNAS);

		ingresarFichas(tablero, turno, posicion);

		turno = calcularTurno(turno);
		mascara(tablero);
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

	
	
	printf("\n");
	for(i = 0; i<FILAS; i++) {

		
		printf("\t |");

		for(j = 0; j<COLUMNAS; j++) {

			if (inputMatriz[i][j] == 0) {
				printf(" ");
			} else if (inputMatriz[i][j] == 1){
				printf("\x1b[31mX\x1b[37m");
			} else {
				printf("\x1b[32mO\x1b[37m");
			}
			printf("|");

		}

		printf("\n");
		
	}
	printf("\t --------------- \n");
	printf("\t |");
	for (int k = 0 ; k<COLUMNAS ; k++) {

		printf("%d|", k);

	}
	printf("\n");
	return;

}


