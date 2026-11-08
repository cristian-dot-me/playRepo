#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define FILAS 6
#define COLUMNAS 7
#define MAX_CHAR 100
#define MAX_PLAYERS 8
#define LARGO_CAMPO 10      /* maximo de caracteres de usuario y contraseña */
#define LARGO_CLAVE_MIN 6   /* minimo de caracteres de la contraseña */
#define MAX_FALTAS 3        /* faltas consecutivas que descalifican a un jugador */
/* ===== Precarga de jugadores (debug) ===== */
#define CANT_PRECARGADOS 3

#define USER_1  "juanpablo"
#define PASS_1  "juan1234"
#define PART_1  10      /* partidas jugadas */
#define VICT_1  6       /* victorias */
#define RACHA_1 2

#define USER_2  "cristian"
#define PASS_2  "crist1234"
#define PART_2  8
#define VICT_2  3
#define RACHA_2 0

#define USER_3  "valentino"
#define PASS_3  "valen1234"
#define PART_3  5
#define VICT_3  1
#define RACHA_3 1

typedef enum { Pantalla_menu, Pantalla_Registro, Pantalla_InicionS, Pantalla_Juego, Pantalla_Estadisticas, Inicio, Fin } Pantalla;

/* Resultados que devuelve victoria() */
typedef enum { EN_CURSO = 0, GANA_ALGUIEN = 1, EMPATE = 2 } EstadoPartida;

/* Motivo por el que termino la partida (se guarda en PARTIDA) */
typedef enum { MOTIVO_NINGUNO = 0, MOTIVO_CUATRO_EN_LINEA = 1, MOTIVO_EMPATE = 2, MOTIVO_ABANDONO = 3, MOTIVO_FALTAS = 4 } MotivoFin;

typedef struct {
        int idplayer;
        char Player[LARGO_CAMPO + 1];
        char Password[LARGO_CAMPO + 1];
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
        int cantMovInv1;        /* faltas (movimientos invalidos) del jugador 1 en la partida */
        int cantMovInv2;        /* faltas (movimientos invalidos) del jugador 2 en la partida */
        int movTotales;
        int ganador;            /* 1, 2 o 0 si hubo empate */
        MotivoFin motivo;
} PARTIDA;

/* ===================== PROTOTIPOS ===================== */

/* --- Entrada de datos --- */
/*
        Nombre:         vaciarStdin
        Tipo:           Procedimiento
        Funcionamiento: Descarta caracteres del buffer de entrada hasta el '\n'.
*/
void vaciarStdin(void);
/*
        Nombre:         limpiarSiDesbordo
        Tipo:           Procedimiento
        Funcionamiento: Si el texto leido no termino en '\n' vacia el buffer; luego quita el '\n'.
        Entrada/Salida: buf
*/
void limpiarSiDesbordo(char *buf);
/*
        Nombre:         leerLinea
        Tipo:           Procedimiento
        Funcionamiento: Lee una linea completa (fgets) y la deja sin '\n' ni sobrante en el buffer.
        Entrada:        tam
        Salida:         buf
*/
void leerLinea(char *buf, int tam);
/*
        Nombre:         leerEntero
        Tipo:           Funcion
        Funcionamiento: Lee un entero y vacia el buffer. Si lo ingresado no es un numero devuelve 0.
        Salida:         numero leido
*/
int leerEntero(void);
/*
        Nombre:         esperarEnter
        Tipo:           Procedimiento
        Funcionamiento: Muestra un aviso y espera que se presione ENTER.
*/
void esperarEnter(void);

/* --- Validaciones --- */
/*

        Nombre:         validarString
        Tipo:           Funcion
        Funcionamiento: Devuelve 0 si el texto es valido, 1 si esta vacio, 2 si supera LARGO_CAMPO.
        Entrada:        InputStr
*/
int validarString(char *InputStr);
/*
        Nombre:         validarClave
        Tipo:           Funcion
        Funcionamiento: Devuelve 0 si la clave es valida, 1 si esta vacia, 2 si supera LARGO_CAMPO, 3 si tiene menos de LARGO_CLAVE_MIN.
        Entrada:        InputStr
*/
int validarClave(char *InputStr);
/*
        Nombre:         validarUser
        Tipo:           Procedimiento
        Funcionamiento: Busca inputstr entre los jugadores registrados. Si existe escribe 1 en validar1 y su ubicacion en ub; si no, 0 y -1.
        Entrada:        inputstr, players, cantidad
        Salida:         validar1, ub
*/
void validarUser(char *inputstr, PLAYERS players[], int cantidad, int *validar1, int *ub);
/*
        Nombre:         contarRegistrados
        Tipo:           Funcion
        Funcionamiento: Cuenta cuantos jugadores ya estan registrados (idplayer != 0).
*/
int contarRegistrados(PLAYERS players[]);

/* --- Menu y pantallas --- */
void mostrarMenu(void);
void menuF(Pantalla *pantalla);
void bannerPrincipal(void);
void pantallaCarga(void);

/* --- Registro --- */
/*
        Nombre:         pedirCampo
        Tipo:           Procedimiento
        Funcionamiento: Muestra el mensaje y pide un texto hasta que sea valido (no vacio, hasta LARGO_CAMPO).
        Entrada:        mensaje
        Salida:         destino
*/
void pedirCampo( char *mensaje, char *destino);
/*
        Nombre:         pedirClave
        Tipo:           Procedimiento
        Funcionamiento: Muestra el mensaje y pide una clave hasta que sea valida (entre LARGO_CLAVE_MIN y LARGO_CAMPO caracteres).
        Entrada:        mensaje
        Salida:         destino
*/
void pedirClave(const char *mensaje, char *destino);
/*
        Nombre:         pedirUsuarioNuevo
        Tipo:           Procedimiento
        Funcionamiento: Pide un nombre de usuario valido y que no exista todavia.
        Entrada:        players
        Salida:         destino
*/
void pedirUsuarioNuevo(PLAYERS players[], char *destino);
bool preguntarFin(void);
void registroJ(PLAYERS players[], Pantalla *pantalla);

/* --- Login --- */
/*
        Nombre:         pedirCredenciales
        Tipo:           Funcion
        Funcionamiento: Pide usuario y contraseña hasta que sean correctos y el usuario sea distinto de ubExcluido.
        Entrada:        players, ubExcluido
        Salida:         ubicacion del jugador en players
*/
int pedirCredenciales(PLAYERS players[], int ubExcluido);
void login(PLAYERS players[], PARTIDA *partida, Pantalla *pantalla, bool *Bjuego);

/* --- Tablero --- */
void cargaMatriz(int inputMatriz[][COLUMNAS]);
void calcularTurno(int *turnoInput);
void ingresarFichas(int tablero[][COLUMNAS], int turno, int pos, int *estado);
bool hayCuatroEnLinea(int m[][COLUMNAS], int turno, int fila, int col, int df, int dc);
bool hayVictoria(int m[][COLUMNAS], int turno);
bool tableroLleno(int m[][COLUMNAS]);
int victoria(int inputMatriz[][COLUMNAS], int turno);

/* --- Pantalla de juego (dibujo) --- */
void imprimirLadoIzquierdo(int fila, PLAYERS jugador, int movimientos);
void imprimirLadoDerecho(int fila, PLAYERS jugador, int movimientos);
void imprimirFilaTablero(int tablero[][COLUMNAS], int fila);
void imprimirNumerosColumnas(void);
void mascaraPrime(int tablero[][COLUMNAS], PLAYERS players[], PARTIDA partida);

/* --- Partida --- */
void iniciarPartida(PARTIDA *partida, int tablero[][COLUMNAS]);
/*
        Nombre:         leerPosicion
        Tipo:           Funcion
        Funcionamiento: Lee la columna elegida. No valida el rango: eso lo hace ingresarFichas para poder contar la falta.
        Salida:         columna ingresada (-1 si el jugador quiere salir)
*/
int leerPosicion(void);
/*
        Nombre:         registrarMovimiento
        Tipo:           Procedimiento
        Funcionamiento: Suma un movimiento valido al jugador "turno" y a los movimientos totales de la partida.
        Entrada:        turno
        Entrada/Salida: partida
*/
void registrarMovimiento(PARTIDA *partida, int turno);
/*
        Nombre:         registrarFalta
        Tipo:           Procedimiento
        Funcionamiento: Suma una falta (movimiento invalido) al jugador "turno".
        Entrada:        turno
        Entrada/Salida: partida
*/
void registrarFalta(PARTIDA *partida, int turno);
/*
        Nombre:         jugarPartida
        Tipo:           Procedimiento
        Funcionamiento: Ejecuta los turnos hasta que alguien gana, abandona, es descalificado por MAX_FALTAS faltas consecutivas o hay empate.
        Salida:         partida (ganador y motivo)
*/
void jugarPartida(int tablero[][COLUMNAS], PLAYERS players[], PARTIDA *partida);
void mostrarResultado(PARTIDA partida);
/*
        Nombre:         registrarResultado
        Tipo:           Procedimiento
        Funcionamiento: Actualiza las estadisticas (partidas jugadas, victorias y racha) de los dos jugadores segun partida->ganador.
        Entrada/Salida: players, partida
*/
void registrarResultado(PLAYERS players[], PARTIDA *partida);
/*
        Nombre:         textoMotivo
        Tipo:           Funcion
        Funcionamiento: Devuelve el texto que describe el motivo de finalizacion.
        Entrada:        motivo
*/
const char *textoMotivo(MotivoFin motivo);
void informeJugador(PLAYERS jugador, int numero, int movimientos, int faltas);
/*
        Nombre:         informeFinal
        Tipo:           Procedimiento
        Funcionamiento: Muestra el informe de cierre: motivo, duracion en turnos y, por jugador, movimientos, faltas, porcentaje de victorias y racha.
        Entrada:        players, partida
*/
void informeFinal(PLAYERS players[], PARTIDA partida);
void juego(PLAYERS players[], bool Bjuego, PARTIDA *partida, int tablero[][COLUMNAS], Pantalla *pantalla);

/* --- Estadisticas --- */
float calcularPorcVictorias(int cantVictorias, int partidasTotales);
void mostrarJugador(PLAYERS jugador, int numero);
void listarJugadores(PLAYERS players[]);
void estadisticas(PLAYERS players[], Pantalla *pantalla);
void precargarJugadores(PLAYERS players[]);
void iniciarJugadores(PLAYERS players[]);

/* ===================== MAIN ===================== */

int main(void) {

        bool finJuego = false;
        bool Bjuego = false;            /* pasa a true cuando hay 2 jugadores logueados */
        PLAYERS players[MAX_PLAYERS];
        int tablero[FILAS][COLUMNAS];
        PARTIDA partida;
        Pantalla pantalla = Pantalla_menu;

        memset(&partida, 0, sizeof(partida));
        iniciarJugadores(players);
	precargarJugadores(players);
        bannerPrincipal();
        pantallaCarga();
        do {
                switch (pantalla) {
                        case Pantalla_menu:
                                menuF(&pantalla);
                                break;
                        case Pantalla_Registro:
                                registroJ(players, &pantalla);
                                break;
                        case Pantalla_InicionS:
                                login(players, &partida, &pantalla, &Bjuego);
                                break;
                        case Pantalla_Juego:
                                juego(players, Bjuego, &partida, tablero, &pantalla);
                                break;
                        case Pantalla_Estadisticas:
                                estadisticas(players, &pantalla);
                                break;
                        default:
                                break;
                }
                finJuego = (pantalla == Fin);
        } while (!finJuego);

        printf("Has salido! \n");
        return 0;
}

void iniciarJugadores(PLAYERS players[]) {
        for (int i = 0; i < MAX_PLAYERS; i++) {
                players[i].idplayer = 0;
                players[i].Player[0] = '\0';
                players[i].Password[0] = '\0';
                players[i].Streak = 0;
                players[i].Victory = 0;
                players[i].PMatches = 0;
                players[i].GameCount = 0;
        }
}

/* ===================== ENTRADA DE DATOS ===================== */

void vaciarStdin(void) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
}

void limpiarSiDesbordo(char *buf) {
        if (strchr(buf, '\n') == NULL) {
                vaciarStdin();
        }
        buf[strcspn(buf, "\n")] = '\0';
}

void leerLinea(char *buf, int tam) {
        if (fgets(buf, tam, stdin) == NULL) {
                buf[0] = '\0';
        } else {
                limpiarSiDesbordo(buf);
        }
}

int leerEntero(void) {
        int numero = 0;
        if (scanf("%d", &numero) != 1) {
                numero = 0;
        }
        vaciarStdin();
        return numero;
}

/* ===================== VALIDACIONES ===================== */

int validarString(char *InputStr) {
        int valido = 0;
        if (strlen(InputStr) == 0) {
                valido = 1;
        } else if (strlen(InputStr) > LARGO_CAMPO) {
                valido = 2;
        }
        return valido;
}

int validarClave(char *InputStr) {
        int valido = validarString(InputStr);
        if (valido == 0 && strlen(InputStr) < LARGO_CLAVE_MIN) {
                valido = 3;
        }
        return valido;
}

void validarUser(char *inputstr, PLAYERS players[], int cantidad, int *validar1, int *ub) {
        int i = 0;
        *validar1 = 0;
        *ub = -1;
        while (i < cantidad && *validar1 == 0) {
                if (players[i].idplayer != 0 && strcmp(inputstr, players[i].Player) == 0) {
                        *validar1 = 1;
                        *ub = i;
                }
                i++;
        }
}

int contarRegistrados(PLAYERS players[]) {
        int cant = 0;
        for (int i = 0; i < MAX_PLAYERS; i++) {
                if (players[i].idplayer != 0) {
                        cant++;
                }
        }
        return cant;
}  

/* ===================== MENU Y PANTALLAS ===================== */

void mostrarMenu(void) {
        printf("\n############################\n");
        printf("###          MENU        ###\n");
        printf("############################\n");
        printf("1) Jugar \n");
        printf("2) Iniciar sesión \n");
        printf("3) Registro \n");
        printf("4) Estadísticas \n");
        printf("5) Salir \n");
}

void menuF(Pantalla *pantalla) {
        mostrarMenu();
        switch (leerEntero()) {
                case 1: *pantalla = Pantalla_Juego; break;
                case 2: *pantalla = Pantalla_InicionS; break;
                case 3: *pantalla = Pantalla_Registro; break;
                case 4: *pantalla = Pantalla_Estadisticas; break;
                case 5: *pantalla = Fin; break;
                default: printf("Opcion invalida! \n"); break;
        }
}

void pantallaCarga(void) {
        printf("Cargando");
        for (int i = 0; i < 5; i++) {
                printf(".");
                fflush(stdout);
                // sleep(1);
        }
}


/* ===================== REGISTRO ===================== */

void pedirCampo( char *mensaje, char *destino) {
        char aux[MAX_CHAR];
        int valido;
        do {
                printf("%s", mensaje);
                leerLinea(aux, MAX_CHAR);
                valido = validarString(aux);
                if (valido == 1) {
                        printf("!! ERROR !! Campo vacio \n");
                } else if (valido == 2) {
                        printf("!! ERROR !! Maximo %d caracteres \n", LARGO_CAMPO);
                }
        } while (valido != 0);
        strcpy(destino, aux);
}

void pedirClave(const char *mensaje, char *destino) {
        char aux[MAX_CHAR];
        int valido;
        do {
                printf("%s", mensaje);
                leerLinea(aux, MAX_CHAR);
                valido = validarClave(aux);
                if (valido == 1) {
                        printf("!! ERROR !! Campo vacio \n");
                } else if (valido == 2) {
                        printf("!! ERROR !! Maximo %d caracteres \n", LARGO_CAMPO);
                } else if (valido == 3) {
                        printf("!! ERROR !! Minimo %d caracteres \n", LARGO_CLAVE_MIN);
                }
        } while (valido != 0);
        strcpy(destino, aux);
}

void pedirUsuarioNuevo(PLAYERS players[], char *destino) {
        char aux[LARGO_CAMPO + 1];
        int existe;
        int ub;
        do {
                pedirCampo("Ingrese usuario: ", aux);
                validarUser(aux, players, MAX_PLAYERS, &existe, &ub);
                if (existe == 1) {
                        printf("[ERROR]: Ese usuario ya existe \n");
                }
        } while (existe == 1);
        strcpy(destino, aux);
}

bool preguntarFin(void) {
        printf("Si ya registraste a todos los jugadores coloca 1 para finalizar \n");
        return leerEntero() == 1;
}

void registroJ(PLAYERS players[], Pantalla *pantalla) {
        int i = contarRegistrados(players);
        bool terminar = false;

        printf("\n");
        printf("\t    --------Registro de jugadores--------- \n ");
        printf("Por favor complete los campos para registrar a los jugadores \n \n");
        printf("----------------------------------------------------------------- \n");

        if (i >= MAX_PLAYERS) {
                printf("No hay lugar para mas jugadores! \n");
        }
        while (i < MAX_PLAYERS && !terminar) {
                pedirUsuarioNuevo(players, players[i].Player);
                pedirClave("Ingrese contraseña del usuario: ", players[i].Password);
                players[i].idplayer = i + 100;
                i++;
                if (i >= 2 && i < MAX_PLAYERS) {
                        terminar = preguntarFin();
                }
        }
        *pantalla = Pantalla_menu;
}

/* ===================== LOGIN ===================== */

int pedirCredenciales(PLAYERS players[], int ubExcluido) {
        char usuario[MAX_CHAR];
        char clave[MAX_CHAR];
        int existe;
        int ub;
        bool correcto = false;
	printf("Ingrese -1 para salir del proceso de logueo! \n");
        do {
                printf("\nUsuario: ");
                leerLinea(usuario, MAX_CHAR);
		if ( !(usuario[0] == '-' && usuario[1] == '1' && strlen(usuario) == 2) ) {
			
	                printf("\nContraseña:");
	                leerLinea(clave, MAX_CHAR);

			validarUser(usuario, players, MAX_PLAYERS, &existe, &ub);

	                if (existe == 0) {
	                        printf("Error nombre de Usuario incorrecto \n");
	                } else if (strcmp(clave, players[ub].Password) != 0) {
	                        printf("Error: contraseña incorrecta \n");
	                } else if (ub == ubExcluido) {
	                        printf("Error \nYa esta logueado \n");
	                } else {
        	                correcto = true;
	                }
		} else {
			ub = -69;
		}
        } while (!correcto && ub != -69);

	return ub;
}

void login(PLAYERS players[], PARTIDA *partida, Pantalla *pantalla, bool *Bjuego) {
        if (contarRegistrados(players) < 2) {
                printf("\nSe necesitan al menos 2 jugadores registrados! \nPor favor, registrese primero. \n");
        } else { 
                printf("\n Ingresa los datos de los 2 usuario que van a jugar: \n");
                partida->ubP1 = pedirCredenciales(players, -1);
		if (partida->ubP1 != -69) {
	               	partida->ubP2 = pedirCredenciales(players, partida->ubP1);
		}if(partida->ubP1==-69 || partida->ubP2==-69){ 
			*Bjuego = false;
		}else{ *Bjuego=true; }
        }
        *pantalla = Pantalla_menu;
}

/* ===================== TABLERO ===================== */

void cargaMatriz(int inputMatriz[][COLUMNAS]) {
        for (int i = 0; i < FILAS; i++) {
                for (int j = 0; j < COLUMNAS; j++) {
                        inputMatriz[i][j] = 0;
                }
        }
}

void calcularTurno(int *turnoInput) {
        if (*turnoInput == 1) {
                *turnoInput = 2;
        } else {
                *turnoInput = 1;
        }
}

void ingresarFichas(int tablero[][COLUMNAS], int turno, int pos, int *estado) {
        int col = pos - 1;
        int fila = FILAS - 1;

        if (pos < 1 || pos > COLUMNAS) {
                *estado = 3;                    /* fuera de rango */
        } else if (tablero[0][col] != 0) {
                *estado = 2;                    /* columna llena */
        } else {
                while (tablero[fila][col] != 0) {
                        fila--;
                }
                tablero[fila][col] = turno;
                *estado = 1;                    /* ficha colocada */
        }
}

/*
        Nombre:         hayCuatroEnLinea
        Tipo:           Funcion
        Funcionamiento: Verifica si desde (fila, col), avanzando en la direccion (df, dc), hay 4 fichas seguidas del jugador "turno".
*/
bool hayCuatroEnLinea(int m[][COLUMNAS], int turno, int fila, int col, int df, int dc) {
        bool hay = true;
        for (int k = 0; k < 4 && hay; k++) {
                int f = fila + k * df;
                int c = col + k * dc;
                if (f < 0 || f >= FILAS || c < 0 || c >= COLUMNAS || m[f][c] != turno) {
                        hay = false;
                }
        }
        return hay;
}

/* Recorre todo el tablero en 4 direcciones: horizontal, vertical, diagonal \ y diagonal / */
bool hayVictoria(int m[][COLUMNAS], int turno) {
        int dirF[4] = {0, 1, 1, -1};
        int dirC[4] = {1, 0, 1, 1};
        bool gano = false;

        for (int i = 0; i < FILAS && !gano; i++) {
                for (int j = 0; j < COLUMNAS && !gano; j++) {
                        for (int d = 0; d < 4 && !gano; d++) {
                                gano = hayCuatroEnLinea(m, turno, i, j, dirF[d], dirC[d]);
                        }
                }
        }
        return gano;
}

bool tableroLleno(int m[][COLUMNAS]) {
        bool lleno = true;
        for (int j = 0; j < COLUMNAS && lleno; j++) {
                if (m[0][j] == 0) {
                        lleno = false;
                }
        }
        return lleno;
}

int victoria(int inputMatriz[][COLUMNAS], int turno) {
        int resultado = EN_CURSO;
        if (hayVictoria(inputMatriz, turno)) {
                resultado = GANA_ALGUIEN;
        } else if (tableroLleno(inputMatriz)) {
                resultado = EMPATE;
        }
        return resultado;
}

/* ===================== DIBUJO DE LA PANTALLA DE JUEGO ===================== */

void imprimirLadoIzquierdo(int fila, PLAYERS jugador, int movimientos) {
        float porc;
        if (fila == 0) {
                printf("%-2s %-15s", "J1:",jugador.Player);

        } else if (fila == 1) {
                printf("%-12s%-7d", "Movimientos:", movimientos);
        } else if (fila == 2) {
                printf("%-6s%-12d ", "Racha:", jugador.Streak);
        } else if (fila == 3) {
                porc = calcularPorcVictorias(jugador.Victory, jugador.GameCount);
                printf("%-10s%-9.0f", "Victoria:", porc);
        } else {
                printf("%-19s", " ");
        }
}

void imprimirLadoDerecho(int fila, PLAYERS jugador, int movimientos) {
        float porc;
        if (fila == 0) {
                 printf("%-2s %-15s\n", "J2:",jugador.Player);
        } else if (fila == 1) {
                printf("%-6s%d\n", " Movimientos:", movimientos);
        } else if (fila == 2) {
                printf("%-6s%d \n", " Racha:", jugador.Streak);
        } else if (fila == 3) {
                porc = calcularPorcVictorias(jugador.Victory, jugador.GameCount);
                printf("%-10s%.0f \n", " Victorias:", porc);
        } else {
                printf("\n");
        }
}

void imprimirFilaTablero(int tablero[][COLUMNAS], int fila) {
        printf("|");
        for (int j = 0; j < COLUMNAS; j++) {
                if (tablero[fila][j] == 0) {
                        printf(" ");
                } else if (tablero[fila][j] == 1) {
                        printf("X");
                } else {
                        printf("O");
                }
                printf("|");
        }
}

void imprimirNumerosColumnas(void) {
        printf("%19s", "");
        printf("--------------- \n");
        printf("%19s", "");
        printf("|");
        for (int k = 1; k <= COLUMNAS; k++) {
                printf("%d|", k);
        }
        printf("\n");
}

void mascaraPrime(int tablero[][COLUMNAS], PLAYERS players[], PARTIDA partida) {
        for (int i = 0; i < FILAS; i++) {
                imprimirLadoIzquierdo(i, players[partida.ubP1], partida.cantMov1);
                imprimirFilaTablero(tablero, i);
                imprimirLadoDerecho(i, players[partida.ubP2], partida.cantMov2);
        }
        imprimirNumerosColumnas();
}

/* ===================== PARTIDA ===================== */

void iniciarPartida(PARTIDA *partida, int tablero[][COLUMNAS]) {
        partida->cantMov1 = 0;
        partida->cantMov2 = 0;
        partida->cantMovInv1 = 0;
        partida->cantMovInv2 = 0;
        partida->movTotales = 0;
        partida->ganador = 0;
        partida->motivo = MOTIVO_NINGUNO;
        cargaMatriz(tablero);
}

int leerPosicion(void) {
        return leerEntero();
}

void registrarMovimiento(PARTIDA *partida, int turno) {
        if (turno == 1) {
                partida->cantMov1++;
        } else {
                partida->cantMov2++;
        }
        partida->movTotales++;
}

void registrarFalta(PARTIDA *partida, int turno) {
        if (turno == 1) {
                partida->cantMovInv1++;
        } else {
                partida->cantMovInv2++;
        }
}

void jugarPartida(int tablero[][COLUMNAS], PLAYERS players[], PARTIDA *partida) {
        int turno = 1;
        int posicion;
        int estadoFichas;
        int estado = EN_CURSO;
        int faltasSeguidas = 0;         /* faltas consecutivas del jugador que tiene el turno */

        do {
                printf("%10s", "");
                printf("------- TURNO DEL JUGADOR: %d ------- \n", turno);
                printf("%13s", "");
                printf("Ingrese posicion: ");
                posicion = leerPosicion();

                if (posicion == -1) {
                        /* abandona quien tenia el turno: gana el otro */
                        estado = GANA_ALGUIEN;
                        partida->motivo = MOTIVO_ABANDONO;
                        calcularTurno(&turno);
                        partida->ganador = turno;
                } else {
                        ingresarFichas(tablero, turno, posicion, &estadoFichas);
                        if (estadoFichas == 1) {
                                faltasSeguidas = 0;
                                registrarMovimiento(partida, turno);
                                estado = victoria(tablero, turno);
                                if (estado == GANA_ALGUIEN) {
                                        partida->ganador = turno;
                                        partida->motivo = MOTIVO_CUATRO_EN_LINEA;
                                } else if (estado == EMPATE) {
                                        partida->motivo = MOTIVO_EMPATE;
                                } else {
                                        calcularTurno(&turno);
                                }
                                mascaraPrime(tablero, players, *partida);
                        } else {
                                if (estadoFichas == 2) {
                                        printf("La columna esta llena! \n");
                                } else {
                                        printf("Ingrese una posicion valida! \n Entre 1 y %d \n", COLUMNAS);
                                }
                                faltasSeguidas++;
                                registrarFalta(partida, turno);
                                printf("Falta %d de %d \n", faltasSeguidas, MAX_FALTAS);
                                if (faltasSeguidas >= MAX_FALTAS) {
                                        /* descalificado quien tenia el turno: gana el otro */
                                        estado = GANA_ALGUIEN;
                                        partida->motivo = MOTIVO_FALTAS;
                                        calcularTurno(&turno);
                                        partida->ganador = turno;
                                }
                        }
                }
        } while (estado == EN_CURSO);
}

void mostrarResultado(PARTIDA partida) {
        if (partida.motivo == MOTIVO_EMPATE) {
                printf("Empate! El tablero esta lleno \n");
        } else {
                printf("Jugador %d ha ganado! \n", partida.ganador);
        }
}

void registrarResultado(PLAYERS players[], PARTIDA *partida) {
        int ub1 = partida->ubP1;
        int ub2 = partida->ubP2;

        partida->contador++;
        players[ub1].GameCount++;
        players[ub2].GameCount++;

        if (partida->ganador == 1) {
                players[ub1].Victory++;
                players[ub1].Streak++;
                players[ub2].Streak = 0;
        } else if (partida->ganador == 2) {
                players[ub2].Victory++;
                players[ub2].Streak++;
                players[ub1].Streak = 0;
        } else {
                players[ub1].Streak = 0;
                players[ub2].Streak = 0;
        }
}

const char *textoMotivo(MotivoFin motivo) {
        const char *texto;
        switch (motivo) {
                case MOTIVO_CUATRO_EN_LINEA: texto = "Cuatro en linea"; break;
                case MOTIVO_EMPATE:          texto = "Empate (tablero lleno)"; break;
                case MOTIVO_ABANDONO:        texto = "Abandono"; break;
                case MOTIVO_FALTAS:          texto = "Descalificacion por faltas consecutivas"; break;
                default:                     texto = "Sin finalizar"; break;
        }
        return texto;
}

void informeJugador(PLAYERS jugador, int numero, int movimientos, int faltas) {
        float porcVictorias = calcularPorcVictorias(jugador.Victory, jugador.GameCount);

        printf("Jugador %d: %s \n", numero, jugador.Player);
        printf("  Movimientos: %d \n", movimientos);
        printf("  Faltas: %d \n", faltas);
        printf("  Porc. de partidas ganadas: %.0f \n", porcVictorias);
        printf("  Racha actual: %d \n", jugador.Streak);
}

void informeFinal(PLAYERS players[], PARTIDA partida) {
        printf("\n-------- INFORME FINAL DE LA PARTIDA -------- \n");
        printf("Motivo de finalizacion: %s \n", textoMotivo(partida.motivo));
        printf("Duracion: %d turnos \n", partida.movTotales);
        informeJugador(players[partida.ubP1], 1, partida.cantMov1, partida.cantMovInv1);
        informeJugador(players[partida.ubP2], 2, partida.cantMov2, partida.cantMovInv2);
        printf("--------------------------------------------- \n");
}

void juego(PLAYERS players[], bool Bjuego, PARTIDA *partida, int tablero[][COLUMNAS], Pantalla *pantalla) {
        if (Bjuego) {
                iniciarPartida(partida, tablero);
                pantallaCarga();
                printf("\nPara salir del juego en cualquier momento, ingrese -1 \n");
                mascaraPrime(tablero, players, *partida);
                printf("\n");

                jugarPartida(tablero, players, partida);
                mostrarResultado(*partida);
                registrarResultado(players, partida);
                informeFinal(players, *partida);
        } else {
                pantallaCarga();
                printf("Jugadores insuficientes \n");
                printf("Se necesitan al menos dos jugadores distintos para jugar! \nPor favor, inicie sesion antes! \n");
        }
        *pantalla = Pantalla_menu;
}

/* ===================== ESTADISTICAS ===================== */

float calcularPorcVictorias(int cantVictorias, int partidasTotales) {
        float resultado = 0;
        if (partidasTotales != 0) {
                resultado = (cantVictorias * 100.0f) / partidasTotales;
        }
        return resultado;
}

void mostrarJugador(PLAYERS jugador, int numero) {
        float porcVictorias = calcularPorcVictorias(jugador.Victory, jugador.GameCount);

        printf("Jugador[%d] \n", numero);
        printf("ID: %d \n", jugador.idplayer);
        printf("Nombre: %s \n", jugador.Player);
        printf("Racha actual: %d \n", jugador.Streak);
        printf("Cant. de victorias: %d \n", jugador.Victory);
        printf("Cant. de partidas jugadas: %d \n", jugador.GameCount);
        printf("Porc.  de partidas ganadas: %.2f%s \n", porcVictorias, "%");
        printf("-------------------------------- \n");
}

void listarJugadores(PLAYERS players[]) {
        printf("-------------------------------- \n");
        for (int i = 0; i < MAX_PLAYERS; i++) {
                if (players[i].idplayer != 0) {
                        mostrarJugador(players[i], i + 1);
                }
        }
}

void estadisticas(PLAYERS players[], Pantalla *pantalla) {
	char aux[MAX_CHAR];
	if (contarRegistrados(players) > 0) {
                listarJugadores(players);
		printf("Presioner ENTER para continuar! \n");
		fgets(aux, MAX_CHAR, stdin);
		limpiarSiDesbordo(aux);
        } else {
                pantallaCarga();
                printf("\nNo hay jugadores registrados! \n");
        }
        *pantalla = Pantalla_menu;
}

/* ===================== DECORACION ===================== */

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
	printf("-> Juan Pablo Diaz Dell'Aringa \n-> Cristian Vladimir Campelo\n-> Valentino Emmanuel Andrada\n");
	printf(
        "  ___                      _ _ \n"
        " / __|_ _ _  _ _ __  ___  / / |\n"
        "| (_ | '_| || | '_ \\/ _ \\ | | |\n"
        " \\___|_|  \\_,_| .__/\\___/ |_|_|\n"
        "              |_|\n"
    );

}
void precargarJugadores(PLAYERS players[]) {
        players[0].idplayer = 100;
        strcpy(players[0].Player, USER_1);
        strcpy(players[0].Password, PASS_1);
        players[0].GameCount = PART_1;
        players[0].PMatches = PART_1;
        players[0].Victory = VICT_1;
        players[0].Streak = RACHA_1;

        players[1].idplayer = 101;
        strcpy(players[1].Player, USER_2);
        strcpy(players[1].Password, PASS_2);
        players[1].GameCount = PART_2;
        players[1].PMatches = PART_2;
        players[1].Victory = VICT_2;
        players[1].Streak = RACHA_2;

        players[2].idplayer = 102;
        strcpy(players[2].Player, USER_3);
        strcpy(players[2].Password, PASS_3);
        players[2].GameCount = PART_3;
        players[2].PMatches = PART_3;
        players[2].Victory = VICT_3;
        players[2].Streak = RACHA_3;
}
