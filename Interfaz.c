#include "Headers/Interfaz.h"

int selectOpcion(int cantOpciones);

void printSubMenu(OpcionesMenu *om, Coordenada xy, int selector, int cantOpciones);

/** @def Esta función imprime un encabezado en pantalla (en una posición fija) con un título y una etiqueta.
	@param título Cadena de caracteres que representa el título del encabezado.
	@param etiqueta Cadena de caracteres que representa la etiqueta del encabezado. */

void header(string titulo, string etiqueta) {
	gotoxy(ANCHO_PANTALLA - strlen(etiqueta), 0); // Se posiciona pegado al costado derecho de la pantalla.
	color(BLUE, WHITE);
	printf("%s", etiqueta);
	color(WHITE, BLACK);
	for (int i = 1; i < 4; i++) {
		gotoxy(0, i);
		insertCaracteres(ANCHO_PANTALLA, ' '); // Imprime caracteres vacíos para cambiar en esa zona al color seleccionado.
	}
	gotoxy(posCentrado(strlen(titulo)), 2); // Posiciona el título centrado en la parte superior del encabezado.
	printf("%s", titulo);
	color(BLACK, WHITE);
	gotoxy(0, 5); // Posiciona el cursor debajo del encabezado.
}

/** @def Esta función calcula la posición horizontal centrada para imprimir una cadena en pantalla.
	@param ancho Cantidad de caracteres que ocupa el ancho de pantalla, para calcular la posición centrada.
	@return La posición horizontal centrada (x) para imprimir la cadena en pantalla. */

int posCentrado(int ancho) {
	return (ANCHO_PANTALLA - ancho) / 2;
}

void menuPrincipal() {
	OpcionesMenu om[] = {"        MENU PRINCIPAL", "SOCIOS", "LIBROS", "PRESTAMOS", "FINALIZAR PROGRAMA"};
	int opcionSeleccionada;
	int cantOpciones = SIZEOFARRAY(om);
	Coordenada xy = {POS_MENU_X, POS_MENU_Y};
	do {
		opcionSeleccionada = menu(om, xy, cantOpciones);
		clean();
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
		clean();
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
		clean();
		switch (opcionSeleccionada) {
			case 1:
				altaLibro();
				break;
			case 2:
				bajaLibro();
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
		clean();
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

/** @def Esta función muestra un menú en pantalla y permite al usuario navegar entre las opciones.
	@param om Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del menú (la posición 0 representa el titulo).
	@param xy Una estructura 'Coordenada' que indica la posición en la que se dibujará el menú.
	@param cantOpciones El número de opciones en el menú.
	@return La opción seleccionada por el usuario (comienza en 1). */

int menu(OpcionesMenu om[], Coordenada xy, int cantOpciones) {
	int opcion = 1;
	int key;
	_setcursortype(_NOCURSOR); // Oculta el cursor.
	clean();
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
				break;
			case UP_ARROW:
			case LEFT_ARROW:
				opcion--;
				if (opcion < 1) {
					opcion = cantOpciones - 1;
				}
				break;
			case ESC:
				opcion = cantOpciones - 1;
		}
		printMenu(om, xy, opcion, cantOpciones);
	} while (key != ENTER && key != ESC);
	return opcion;
}

/** @def Esta función dibuja un menú en pantalla, resaltando la opción seleccionada por el usuario.
	@param om Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del menú.
	@param xy Una estructura 'Coordenada' que indica la posición en la que se dibujará el menú.
	@param selector El índice de la opción seleccionada que debe resaltarse (comienza en 1).
	@param cantOpciones El número total de opciones en el menú. */

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

/** Esta función imprime una opción del menú en pantalla, ajustándose y rellenando con ' ' según el ancho del menú indicado.
	@param opc Cadena de caracteres que representa la opción del menú a imprimir. */

void printOpcion(string opc) {
	printf("%s", opc);
	insertCaracteres(ANCHO_MENU - strlen(opc), ' ');
}

int subMenu(OpcionesMenu om[], Coordenada xy, int cantOpciones) {
	int opcion = 0;
	int key;
	int ancho = 0;
	_setcursortype(_NOCURSOR); // Oculta el cursor.
	for(int i = 0; i < cantOpciones; i++){
		ancho += strlen(om[i].opcion) + 2;
	}
	xy.x = posCentrado(ancho);
	printSubMenu(om, xy, opcion, cantOpciones);

	do {
		key = getKey();
		switch (key) {
			case DOWN_ARROW:
			case RIGHT_ARROW:
				opcion++;
				if (opcion >= cantOpciones) {
					opcion = 0;
				}
				break;
			case UP_ARROW:
			case LEFT_ARROW:
				opcion--;
				if (opcion < 0) {
					opcion = cantOpciones - 1;
				}
				break;
			case ESC:
				opcion = cantOpciones - 1;
		}
		printSubMenu(om, xy, opcion, cantOpciones);
	} while (key != ENTER && key != ESC);
	return opcion;
}

void printSubMenu(OpcionesMenu om[], Coordenada xy, int selector, int cantOpciones) {
	gotoxy(0, xy.y);
	color(BLUE, YELLOW);
	insertCaracteres(ANCHO_PANTALLA, ' ');
	for (int i = 0; i < cantOpciones; i++) {
		if (i == selector) {
			color(WHITE, BLUE);

		} else {
			color(BLUE, WHITE);
		}
		gotoxy(xy.x, xy.y);
		printf("%s", om[i].opcion);
		xy.x += strlen(om[i].opcion) + 2;
	}
}

/** @def Esta función imprime una secuencia de caracteres repetidos en pantalla.
	@param cant Cantidad de veces que se imprimirá el caracter especificado.
	@param caracter Caracter que se imprimirá repetidamente. */

void insertCaracteres(int cant, char caracter) {
	for (int i = 0; i < cant; i++) {
		printf("%c", caracter);
	}
}

/**	@def Esta función captura y devuelve la tecla presionada por el usuario.
	@return El valor entero que representa la tecla presionada por el usuario. */

int getKey() {
	int key = getch();
	if (!key) {
		key = getch();
		return key;
	} else {
		return key;
	}
}

/** @def Esta función limpia la pantalla y restaura los colores predeterminados. */

void clean(){
	color(BLACK, WHITE);
	CLEAN();
}

/** @def Captura un número entero ingresado por el usuario desde el teclado.
	@param cantCaracteres Cantidad máxima de caracteres permitidos para la entrada.
	@param flagTopeCaracteres Un indicador que, si es verdadero (distinto de cero), permite que la entrada
	      finalice al presionar ENTER. Si es falso (igual a cero), la entrada se limita a `cantCaracteres` incluso
	      después de presionar ENTER.
	@return El número entero capturado desde el teclado. */

long long int capturaCaracter(int cantCaracteres, boolean flagTopeCaracteres) {
	char key;
	long long valorNumerico = 0;
	int digito = 0;
	boolean flagDelete = false;
	Coordenada xy = getCoordenada();

	do{
		key = getKey();
		if (key >= '0' && key <= '9'){
			digito = key - '0';
			valorNumerico = (valorNumerico * 10) + digito;
			cantCaracteres--;
			flagDelete = true;
		}
		if(key == BACKSPACE && flagDelete){
			valorNumerico = (valorNumerico - digito) / 10;
			gotoxy(xy.x, xy.y);
			insertCaracteres(13, ' ');
			cantCaracteres++;
			flagDelete = false;
		}
		gotoxy(xy.x, xy.y);
		printf("%lld", valorNumerico);
		if(key == ENTER && !flagTopeCaracteres){
			cantCaracteres = 0;
		}
	} while(cantCaracteres != 0);
	return valorNumerico;
}