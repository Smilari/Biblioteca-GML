#include "Headers/Menus.h"

/**/
void menuPrincipal() {
	OpcionesMenu om[] = {"        MENU PRINCIPAL", "SOCIO", "LIBRO", "PRESTAMO", "FINALIZAR PROGRAMA"};
	int opcionSeleccionada;
	int cantOpciones = SIZEOFARRAY(om);
	Coordenada xy = {POS_MENU_X, POS_MENU_Y};
	do {
		opcionSeleccionada = menu(om, xy, cantOpciones);
		switch (opcionSeleccionada) {
		}
	} while (opcionSeleccionada != (cantOpciones-1));
}

void printOpcion(string opc) {
	printf("%s", opc);
	insertCaracteres(ANCHO_MENU - strlen(opc), ' ');
}

void printMenu(OpcionesMenu om[], Coordenada xy, int selector, int cantOpciones) {
	color(WHITE, BLACK);
	gotoxy(xy.x, xy.y);
	printOpcion(om[0].opcion);
	for (int i = 1; i < cantOpciones; i++) {
		if (i == selector) {
			color(CYAN, WHITE);
		} else {
			color(YELLOW, BLACK);
		}
		gotoxy(xy.x, xy.y + i);
		printOpcion(om[i].opcion);
	}
}

void insertCaracteres(int cant, char caracter) {
	for (int i = 0; i < cant; i++) {
		printf("%c", caracter);
	}
}

int menu(OpcionesMenu om[], Coordenada xy, int cantOpciones) {
	int opcion = 1;
	_setcursortype(_NOCURSOR);
	CLEAN();
	printMenu(om, xy, opcion, cantOpciones);

	int key = getKey();
	while (key != ENTER && key != ESC) {
		key = getKey();
		switch (key) {
			case DOWN_ARROW:
			case RIGHT_ARROW:
				opcion++;
				if (opcion >= cantOpciones) {
					opcion = 1;
				}
				printMenu(om, xy, opcion, cantOpciones);
				break;
			case UP_ARROW:
			case LEFT_ARROW:
				opcion--;
				if (opcion <= 0) {
					opcion = cantOpciones - 1;
				}
				printMenu(om, xy, opcion, cantOpciones);
				break;
			case ESC:
				opcion = cantOpciones - 1;
		}
	}
	return opcion;
}

int getKey() {
	int key = getch();
	if (!key) {
		key = getch();
		return key;
	} else {
		return key;
	}
}
