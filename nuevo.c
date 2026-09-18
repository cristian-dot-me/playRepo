#include <stdio.h>
#include <stdbool.h> 
#include <string.h>
#include "structs.h"
#include <unistd.h>

#define	FILAS 6
#define COLUMNAS 7
                      
typedef struct {      

    int idplayer;     
    char Player[10];  
    char Password[11];
    int Streak;       
    int Victory;      
    int PMatches;     
    int GameCount;    

}Player;              


void Vstring(char *InputStr);
int calcularTurno(int turnoInput); 
void ingresarFichas(int tablero[][COLUMNAS], int turno, int pos);
void mascara(int inputMatriz[][COLUMNAS]);
void cargaMatriz(int inputMatriz[][COLUMNAS]); 
void pantallaCarga(void);

int main(void) {


	int tablero[FILAS][COLUMNAS];
	int turno;
	int posicion;
	int CantPlayers;
	//CANTIDAD DE JUGADORES A INGRESAR AL JUEGO"                      
	do {                                                              
		printf("Ingrese Cantidades de Jugadores");                    
		scanf("%d",&CantPlayers);                                     
	}while (CantPlayers<2 || CantPlayers>900);                        
                                                                  
	// DEFINIMOS EL VECTOR DE JUGADORES                               
	Player Players[CantPlayers];                                      
                                                                  
	//VALIDACION de ingreso de id,usuario y contraseña                
	for (int i = 0; i < CantPlayers; ++i) {                           
		do {                                                          
			printf("Ingrese Id del Jugador %d :",i);                   
			scanf("%d", &Players[i].idplayer);                          
		} while (Players[i].idplayer<100 || Players[i].idplayer>999); 
		getchar();
		printf("----------------------------- \n");                      
		printf("Ingrese nombre del usuario:");                        
		Vstring(Players[i].Player);                                
		printf("\n Ingrese Contraseña del Usuario;");                    
		Vstring(Players[i].Password);                               
	}                                                                 
        
	// JUEGO PRINCIPAL

	cargaMatriz(tablero);
	pantallaCarga();

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

void Vstring(char *InputStr) {                     

    do {                                           
        fgets(InputStr,11,stdin);                  

        if (strlen(InputStr)==1) {                 
            printf("!! ERROR !! \n");                 
            printf("!!Campo Vacio!! \n");             
            printf("Ingrese nueva mente el campo: ");
                                                   
        }                                          
    } while (strlen(InputStr)==1);                 
                                                   
}                                                  

void pantallaCarga(void) {
	
	printf("Cargando");
	for(int i=0;i < 5;i++){
	        printf(".");
		fflush(stdout);
		usleep(300000);
	}
	

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
				// sacar comentario para printer con colores en
				// ;inux
//				printf("\x1b[31mX\x1b[37m");
				printf("X");
			} else {
				// sacar comentario para printer con colores en
				// ;inux
//				printf("\x1b[32mO\x1b[37m");
				printf("O");
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

bool victoria(int m[][6], int orden) {

	
	
	// recorrido horizontal

	bool victoria 	= false;
	int c1 		= 0;
	int c2	 	= 0;
	int i 		= 0;
	int j 		= 0;
	int inicio	= 0;
	int k 		= 0; // <-- borrar para entrega

	for (i=0;i<orden && !victoria;i++) {

		c1 	= 0;
		c2 	= 0;

		for (j=0;j<orden;j++) {

			if (m[i][j] != 0 && m[i][j] == 1) {

				c1++;

				if (m[i][j+1] == 1) {

					c1++;
					j++;	

				} else {

					c1 = 0;

				}

			} else if (m[i][j] == 2) {

				c2++;

				if (m[i][j+1] == 2) {

					c2++;
					j++;

				} else {

					c2 = 0;

				}

			}

			if (c1 >= 4 || c2 >= 4) {

				printf("Valor de c1: %d \n", c1);
				printf("Valor de c2: %d \n", c2);
				victoria = true;
				printf("[VICTORIA_F]: La siguiente fila cumple con la condicion de victoria: \n");

				for (k=0;k<orden; k++) {

					printf("%d \t", m[i][k]);

				}
				printf("\n");
			}

		}

	}

	if (victoria) {
		return victoria;
	}


	// comprobacion en vertical
	c1 = 0;
	c2 = 0;
	j = 0;
	i = 0;
	k = 0;

	for (i=0;i<orden && !victoria;i++) {

		for (j=0;j<orden;j++) {

			if (m[j][i] != 0 && m[j][i] == 1 ) {

				c1++;

				if (m[j+1][i] == 1) {

					c1++;
					j++;

				} else {

					c1 = 0;

				}
			
			} else if (m[j][i] == 2 ) {

				c2++;

				if (m[j+1][i] == 2) {

					c2++;
					j++;

				} else {

					c2 = 0;			

				}
			} 


		}

	
		if (c1 >= 4 || c2 >= 4) {
			victoria = true;
			printf("Condicion de victoria dentro de una COLUMNA \n");
			for (k=0;k<orden;k++) {
				printf("Fila %d: %d \n", k, m[k][i]);
			}
		}

	}

	if (victoria) {
		return victoria;
	}

	c1 	= 0;
	c2 	= 0;

	while(flag) {

		for (i=inicio;i<control;i++) {

			for (j=0;j<orden;j++) {

						

			}

		}
	}

	return victoria;

}

