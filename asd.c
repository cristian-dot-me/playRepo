#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
typedef struct {          
                          
    int idplayer;         
    char Player[11];      
    char Password[11];    
    int Streak;           
    int Victory;          
    int PMatches;         
    int GameCount;        
                          
}PLAYERS;                 

bool validarUserCambiado(char *inputstr, PLAYERS players[], int cantPlayers, int *ub) {                                                                           
        int i;                                                                      
	bool validar;
        for (i = 0; i<cantPlayers; i++) {                                            
                if (strcmp(inputstr, players[i].Player)==0) {                                                

                        validar = 1;
                        *ub = i;                                                      
                        i=cantPlayers;                                              

                } else {                                                                                                            	validar = 0;                                                
                }                                                                   
        }                                                                           
	return validar;
}                                                                                   

void validarUserOriginal(char *inputstr, PLAYERS players[], int cantPlayers, int *validar, int *ub) {
        int i;
	int uno = 1;
        for (i = 0; i<cantPlayers; i++) {                                                    
//              validar = 0;                                                                 
                if (strcmp(inputstr, players[i].Player)==0) {                                                                                                               
                        *validar = uno;
                        *ub=i;                                                               
                        i=cantPlayers;                                                       
                                                                                             
                } else {                                                                     
                                                                                             
                        validar = 0;                                                         
                                                                                             
                }                                                                            
        }                                                                                    
}                                                                                            


int main(void) {

	PLAYERS structPrueba[3];
	char entrada1[10];
	char entrada2[10];
	strcpy(entrada1, "pepe");
	strcpy(entrada2, "hola");

	strcpy(structPrueba[0].Player, entrada1);
	strcpy(structPrueba[1].Player, entrada2);
	int cantPlayers = 2;
	int ubicacion = 1;
	int validar;
	int validar2;

	validarUserOriginal(entrada1, structPrueba, cantPlayers, &validar, &ubicacion);

	printf("Validar: %d \n", validar);

	validarUserOriginal(entrada2, structPrueba, cantPlayers, &validar2, &ubicacion);

	printf("Validar: %d \n", validar2);

	return 0;
}
