#include "Headers/Interfaz.h"

void header(string titulo, string etiqueta) {
	gotoxy(ANCHO_PANTALLA - strlen(etiqueta), 0);
	color(BLUE, WHITE);
	printf("%s", etiqueta);
	color(WHITE, BLACK);
	for(int i = 1; i < 4; i++){
		gotoxy(0, i);
		insertCaracteres(ANCHO_PANTALLA, ' ');
	}
	gotoxy(posCentrado(titulo), 2);
	printf("%s", titulo);
	color(BLACK, WHITE);
	gotoxy(0, 5);
}

int posCentrado(string str){
	return (ANCHO_PANTALLA - strlen(str))/2;
}

void menuPrincipal() {
	OpcionesMenu om[] = {"        MENU PRINCIPAL", "SOCIOS", "LIBROS", "PRESTAMOS", "FINALIZAR PROGRAMA"};
	int opcionSeleccionada;
	int cantOpciones = SIZEOFARRAY(om);
	Coordenada xy = {POS_MENU_X, POS_MENU_Y};
	do {
		opcionSeleccionada = menu(om, xy, cantOpciones);
		switch (opcionSeleccionada) {
			case 1:
				menuSocios();
				break;
			case 2:
				menuLibros();
				break;
			case 3:
				menuPrestamos();
				break;
		}
	} while (opcionSeleccionada != (cantOpciones - 1));
}

void menuSocios() {
	OpcionesMenu om[] = {"            SOCIOS", "ALTA", "BAJA", "MODIFICACION", "LISTAR", "CONSULTAR", "VOLVER AL MENU PRINCIPAL"};
	int opcionSeleccionada;
	int cantOpciones = SIZEOFARRAY(om);
	Coordenada xy = {POS_MENU_X, POS_MENU_Y};
	do {
		opcionSeleccionada = menu(om, xy, cantOpciones);
		switch (opcionSeleccionada) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
		}
	} while (opcionSeleccionada != (cantOpciones - 1));
}

void menuLibros() {
	OpcionesMenu om[] = {"            LIBROS", "ALTA", "BAJA", "MODIFICACION", "LISTAR", "CONSULTAR", "VOLVER AL MENU PRINCIPAL"};
	int opcionSeleccionada;
	int cantOpciones = SIZEOFARRAY(om);
	Coordenada xy = {POS_MENU_X, POS_MENU_Y};
	do {
		opcionSeleccionada = menu(om, xy, cantOpciones);
		switch (opcionSeleccionada) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
		}
	} while (opcionSeleccionada != (cantOpciones - 1));
}

void menuPrestamos() {
	OpcionesMenu om[] = {"          PRESTAMOS", "LISTAR SOCIOS", "CONSULTA POR ID SOCIO", "LISTAR LIBROS", "CONSULTA POR ID LIBRO", "VOLVER AL MENU PRINCIPAL"};
	int opcionSeleccionada;
	int cantOpciones = SIZEOFARRAY(om);
	Coordenada xy = {POS_MENU_X, POS_MENU_Y};
	do {
		opcionSeleccionada = menu(om, xy, cantOpciones);
		switch (opcionSeleccionada) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
		}
	} while (opcionSeleccionada != (cantOpciones - 1));
}

int menu(OpcionesMenu om[], Coordenada xy, int cantOpciones) {
	int opcion = 1;
	_setcursortype(_NOCURSOR);
	color(BLACK, WHITE);
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

void printOpcion(string opc) {
	printf("%s", opc);
	insertCaracteres(ANCHO_MENU - strlen(opc), ' ');
}

void insertCaracteres(int cant, char caracter) {
	for (int i = 0; i < cant; i++) {
		printf("%c", caracter);
	}
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
