#include "Headers/Interfaz.h"

void header(string titulo, string etiqueta) {
/*  Descripción: Esta función imprime un encabezado en pantalla (en una posición fija) con un título y una etiqueta.
	Parámetros:
	- titulo: Cadena de caracteres que representa el título del encabezado.
	- etiqueta: Cadena de caracteres que representa la etiqueta del encabezado. */

	gotoxy(ANCHO_PANTALLA - strlen(etiqueta), 0); // Se posiciona pegado al costado derecho de la pantalla
	color(BLUE, WHITE);
	printf("%s", etiqueta);
	color(WHITE, BLACK);
	for (int i = 1; i < 4; i++) {
		gotoxy(0, i);
		insertCaracteres(ANCHO_PANTALLA, ' ');
	}
	gotoxy(posCentrado(titulo), 2);
	printf("%s", titulo);
	color(BLACK, WHITE);
	gotoxy(0, 5);
}

int posCentrado(string str) {
/*  Descripción: Esta función calcula la posición horizontal centrada para imprimir una cadena en pantalla.
	Parámetros:
	- str: Cadena de caracteres cuya longitud se utilizará para calcular la posición centrada.
	Retorno: La posición horizontal centrada para imprimir la cadena en pantalla. */

	return (ANCHO_PANTALLA - strlen(str)) / 2;
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
	OpcionesMenu om[] = {"            SOCIOS", "ALTA", "BAJA", "MODIFICACION", "LISTAR", "CONSULTAR",
						 "VOLVER AL MENU PRINCIPAL"};
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
	OpcionesMenu om[] = {"            LIBROS", "ALTA", "BAJA", "MODIFICACION", "LISTAR", "CONSULTAR",
						 "VOLVER AL MENU PRINCIPAL"};
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
	OpcionesMenu om[] = {"          PRESTAMOS", "LISTAR SOCIOS", "CONSULTA POR ID SOCIO", "LISTAR LIBROS",
						 "CONSULTA POR ID LIBRO", "VOLVER AL MENU PRINCIPAL"};
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
/*  Descripción: Esta función muestra un menú en pantalla y permite al usuario navegar entre las opciones.
	Parámetros:
	- om: Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del menú (la posición 0 representa el titulo).
	- xy: Una estructura 'Coordenada' que indica la posición en la que se dibujará el menú.
	- cantOpciones: El número de opciones en el menú.
	Retorno: La opción seleccionada por el usuario (comienza en 1). */

	int opcion = 1;
	int key;
	_setcursortype(_NOCURSOR);
	color(BLACK, WHITE);
	CLEAN();
	printMenu(om, xy, opcion, cantOpciones);

	do {
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
	} while (key != ENTER && key != ESC);
	return opcion;
}


void printMenu(OpcionesMenu om[], Coordenada xy, int selector, int cantOpciones) {
/*  Descripción: Esta función dibuja un menú en pantalla, resaltando la opción seleccionada por el usuario.
	Parámetros:
	- om: Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del menú.
	- xy: Una estructura 'Coordenada' que indica la posición en la que se dibujará el menú.
	- selector: El índice de la opción seleccionada que debe resaltarse (comienza en 1).
	- cantOpciones: El número total de opciones en el menú. */

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
/*  Descripción: Esta función imprime una opción del menú en pantalla, ajustandose y rellenando con ' ' según el ancho del menú indicado.
	Parámetros:
	- opc: Cadena de caracteres que representa la opción del menú a imprimir. */

	printf("%s", opc);
	insertCaracteres(ANCHO_MENU - strlen(opc), ' ');
}

void insertCaracteres(int cant, char caracter) {
/*  Descripción: Esta función imprime una secuencia de caracteres repetidos en pantalla.
	Parámetros:
	- cant: Cantidad de veces que se imprimirá el caracter especificado.
	- caracter: Caracter que se imprimirá repetidamente. */

	for (int i = 0; i < cant; i++) {
		printf("%c", caracter);
	}
}

int getKey() {
/*  Descripción: Esta función captura y devuelve la tecla presionada por el usuario.
	Retorno: El valor entero que representa la tecla presionada por el usuario. */

	int key = getch();
	if (!key) {
		key = getch();
		return key;
	} else {
		return key;
	}
}
