#include <stdio.h>
#include <stdbool.h>

bool victoria(int m[][6], int orden) {
        
        // recorrido horizontal

        bool victoria   = false;
        int c1          = 0;
        int c2          = 0;
        int i           = 0;
        int j           = 0;
        int k           = 0; // <-- borrar para entrega

        for (i=0;i<orden && !victoria;i++) {

                c1      = 0;
                c2      = 0;

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

        return victoria;

}

void mostrarM(int m[][6], int filas, int columnas, bool pedantic) {

        int i           = 0;
        int j           = 0;

        if (filas > 6 || columnas > 6) {
                printf("Fuera de limites en funcion mostrarM \n Revisar indices \n");
                return;
        } 

        if (pedantic) {
                printf("┏========================================┓ \n");
        }

        for (i=0;i<filas;i++) {

                if (pedantic) {
                        printf("|");
                }

                for (j=0;j<columnas;j++) {

                        printf("%d", m[i][j]);

                        if (j < columnas - 1) {
                                printf("\t");
                        }

                }

                if (pedantic) {
                        printf("|");
                }

                printf("\n");
        }

        if (pedantic) {
                printf("┗========================================┛ \n");
        }


}

void remind(bool debug) {
        
        if (debug) {
                printf("[RECORDATORIO]: Borrar variable k y loop de debug en funcion victoria() \n");
                printf("[RECORDATORIO]: Borrar variable ENTREGA_G \n"); 
        }

}


