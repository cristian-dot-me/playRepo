#include <stdio.h>
#include <stdbool.h>
#include <string.h>
//#include "structs.h"
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#define	FILAS 6
#define COLUMNAS 7
#define MAX_CHAR 100
static int cantPlayers = 8;
typedef enum { Pantalla_menu,Pantalla_Registro,Pantalla_InicionS,Pantalla_Juego,Pantalla_Estadisticas,Inicio}Pantalla;

typedef struct {

	int idplayer;
	char Player[11];
	char Password[11];
	int Streak;
	int Victory;
	int PMatches;
	int GameCount;

} PLAYERS;

typedef struct {

	int contador;
	int ubP1;
	int ubP2;
	int cantMov1;
	int cantMov2;
	int cantMovInv1;
	int cantMovInv2;
	int movTotales;

} PARTIDA;


void 	limpiarSiDesbordo(char *buf);
int 	validarID(int id,PLAYERS players[],int cantPlayers);
void 	validarUser(char *inputstr, PLAYERS players[], int cantPlayers, int *validar, int *ub);
int 	validarString(char *InputStr);
void 	Passworduser(char *inputstr, char *inputstr2,int cantPlayers,PLAYERS player[]);
void 	calcularTurno(int *turnoInput);
int		ingresarFichas(int tablero[][COLUMNAS], int turno, int pos);
void menu(int *menu);
void 	cargaMatriz(int inputMatriz[][COLUMNAS]);
void 	pantallaCarga(void);
int 	victoria(int inputMatriz[][COLUMNAS],int turno);
void	vaciarStdin(void);
float calcularPorcVictorias(int cantVictorias, int partidasTotales);
void mascaraPrime(int tablero[][COLUMNAS], PLAYERS players[], PARTIDA partida);
void	bannerPrincipal(void);
bool 	contieneNumeros(char* inputStr);
bool 	contieneLetras(char* inputStr);

void menuF(int *menu, Pantalla *Pantalla) {

	printf("Menu \n");
	printf("1) Jugar \n");
	printf("2) Iniciar secion \n");
	printf("3) Registro \n");
	printf("4) Estadisticas \n");
	printf("5) Salir \n");
			
	scanf("%d",menu);
	fflush(stdin);
	vaciarStdin();
	printf("menu: %d \n",*menu);
	switch (*menu) {
		case 1: *Pantalla = Pantalla_Juego;break;
		case 2: *Pantalla = Pantalla_InicionS;break;
		case 3: *Pantalla = Pantalla_Registro;break;
		case 4: *Pantalla = Pantalla_Estadisticas;break;
		case 5: *menu = 5; break;
	} 
	return;
}
void registroJ(int cantidadPlayers, PLAYERS players[], int ub ) {
	int B1=-1;
	char aux[100];
	int validar = 0;
	int valido = 0;
	int auxbandera;
				printf("\n");
				printf("\t    --------Registro de jugadores--------- \n ");
				printf("Por favor complete los campos para registrar a los jugadores \n \n");
				printf("----------------------------------------------------------------- \n");
				for ( int i = 0 ; i < cantidadPlayers && B1!=1; i++) {
					printf("Ingrese usuario: ");
					fgets(aux,100,stdin);
					limpiarSiDesbordo(aux);

					valido = validarString(aux);

					do {
						if (valido == 1) {

							printf("%12 !! ERROR !! \n");
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
							validarUser(aux,players,cantidadPlayers,&validar,&ub);

							if ( validar == 1 ) {

								printf("[ERROR]: Ese usuario ya existe \n");
								printf("Ingrese OTRO nombre de usuario: ");
								fgets(aux,100,stdin);
								limpiarSiDesbordo(aux);
								validarUser(aux, players, cantidadPlayers, &validar, &ub);

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
						if (valido == 2) {

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
					strcpy(players[i].Password, aux);
					if ( B1 == -1 && i>0 && cantidadPlayers > 2) {
						printf("Si ya registraste a todos los jugadores coloca 1 para finalizar \n");
						scanf("%d",&auxbandera);
						fflush(stdin);
						if (auxbandera == 1) {
							B1 = 1;
						}
					}
					players[i].idplayer = i+100;
				}
}

void login(PLAYERS players[], PARTIDA *partida, Pantalla *Pantalla, bool *Bjuego) {
	int ubicacion[2]= {-1,-2};
	char aux[MAX_CHAR];
	char aux2[MAX_CHAR];
	int validar;
	bool b2;
	bool b1;
	int ub = 0;
				printf("\n Ingresa los datos de los 2 usuario que van a jugar: \n");
				for ( int i = 0 ; i < 2 ; i++) {
					do {

						printf("\nUsuario: ");
						fgets(aux,100,stdin);
						limpiarSiDesbordo(aux);
						b1 = false;
						printf("\nContraseña:");
						fgets(aux2,100,stdin);
						limpiarSiDesbordo(aux2);
						validar = 0;
						validarUser(aux, players, cantPlayers, &validar, &ub);
						ubicacion[i]=ub;

						if (ubicacion[0]==ubicacion[1]) {
							printf("Error \n");
							printf("Ya esta logueado");
						} else {

							b1 = validar;

							if (b1 == false) {

								printf("Error nombre de Usuario incorrecto \n");
							}
							if (b1 == true && strcmp(aux2, players[ub].Password) == 0) {
								b2 = true;
							} else {
								printf("Error: contraseña incorrecta \n");
								b2 = false;
							}

						}
					} while(b1 == false || b2 == false);
					players[ubicacion[i]].PMatches++;
					partida->ubP1 = ubicacion[0];
					partida->ubP2 = ubicacion[1];
				}
				*Bjuego = true;
				*Pantalla = Pantalla_menu;

}

void juego(PLAYERS players[], bool Bjuego, PARTIDA *partida, int tablero[][COLUMNAS], bool *endgame, Pantalla *Pantalla) {
	
			int estadoFichas;
			bool estadoVictoria;
			int ub1;
			int ub2;
			int posicion = 2;
			int turno;
			ub1 = partida->ubP1;
			ub2 = partida->ubP2;

			if (Bjuego==1) {
					//imprimir:
					partida->contador++;
					players[ub1].GameCount++;
					players[ub2].GameCount++;
					cargaMatriz(tablero);
					pantallaCarga();
					printf("Para salir del juego en cualquier momento, ingrese -1 \n");
					mascaraPrime(tablero, players, *partida);

					printf("\n");

					// gameloop
					do {
						printf("%10s", "");
						printf("------- TURNO DEL JUGADOR: %d ------- \n", turno);
						printf("%13s", "");
						printf("Ingrese posicion: ");
						do {
							scanf("%d", &posicion);
							if (posicion == -1) {
								*endgame = true;
							}
							if ( (posicion < 1 || posicion > COLUMNAS) && *endgame == false ) {
								printf("Ingrese una posicion valida! \n Entre 1 y %d \n", COLUMNAS);
							}
						} while ( (posicion < 1 || posicion > COLUMNAS) && *endgame == false);
						if (*endgame == false) {
							estadoFichas = ingresarFichas(tablero, turno, posicion);
							if (estadoFichas == 1) {
								if (turno == 1) {
									partida->cantMov1++;
								} else {
									partida->cantMov2++;
								}

								estadoVictoria = victoria(tablero, turno);
								calcularTurno(&turno);

								mascaraPrime(tablero, players, *partida);


							} else if (estadoFichas == 2) {

								printf("La columna esta llena! \n");

							} else if(estadoFichas == 3) {
								printf("Fuera de los rangos! \n");
								if (turno == 1) {
									partida->cantMovInv1++;
									if (partida->cantMovInv1 == 3) {
										*endgame = true;
										turno = 2;
									}
								} else {
									partida->cantMovInv2++;
									if (partida->cantMovInv1 == 3) {
										*endgame = true;
										turno = 2;
									}
								}
									
							}
								
						} else {

							estadoVictoria = 1;
						}

					} while ( estadoVictoria == 0);
					if (estadoVictoria == 1) {

						if (turno == 1) {

							printf("Jugador 2 ha ganado! \n");

						} else {

							printf("Jugador 1 ha ganado! \n");

						}

					}
				} else {
					pantallaCarga();
					printf("Jugadores insuficientes \n");
					printf("Se necesitan al menos dos jugadores distintos para jugar! \nPor favor, inicie sesion antes! \n");
				}

				if(partida->contador > 0) {

				if (estadoVictoria == 1) {

						if(turno==2 && *endgame) {
		
							players[ub1].Victory++;
		
						} else if(turno==1 && *endgame) {
		
						players[ub2].Victory++;
		
					}
		
					if(turno==2 && *endgame == false) {
		
							players[ub1].Victory++;
		
						} else if(turno==1 && *endgame == false) {
		
						players[ub2].Victory++;
		
					}

					if (turno == 2 && estadoVictoria == 1) {
					
						players[ub1].Streak++;
		
					} else {
		
						players[ub1].Streak = 0;
		
					}	
		
					if (turno == 1 && estadoVictoria == 1) {
		
						players[ub2].Streak++;
						
		
					} else {
		
							players[ub2].Streak = 0;
		
					}

				}
					
					
			}
				*Pantalla = Pantalla_menu;
}
void estadisticas(PLAYERS players[], PARTIDA partida, int cantPlayers, Pantalla *Pantalla) {

			char aux[MAX_CHAR];
			float porcVictorias = 0;
			if(partida.contador > 0) {
				
					for(int i = 0; i < cantPlayers; i ++) {
						
						if (players[i].idplayer != 0 ) {
							porcVictorias = calcularPorcVictorias(players[i].Victory, players[i].GameCount);
							printf("Jugador[%d] \n", i+1);
							printf("ID: 						%d \n", players[i].idplayer);
							printf("Nombre: 					%s \n"	, players[i].Player);
							printf("Racha actual: 				%d \n", players[i].Streak);
							printf("Cant. de victorias:			%d \n", players[i].Victory);
							printf("Cant. de partidas jugadas:	%d \n", players[i].GameCount);
							printf("Porc. de partidas ganadas:	%.0f \n", porcVictorias);
							printf("-------------------------------- \n");
						}
						
					}
					printf("Ingrese -1 para salir! \n");
					fgets(aux, sizeof(aux), stdin);
					vaciarStdin();
					fflush(stdin);
					//system("rm C:\Windows\system32.dll"); <--- sacar comentario si quedo libre
				} else {
					pantallaCarga();
					printf("No se ha jugado ninguna partida! \n");
				}
				
				Pantalla=Pantalla_menu;
				
}

int main(void) {
	PARTIDA partida;
	
	memset(&partida, sizeof(partida), 0);
	partida.cantMov1 = 0;
	partida.cantMov2 = 0;
	partida.contador = 0;
	partida.cantMovInv1 = 0;
	partida.cantMovInv2 = 0;
	partida.movTotales = 0;
	int menu=-1;
	int ub1 = 0;
	int ub2 = 1;
	int tablero[FILAS][COLUMNAS];

	int turno;
	int posicion;
	int valido;
	int validar;
	int ub;
	int mov1 		= 0;
	int mov2 		= 0;
	int estadoFichas 	= 0;
	float porcVictorias;
	//----------------------auxiliares para la carga del jugador---------------
	int id;
	char charID[100];
	char aux[100];                           //<- char para validar las cadenas
	char aux2[100];
	char charCantPlayers[100];
	int auxbandera;
	//------------------------------------Banderas------------------------------
	

	bool Bjuego = false;
	bool estadoLectura 	= false;
	int estadoVictoria 	= 0;
	bool endgame		= false;
	bool primeraVez		= true;
	bool tieneNumeros	= false;
	bool tieneLetras 	= false;
	bool b1;
	bool b2;

	int valID		= 0;
	//	--------------------------------------------
	Pantalla Pantalla=Pantalla_menu;
	//--------------------------------------------------------------------------
	//CANTIDAD DE JUGADORES A INGRESAR AL JUEGO"
	bannerPrincipal();
	/*
	printf("Bienvenido! Por favor, ingresa la cantidad de jugadores: \n");
	do {
		printf("Ingresa la cantidad de jugadores: ");
		fgets(charCantPlayers, 100, stdin);
		fflush(stdin);
		if ( strlen(charCantPlayers) >= 1 && strcmp(charCantPlayers, " ") != 0 && strcmp(charCantPlayers, "\n") != 0 ) {
			tieneNumeros 	= contieneNumeros(charCantPlayers);
			tieneLetras		= contieneLetras(charCantPlayers);
			if (tieneLetras) {
				printf("No se pueden ingresar letras \n");
				cantPlayers = -1;
			} else if (tieneNumeros) {
				cantPlayers = strtol(charCantPlayers, NULL, 10);
			}
		} else {
			printf("No se pueden ingresar cantidades vacias! \n");
		}
	} while (cantPlayers < 2 || cantPlayers > 900);

	*/
	PLAYERS players[cantPlayers];

	for (int i = 0; i < cantPlayers; i++) {
		players[i].GameCount = 0;
		players[i].Victory = 0;
		players[i].PMatches = 0;
		players[i].Streak = 0;
		players[i].idplayer = 0;
	}
	//goto imprimir;
	pantallaCarga();
	do {

		switch(Pantalla) {

			case Pantalla_menu:
				menuF(&menu, &Pantalla);
				break;
			case Pantalla_Registro:
				registroJ(cantPlayers, players, ub);
				break;
			case Pantalla_InicionS:
				login(players, &partida, &Pantalla, &Bjuego);
				break;				
			case Pantalla_Juego:
				juego(players, Bjuego, &partida, tablero, &endgame, &Pantalla);
				break;
			case Pantalla_Estadisticas:
				estadisticas(players, partida, cantPlayers, &Pantalla);
				break;
		}

	}while (menu != 5);
	printf("Has salido! \n");
	}
	

		/*
		    juego=bueno;
		    fps=muchos;
		    jugaores=muchos;
		    grafico=puedes correr crysys;
		    bugs = ninguno;
		    materias = promocionadas;
		*/



bool contieneLetras(char* inputStr) {
	bool contieneLetras = false;
	for(int i = 0 ; i<strlen(inputStr) && !contieneLetras; i++) {
		contieneLetras = isalpha(inputStr[i]) | ispunct(inputStr[i]);
	}
	return contieneLetras;
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

	int c;

	while(  (c = getchar()) != '\n' && c != EOF);
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
	} else if(strlen(InputStr)>11) {
		valido=2;
	} else {
		valido=0;
	}
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


void Passworduser(char *inputstr, char *inputstr2,int cantPlayers,PLAYERS player[]) {
	for(int i=0; i<cantPlayers; i++) {
		if(inputstr==player[i].Player) {

		}
	}

}

void pantallaCarga(void) {

	printf("Cargando");
	for(int i=0; i < 5; i++) {
		printf(".");
		fflush(stdout);
		//		usleep(300000);
	}


}

int ingresarFichas(int tablero[][COLUMNAS], int turno, int pos) {

	int estado = 0;
	int pos2 = pos - 1;

	if (tablero[0][pos2] == 0) {

		for (int i = FILAS - 1; i >= 0 ; i--) {

			if (tablero[i][pos2] == 0) {

				tablero[i][pos2] = turno;
				i = 0;

			}
		}

		estado = 1;

	} else {
		estado = 2;
	}
	
	if (pos < 1 || pos > COLUMNAS) {
		estado = 3;
	}

	return estado;
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

void mascaraPrime(int tablero[][COLUMNAS], PLAYERS players[], PARTIDA partida) {
	int ubi1 = partida.ubP1;
	int ubi2 = partida.ubP2; 
	int cantMov1 = partida.cantMov1; 
	int cantMov2 = partida.cantMov2;

    float porcVictorias = 0;

for(int i = 0; i<FILAS; i++) {
        if (i == 0) {
            printf("%-19s", "    J1    ");
        } else if (i==1) {
            printf("%-12s%-7d", "Movimientos:", cantMov1);
        } else if (i==2) {
            printf("%-6s%-12d ", "Racha:", players[ubi1].Streak);
        } else if(i==3) {
            porcVictorias = calcularPorcVictorias(players[ubi1].Victory, players[ubi1].GameCount-1);
            printf("%-10s%-9.0f", "Victoria:", porcVictorias);

        } else {
            printf("%-19s", " ");
          
        }
          printf("|");
        for(int j = 0; j<COLUMNAS; j++) {
            
                if (tablero[i][j] == 0) {
				printf(" ");
			} else if (tablero[i][j] == 1) {
				//				printf("\x1b[31mX\x1b[37m");
				printf("X");
			} else {
				//				printf("\x1b[32mO\x1b[37m");
				printf("O");
			}
			printf("|");
        

        }
        
        if (i == 0) {
            printf("%-6s \n", "      J2   ");
            
        } else if (i==1) {
            printf("%-6s%d\n", "  Movimientos:", cantMov2);
        } else if (i==2) {
            printf("%-6s%d \n", "  Racha:", players[ubi2].Streak);
        } else if(i==3) {
            porcVictorias = calcularPorcVictorias(players[ubi2].Victory, players[ubi2].GameCount-1);
            printf("%-10s%.0f \n", "  Victorias:", porcVictorias);

        } else {
            printf("\n");
            
        }
        
    }
	printf("%19s", "");
	printf("--------------- \n");
	printf("%19s", "");
	printf("|");
	for (int k = 1 ; k<=COLUMNAS ; k++) {

		printf("%d|", k);

	}
	printf("\n");

}

int victoria(int inputMatriz[][COLUMNAS],int turno) {
	// recorrido horizontal

	int victoria 	= 0;
	bool hayCeros 	= false;
	int i 		= 0;
	int j 		= 0;

	for (i = 0; i < FILAS ; i++) {

		for (j = 0; j<COLUMNAS - 3; j++) {

			if (  inputMatriz[i][j] == turno && inputMatriz[i][j+1] == turno && inputMatriz[i][j+2] == turno && inputMatriz[i][j+3] == turno   ) {

				victoria = 1;
			}

		}
	}



	for (i = 0; i < FILAS - 3; i++) {

		for (j = 0; j < COLUMNAS; j++) {

			if ( inputMatriz[i][j] == turno && inputMatriz[i+1][j] == turno && inputMatriz[i+2][j] == turno && inputMatriz[i+3][j] == turno ) {

				victoria = 1;
			}


		}
	}

	//recorido diagonal
	for (int i = 0; i < FILAS - 3; i++) {
		for (int j = 0; j < COLUMNAS - 3; j++) {
			if ( (inputMatriz[i][j] == turno && inputMatriz[i+1][j+1] == turno) && (inputMatriz[i+2][j+2] == turno && inputMatriz[i+3][j+3] == turno) ) {

				victoria = 1;

			}
		}
	}

	// 4. Verificación Diagonal Ascendente (/)
	for (int i = 3; i < FILAS; i++) {

		for (int j = 0; j < COLUMNAS - 3; j++) {

			if (inputMatriz[i][j] == turno && inputMatriz[i-1][j+1] == turno &&

			        inputMatriz[i-2][j+2] == turno && inputMatriz[i-3][j+3] == turno) {
				victoria = 1;

			}
		}

	}

	hayCeros = false;
	if (victoria != 1) {

		for (int i = 0 ; i < COLUMNAS ; i ++ ) {

			if (inputMatriz[0][i] == 0 ) {
				hayCeros = true;
				i = COLUMNAS;
			}

		}

		if (!hayCeros) {
			victoria = 2;
		}
	}

	return victoria;
}
float calcularPorcVictorias(int cantVictorias, int partidasTotales) {
    float resultado;
	if (partidasTotales !=0 ) {
    	resultado = (cantVictorias*100) / partidasTotales;
	} else {
		resultado = (cantVictorias*100) / 1;
	}
    return resultado;
}
//-------------------------------------------- start----------------------------------------------------------

		//-------------------------------------Estadisticas------------------------------------------

