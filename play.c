#include <stdio.h>


int main(void) {
//asdasdasd
	bool jugar = true;
	char input[3];
	int32_t jugador = 1;

	while (jugar) {

		input = tomarInput();

		if (posicionValida(input)) {

			if (victoria) {
				printf("Jugador %d gana la partida! \n", jugador);
				jugar = false;
				break;
			}
			


		}
		

	}

}

char* tomarInput() {

	bool valido = false;
	char input[3];
	
	while (!valido) {

		
		fgets(input, 3, stdin);	
	
		if (strlen(input) == 2) {

			if (isdigit(input[1] && isalpha(input[0]))) {
				valido = true;
			} 
		}

	}

	return input;
}
