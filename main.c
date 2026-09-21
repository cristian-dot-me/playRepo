#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//#include "structs.h"
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

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
void 	limpiarSiDesbordo(char *buf);
int 	validarID(int id,PLAYERS players[],int cantPlayers);
void 	validarUser(char *inputstr, PLAYERS players[], int cantPlayers, int *validar, int *ub);
int 	validarString(char *InputStr);
void 	Passworduser(char *inputstr, char *inputstr2,int cantPlayers,PLAYERS player[]);
void 	calcularTurno(int *turnoInput);
void 	ingresarFichas(int tablero[][COLUMNAS], int turno, int pos);
void 	mascara(int inputMatriz[][COLUMNAS]);
void 	cargaMatriz(int inputMatriz[][COLUMNAS]);
void 	pantallaCarga(void);
int 	victoria(int inputMatriz[][COLUMNAS],int turno);
void	vaciarStdin(void);
bool 	contieneNumeros(char* inputStr);
void	bannerPrincipal(void);

int main(void) {


	int tablero[FILAS][COLUMNAS];
	int ubicacion[2]={-1,-2};
	int turno;
	int posicion;
	int cantPlayers;
	int valido;
	int validar;
	int ub;

	//----------------------auxiliares para la carga del jugador---------------
	int id;
	char charID[5];
	char aux[100];                              //<- char para validar las cadenas
	char aux2[100];

	//------------------------------------Banderas------------------------------
	int b1;
	int b2;
	bool estadoLectura 	= false;
	int estadoVictoria 	= 0;
	bool endgame		= false;
	//-------------------------------------------------------------------------------------------------------------
	//CANTIDAD DE JUGADORES A INGRESAR AL JUEGO"
	bannerPrincipal();
	printf("Bienvenido! Por favor, ingresa la cantidad de jugadores \n");
	do {

		printf("Ingrese cantidad de jugadores: ");
		scanf("%d",&cantPlayers);
		vaciarStdin();
		if (cantPlayers < 2 || cantPlayers > 900) {
			printf("La cantidad de jugadores debe estar entre 2 y 900! \n");
		}

	} while (cantPlayers < 2 || cantPlayers > 900);

	// DEFINIMOS EL VECTOR DE JUGADORES
	PLAYERS players[cantPlayers];


	printf("\n");
	printf("\t    --------Registro de jugadores--------- \n ");
	printf("Por favor complete los campos para registrar a los jugadores \n \n");
	printf("----------------------------------------------------------------- \n");
	//Logeo y validacion de ingreso de id, usuario y contraseña

	for (int i = 0 ; i < cantPlayers ; ++i) {

		do {

			if (i != 0) {
				fflush(stdin);
			} 

			printf("Ingrese ID del jugador %d: ", i+1);

			fgets(charID, sizeof(charID), stdin);
			fflush(stdin);

			if ( strlen(charID) > 1 ) {

				estadoLectura = 1;
				id = strtol(charID, NULL, 10); 

			} else {
				
				printf("No se pueden meter ID's vacias! \n");
				estadoLectura = 0;

			}

			if (estadoLectura == 0) {

				printf("No se ha ingresado un valor valido, intente de nuevo \n");
				id = 0;

			}

			if ( (id < 100 || id > 999) && estadoLectura != 0 ) {

				if ( !contieneNumeros(charID)  ) {

					printf("Solo se pueden ingresar numeros! \n");

				} else {

					printf("La ID debe ser de tres digitos! \n");

				}

				vaciarStdin();
	
			}

		} while ( id < 100 || id > 999 || validarID(id,players,cantPlayers));

		fflush(stdin);
		players[i].idplayer = id;

		//-------------------------------------------- Nombre y contraseña ----------------------------------------------------------

//		vaciarStdin();       
		printf("Ingrese usuario: ");
		fgets(aux,100,stdin);
		limpiarSiDesbordo(aux);

		valido = validarString(aux);

		do {
			if (valido == 1) {

				printf("!! ERROR !! \n");
				printf("!!Campo Vacio!! \n");
				printf("Ingrese nueva mente el campo: ");
				fgets(aux,100,stdin);
				limpiarSiDesbordo(aux);

			}

			if (valido == 2) {

			    printf("!!ERROR!! \n");
			    printf("!Ingresar porfavor un usuario de hasta 10 caracteres \n");
			    printf("Ingrese usuario: ");
			    fgets(aux,100,stdin);
			   limpiarSiDesbordo(aux);

			}
			    
			    valido = validarString(aux);

			      do {
					validar = 0;
			           validarUser(aux,players,cantPlayers,&validar,&ub);

			           if ( validar == 1 ){ 

//					printf("Error! Usuario invalido \n");
			               	printf("[ERROR]: Ese usuario ya existe \n");
			               	printf("Ingrese OTRO nombre de usuario: ");
			               	fgets(aux,100,stdin);
			               	limpiarSiDesbordo(aux);
					validarUser(aux, players, cantPlayers, &validar, &ub);

			           }

			     } while (validar == 1);

		} while (valido == 1 || valido == 2);
		///-------------------------------se asigna el valor de aux a players.player--------------------------------
		strcpy(players[i].Player,aux);


		valido = 0;
		printf("Ingrese contraseña del usuario: ");
		fgets(aux,100,stdin);
	      	limpiarSiDesbordo(aux);
		fflush(stdin);
		valido = validarString(aux);		
		do {
			if (valido == 1) {
				printf("!! ERROR !! \n");
				printf("!! Campo vacio!! \n");
				printf("Ingrese nuevamente: ");
				fgets(aux,100,stdin);
		         	limpiarSiDesbordo(aux);
				valido=validarString(aux);
			}
			
			//validacion de que la contraseña solo tenga 10 caracteres 		
			if (valido == 2){

			    printf("!!ERROR!! \n");
			    printf("!Ingresar una contraseña de hasta 10 caracteres \n");
			    printf("Ingrese contraseña del usuario: ");
			    fgets(aux,100,stdin);
			    limpiarSiDesbordo(aux);
				fflush(stdin);
			    valido=validarString(aux);

			}
			
		} while (valido == 1 || valido == 2);

	//-------------------------------se asigna el valor de aux a players.password--------------------------------
		strcpy(players[i].Password,aux);

	}
	//-------------------------------------------- start----------------------------------------------------------
	
	
	
	//---------------------------------------------Iniciar sesion--------------------------------------------------

	printf("\n Ingresa los datos de los 2 usuario que van a jugar: \n");
	do{
	for( int i = 0 ; i < 2 ; i++){

		do {
			
			printf("\n\tUsuario: ");
			fgets(aux,100,stdin);
			limpiarSiDesbordo(aux);         
			b1 = 0;
			printf("\n\tContraseña:");
			fgets(aux2,100,stdin);
        		limpiarSiDesbordo(aux2);
			validar = 0;
        		validarUser(aux, players, cantPlayers, &validar, &ub);
        		ubicacion[i]=ub;
        	if(ubicacion[0]==ubicacion[1]){
        	    printf("Error");
        	    printf("Ya esta logueado");}else{
        		b1 = validar;

			if (b1 == 0) {

				printf("Error nombre de Usuario incorrecto \n");

			}

			if (b1 == 1 && strcmp(aux2, players[ub].Password) == 0) {

				b2 = 1;

			} else {

				printf("Error: contraseña incorrecta \n");
				b2 = 0;

         		}
        	    }
         	} while(b1 == 0 || b2 == 0);
            players[ubicacion[i]].PMatches++;
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

				endgame = true;

			}
			printf("posicion: %d \n", posicion);
			if ( (posicion < 1 || posicion > COLUMNAS) && endgame == false ) {

				printf("Ingrese una posicion valida! \n Entre 1 y %d \n", COLUMNAS);

			}

		} while ( (posicion < 1 || posicion > COLUMNAS) && endgame == false);
		if (endgame == false) {
            
			ingresarFichas(tablero, turno, posicion);
			estadoVictoria = victoria(tablero, turno);
			calcularTurno(&turno);
			mascara(tablero);

		} else {

			estadoVictoria = 1;
		}
	} while ( !estadoVictoria );
	
	
	
	//-------------------------------------Estadisticas------------------------------------------
     if(turno==2 && endgame){
         
         players[ubicacion[0]].Victory++;
         
       } else if(turno==1 && endgame){
           
         players[ubicacion[1]].Victory++;
         
     }
     
     if (turno == 1 && estadoVictoria == 1) {
     
            players[ubicacion[0]].Streak++;
     
     } else {
         
         players[ubicacion[0]].Streak = 0;
         
     }
     
     if (turno == 2 && estadoVictoria == 1) {
    
            players[ubicacion[1]].Streak++;
     
     } else {
         
         players[ubicacion[1]].Streak = 0;
         
     }
     
     
     printf("Estadisticas");
     
     
     
    /*  
        juego=bueno;
        fps=muchos;
        jugaores=muchos;
        grafico=puedes correr crysys;
        bugs = ninguno;
        materias = promocionadas;
	*/
	    
	}while(1);
	
	return 0;
}

void bannerPrincipal(void) {

        printf("\t_._______\n");
        printf("\t| _______ |\n");
        printf("\t||,-----.||\n");
        printf("\t|||     |||\n");
        printf("\t|||_____|||\n");
        printf("\t|`-------'| \n");
        printf("\t| +     O | \n");
        printf("\t|      O  |\n");
        printf("\t| / /  ##,\"\n");
        printf("\t`------\"\n");
	printf("grupo eleven \n");
	printf("-> jpdd \n-> Xx_cvc_xX\n-> vea\n");

}

bool contieneNumeros(char* inputStr) {

        bool tieneNumeros = false;

        for(int i = 0 ; i<strlen(inputStr); i++) {

                int status = isdigit(inputStr[i]);

                if (status) {

                        tieneNumeros = true;
                        i = strlen(inputStr);

                }


        }

        return tieneNumeros;
}


void vaciarStdin(void) {
	
	int hola;

        while(  (hola = getchar()) != '\n' && hola != EOF);
        return;

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

			printf("[ERROR]: ID invalida! \n");
			printf("ID ya existente \n");
			validar = 1;
			i = cantPlayers;

		} else {
			validar = 0;
		}
	}
	return validar;
	
	
}

void validarUser(char *inputstr, PLAYERS players[], int cantPlayers, int *validar1, int *ub) {
	int i;
	for (i = 0; i<cantPlayers; i++) {

		if (strcmp(inputstr, players[i].Player)==0) {

			*validar1 = 1;
			*ub=i;
			i=cantPlayers;

		} else {

			*validar1 = 0;

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
//		usleep(300000);
	}


}

void ingresarFichas(int tablero[][COLUMNAS], int turno, int pos) {

	int pos2 = pos - 1;
	for (int i = FILAS; i >= 0 ; i--) {

		if (tablero[i][pos2] == 0) {
		    
			tablero[i][pos2] = turno;
			i = 0;

		}
	}

	return;
}

void calcularTurno(int *turnoInput) {

	if (*turnoInput == 1) {
		*turnoInput = 2;
	} else {
		*turnoInput = 1;
	}

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
	for (int k = 1 ; k<=COLUMNAS ; k++) {

		printf("%d|", k);

	}
	printf("\n");
	return;

}

int victoria(int inputMatriz[][COLUMNAS],int turno) {
	// recorrido horizontal

	bool victoria 	= false;
	int c1 		= 0;
	int c2	 	= 0;
	int i 		= 0;
	int j 		= 0;	
	int k 		= 0; // <-- borrar para entrega
	int l		= 0;

	for (i = 0; i < FILAS ; i++) {

		for (j = 0; j<COLUMNAS - 3; j++) {

			if (  inputMatriz[i][j] == turno && inputMatriz[i][j+1] == turno && inputMatriz[i][j+2] == turno && inputMatriz[i][j+3] == turno   ) {

				return victoria = true;	
			}
		
		}
	}


	
	for (i = 0; i < FILAS - 3; i++) {

		for (j = 0; j < COLUMNAS; j++) {
	
			if ( inputMatriz[i][j] == turno && inputMatriz[i+1][j] == turno && inputMatriz[i+2][j] == turno && inputMatriz[i+3][j] == turno ) {

				return victoria = true;	
				printf("GANADOR: %d \n", turno);
			}
	

		}
	}
	
	c1 	= 0;
	c2 	= 0;
	victoria = false;
	//recorido diagonal
	for (int i = 0; i < FILAS - 3; i++) {
		for (int j = 0; j < COLUMNAS - 3; j++) {
			turno = 1; 
			if ( (inputMatriz[i][j] == turno && inputMatriz[i+1][j+1] == turno) && (inputMatriz[i+2][j+2] == turno && inputMatriz[i+3][j+3] == turno) ) {

				return victoria = true;
				printf("inputMatrizNormal: %d ,inputMatriz+1: %d \n ", inputMatriz[i][j], inputMatriz[i+1][j+1]);
				printf("inputMatrizNormal: %d ,inputMatriz+1: %d \n ", inputMatriz[i+2][j+2], inputMatriz[i+3][j+3]);

				}
		}
	}

	// 4. Verificación Diagonal Ascendente (/)
	for (int i = 3; i < FILAS; i++) {

		for (int j = 0; j < COLUMNAS - 3; j++) {

			if (inputMatriz[i][j] == turno && inputMatriz[i-1][j+1] == turno &&

				inputMatriz[i-2][j+2] == turno && inputMatriz[i-3][j+3] == turno) {
				return victoria = true;

				}
		}

	}
	
	

	return victoria;
}



//nota el codigo esta funcional pero se debe someter a mucho test de prueba de errores
//en un momento en la carga del los datos para el registro me tiro un bucle sin motivo
// al reintentar el error del bucle no lo logre ** a tener en cuenta para el testeo 
