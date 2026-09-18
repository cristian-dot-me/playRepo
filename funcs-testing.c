#include <stdio.h>
#include <stdbool.h>

// recorrido horizontal para verificar victoria 	[ X ]
// recorrido vertical para verificar victoria		[ X ]
// recorrido en diagonal para verificar victoria	[...]

void mostrarM(int m[][6], int filas, int columnas, bool pedantic);
bool victoria(int m[][6], int orden);
void remind(bool debug); 

bool debug = true;

int main(void) {

	bool estado 	= false;
	int m 		= 6;
	int n 		= 6;
	int pepe[6][6] = {

		{0,0,0,0,0,0},
		{1,2,1,2,1,0},
		{1,2,2,0,0,0},
		{1,0,0,0,0,0},
		{1,0,0,0,0,0},
		{0,0,0,1,1,1}

	}; 


	mostrarM(pepe, m, n, true);

	if (victoria(pepe, m)) {
		printf("Se cumple una condicion de victoria \n");
	} else {
		printf("No se cumple ninguna condicion de victoria \n");
	}

	remind(debug);

	return 0;

}

void remind(bool debug) {
	
	if (debug) {
		printf("[RECORDATORIO]: Borrar variable k y loop de debug en funcion victoria() \n");
		printf("[RECORDATORIO]: Borrar variable ENTREGA_G \n");	
	}

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
//	control = orden;
//	inicio 	= 2;
//	final 	= 3;
	bool flag = true;
/*
	while(flag) {

		for (i=inicio;i<control;i++) {

			for (j=0;j<orden;j++) {

						

			}

		}
	}
*/
	return victoria;

}

void mostrarM(int m[][6], int filas, int columnas, bool pedantic) {

	int i 		= 0;
	int j 		= 0;

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

