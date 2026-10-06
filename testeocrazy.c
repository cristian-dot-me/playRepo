#include <stdio.h>
#define COLUMNAS 7
#define FILAS 6


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
	int cantMov1;
	int cantMov2;
	int cantMovInv1;
	int cantMovInv2;
	int movTotales;

} PARTIDA;

float calcularPorcVictorias(int cantVictorias, int partidasTotales) {
    float resultado;
    resultado = (cantVictorias*100) / partidasTotales;
    return resultado;
}
void mascaraPrime(int tablero[][COLUMNAS], PLAYERS players[], int ub1, int ub2, int cantMov1, int cantMov2);
int main(void) {
    
    int tablero[FILAS][COLUMNAS];
    PARTIDA partida;
    partida.contador = 1;
    PLAYERS players[2];
    players[0].GameCount = 2;
    players[0].Victory = 1;
    players[0].Streak = 1;
    players[1].GameCount = 3;
    players[1].Victory = 2;
    players[1].Streak = 0;
    
    int cantMov1 = 30;
    int cantMov2 = 13;
    float porcVictorias;
    int ub1 = 0;
    int ub2 = 1;
    tablero[0][0]=0;
    mascaraPrime(tablero, players, ub1, ub2, cantMov1, cantMov2);
    
    return 0;
}

void mascaraPrime(int tablero[][COLUMNAS], PLAYERS players[], int ub1, int ub2, int cantMov1, int cantMov2) {

    float porcVictorias;
for(int i = 0; i<FILAS; i++) {
        if (i == 0) {
            printf("%-19s", "    J1    ");
        } else if (i==1) {
            printf("%-12s%-7d", "Movimientos:", cantMov1);
        } else if (i==2) {
            printf("%-6s%-12d ", "Racha:", players[ub1].Streak);
        } else if(i==3) {
            porcVictorias = calcularPorcVictorias(players[ub1].Victory, players[ub1].GameCount);
            printf("%-10s%-9.0f", "Victorias:", porcVictorias);

        } else {
            printf("%-19s", " ");
          
        }
          printf("| ");
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
            printf("%-6s%d \n", "  Racha:", players[ub2].Streak);
        } else if(i==3) {
            porcVictorias = calcularPorcVictorias(players[ub2].Victory, players[ub2].GameCount);
            printf("%-10s%.0f \n", "  Victorias:", porcVictorias);

        } else {
            printf("\n");
            
        }
        
    }

}