#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//#include "structs.h"
#include <unistd.h>

#define	FILAS 6
#define COLUMNAS 7

typedef struct {

    int idplayer;
    char Player[11];
    char Password[11];
    int Streak;
    int Victory;
    int PMatches;
    int GameCount;

}PLAYERS;
void limpiarSiDesbordo(char *buf);
int validarID(int id,PLAYERS players[],int cantPlayers);
void validarUser(char *inputstr, PLAYERS players[], int cantPlayers, int *validar, int *ub);
int validarString(char *InputStr);
void Passworduser(char *inputstr, char *inputstr2,int cantPlayers,PLAYERS player[]);
int calcularTurno(int turnoInput);
void ingresarFichas(int tablero[][COLUMNAS], int turno, int pos);
void mascara(int inputMatriz[][COLUMNAS]);
void cargaMatriz(int inputMatriz[][COLUMNAS]);
void pantallaCarga(void);
bool victoria(int inputMatriz[][COLUMNAS],int turno);

int main(void) {


	int tablero[FILAS][COLUMNAS];
	int turno;
	int posicion;
	int cantPlayers;
	int valido;
	int validar;
	int ub;
	//----------------------auxiliares para la carga del jugador---------------
	int id;

	char aux[100];                              //Char para validad las cadenas
	char aux2[100];
	bool estadoVictoria = false;
	//------------------------------------Banderas------------------------------
	int b1;
	int b2;

	//CANTIDAD DE JUGADORES A INGRESAR AL JUEGO"
	do {
		printf("Ingrese cantidad de jugadores: ");
		scanf("%d",&cantPlayers);

	} while (cantPlayers<2 || cantPlayers>900);
	getchar();
	// DEFINIMOS EL VECTOR DE JUGADORES
	PLAYERS players[cantPlayers];
     printf("\t    --------Registro de jugadores--------- \n ");
	printf("Porfavor complete los campos para registras a los jugadores \n \n");
	printf("----------------------------------------------------------------- \n");
	//Logeo y validacion de ingreso de id, usuario y contraseña
	for (int i = 0 ; i < cantPlayers ; ++i) {
		do {


			printf("Ingrese ID del jugador %d: ", i+1);

			scanf("%d", &id);

		} while ((id < 100 || id > 999)|| validarID(id,players,cantPlayers));



		players[i].idplayer=id;
		getchar();
		//-------------------------------------------- Nombre y contraseña ----------------------------------------------------------

       
		printf("Ingrese usuario: ");
		fgets(aux,100,stdin);
		limpiarSiDesbordo(aux);
		valido=validarString(aux);
		do {
			if (valido==1) {
				printf("!! ERROR !! \n");
				printf("!!Campo Vacio!! \n");
				printf("Ingrese nueva mente el campo: ");
				fgets(aux,100,stdin);
				limpiarSiDesbordo(aux);}
			if (valido==2){
			    printf("!!ERROR!! \n");
			    printf("!Igresar porfavor un usuario de hasta 10 caracteres \n");
			    printf("Ingrese usuario: ");
			    fgets(aux,100,stdin);
			   limpiarSiDesbordo(aux);}
			    
			    valido=validarString(aux);
			    
			      do{
			           validarUser(aux,players,cantPlayers,&validar,&ub);
			           if(validar==1){ 
			               printf("error Usuario invalida \n");
			               printf("User ya existente \n");
			               printf("Ingrese Un usuario");
			               fgets(aux,100,stdin);
			               limpiarSiDesbordo(aux);
			           }
			     }while(validar==1);
			
		     
			    
			    
			
		} while (valido == 1 || valido== 2);
		//-------------------------------se asigna el valor de aux a players.player--------------------------------
		strcpy(players[i].Player,aux);
		valido=0;
		printf("Ingrese contraseña del usuario: ");
		fgets(aux,100,stdin);
      	limpiarSiDesbordo(aux);
		valido=validarString(aux);
		
		do {
			if (valido==1) {
				printf("!! ERROR !! \n");
				printf("!!Campo Vacio!! \n");
				printf("Ingrese nueva mente: ");
				fgets(aux,100,stdin);
		         	limpiarSiDesbordo(aux);
				valido=validarString(aux);
			}
			
			//validacion de que la contraseña solo tenga 10 caracteres 
			
			if (valido==2){
			    printf("!!ERROR!! \n");
			    printf("!Igresar porfavor una contraseña de hasta 10 caracteres \n");
			    printf("Ingrese contraseña del usuario: ");
			    fgets(aux,100,stdin);
			     limpiarSiDesbordo(aux);
			    valido=validarString(aux);
			}
			
		} while (valido == 1 || valido == 2);
		//-------------------------------se asigna el valor de aux a players.password--------------------------------
		strcpy(players[i].Password,aux);

	}
	getchar();
	//-------------------------------------------- start----------------------------------------------------------
	
	
	
	//---------------------------------------------Iniciar secion--------------------------------------------------

    printf("Ingresa los datos de los 2 usuario que van a jugar: \n");
    for(int i=0;i<2;i++){
    	do{
    
       printf("Usuario:");
        fgets(aux,100,stdin);
       limpiarSiDesbordo(aux);

         printf("\n Contraseña:");
        fgets(aux2,100,stdin);
        limpiarSiDesbordo(aux2);
        validarUser(aux, players, cantPlayers, &validar, &ub);
        b1 = validar;
        if (b1 == 0) {
           printf("Error nombre de Usuario incorrecto\n");
        }

        if (b1 == 1 && strcmp(aux2, players[ub].Password) == 0) {
           b2 = 1;
        } else {
         printf("Erro contraseña incorrecta\n");
          b2 = 0;
         }
		
         }while(b1==0 || b2==0 );
    }
	//-------------------------------------------------------------------------------------------------------------
	cargaMatriz(tablero);
	pantallaCarga();
	printf("Para salir del juego en cualquier momento, ingrese -1 \n");
	mascara(tablero);
	turno = 1;
	printf("\n");
	// gameloop
	do {
		printf("\n -------TURNO DEL JUGADOR: %d ------- \n", turno);
		printf("Ingrese posicion: ");

		do {
			scanf("%d", &posicion);

			if (posicion == -1) {
				posicion = -93;
			}
			if (posicion < 1 || posicion > COLUMNAS) {
				printf("Ingrese una posicion valida! \n Entre 1 y %d \n", COLUMNAS);
			}

		}while(posicion < 1 || posicion > COLUMNAS);

		ingresarFichas(tablero, turno, posicion);
        victoria(tablero,turno);
		turno = calcularTurno(turno);
		mascara(tablero);
		estadoVictoria = victoria(tablero,turno);
		if (estadoVictoria == true) {
			posicion = -93;
		}

	}while(posicion == -93);


	return 0;
}

void limpiarSiDesbordo(char *buf) {
    if (strchr(buf, '\n') == NULL) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
    buf[strcspn(buf, "\n")] = '\0';
}

int validarString(char *InputStr) {
   int valido;
        if (strlen(InputStr)==1) {
          valido=1;
        }else if(strlen(InputStr)>11){
            valido=2;
        }else{valido=0;}
	return valido;

}

int validarID(int id,PLAYERS players[],int cantPlayers) {
	int i;
	int validar;
	for (i = 0; i<cantPlayers; i++) {
		if (id == players[i].idplayer) {
			printf("error id invalida \n");
			printf("id ya existente \n");
			validar = 1;
			i=cantPlayers;
		}else {
			validar = 0;
		}
	}
	return validar;
}

void validarUser(char *inputstr, PLAYERS players[], int cantPlayers, int *validar, int *ub) {
	int i;
	for (i = 0; i<cantPlayers; i++) {
		if (strcmp(inputstr, players[i].Player)==0) {
			*validar = 1;
			*ub=i;
			i=cantPlayers;
		}else {
			validar = 0;
		}
	}
}


void Passworduser(char *inputstr, char *inputstr2,int cantPlayers ,PLAYERS player[]){
     for(int i=0;i<cantPlayers;i++){
      if(inputstr==player[i].Player){
                
      }
     }
    
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

bool victoria(int inputMatriz[][COLUMNAS],int turno) {
	// recorrido horizontal

	bool victoria 	= false;
	int c1 		= 0;
	int c2	 	= 0;
	int i 		= 0;
	int j 		= 0;
	int inicio	= 0;
	int k 		= 0; // <-- borrar para entrega

	for (i=0;i<FILAS && !victoria;i++) {

		c1 	= 0;
		c2 	= 0;

		for (j=0;j<FILAS;j++) {

			if (inputMatriz[i][j] != 0 && inputMatriz[i][j] == 1) {

				c1++;

				if (inputMatriz[i][j+1] == 1) {

					c1++;
					j++;

				} else {

					c1 = 0;

				}

			} else if (inputMatriz[i][j] == 2) {

				c2++;

				if (inputMatriz[i][j+1] == 2) {

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

				for (k=0;k<FILAS; k++) {

					printf("%d \t", inputMatriz[i][k]);

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

	for (i=0;i<FILAS && !victoria;i++) {

		for (j=0;j<COLUMNAS;j++) {

			if (inputMatriz[j][i] != 0 && inputMatriz[j][i] == 1 ) {

				c1++;

				if (inputMatriz[j+1][i] == 1) {

					c1++;
					j++;

				} else {

					c1 = 0;

				}

			} else if (inputMatriz[j][i] == 2 ) {

				c2++;

				if (inputMatriz[j+1][i] == 2) {

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
			for (k=0;k<COLUMNAS;k++) {
				printf("Fila %d: %d \n", k, inputMatriz[k][i]);
			}
		}

	}
	c1 	= 0;
	c2 	= 0;


	/*
		while(flag) {

			for (i=inicio;i<control;i++) {

				for (j=0;j<orden;j++) {



				}

			}
		}
	*/
	//recorido diagonal
	for (int i = 0; i < FILAS - 3; i++) {
		for (int j = 0; j < COLUMNAS - 3; j++) {
			if (inputMatriz[i][j] == turno && inputMatriz[i+1][j+1] == turno &&
				inputMatriz[i+2][j+2] == turno && inputMatriz[i+3][j+3] == turno) {
				victoria = true;
				}
		}
	}

	// 4. Verificación Diagonal Ascendente (/)
	for (int i = 3; i < FILAS; i++) {
		for (int j = 0; j < COLUMNAS - 3; j++) {
			if (inputMatriz[i][j] == turno && inputMatriz[i-1][j+1] == turno &&
				inputMatriz[i-2][j+2] == turno && inputMatriz[i-3][j+3] == turno) {
				victoria = true;
				}
		}
		return victoria;
	}
}



















//nota el codigo esta funcional pero se debe someter a mucho test de prueba de errores
//en un momento en la carga del los datos para el registro me tiro un bucle sin motivo
// al reintentar el error del bucle no lo logre ** a tener en cuenta para el testeo 
