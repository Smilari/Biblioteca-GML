#include "Headers/Interfaz.h"

/**@brief Esta función imprime un encabezado en pantalla (en una posición fija) con un título y una etiqueta.
 *
 * @param título Cadena de caracteres que representa el título del encabezado.
 * @param etiqueta Cadena de caracteres que representa la etiqueta del encabezado.
 */
void header(string titulo, string etiqueta, int bgd, int txt) {
	gotoxy(posDerecha(strlen(etiqueta)), 0); // Se posiciona pegado al costado derecho de la pantalla.
	color(WHITE, BLACK);
	printf("%s", etiqueta);
	for (int i = 1; i < 4; i++) {
		gotoxy(0, i);
		lineaDeColor(bgd, txt);
	}
	gotoxy(posCentrado(strlen(titulo)), 2); // Posiciona el título centrado en la parte superior del encabezado.
	printf("%s", titulo);
	color(BLACK, WHITE);
	gotoxy(0, POS_Y_AFTER_HEADER); // Posiciona el cursor debajo del encabezado.
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
				menuModificar();
				break;
			case 4:
				listAllLibros();
				break;
			case 5:
				consultarLibro();
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

void menuModificar() {
	OpcionesMenu om[] = {"      MODIFICAR REGISTRO", "LIBRO", "AUTOR", "EDITORIAL", "GENERO",
						 "VOLVER AL MENU PRINCIPAL"};
	int opcionSeleccionada;
	int cantOpciones = SIZEOFARRAY(om);
	Coordenada xy = {POS_MENU_X, POS_MENU_Y};
	do {
		opcionSeleccionada = menu(om, xy, cantOpciones);
		clean();
		switch (opcionSeleccionada) {
			case 1:
				modificarLibro();
				break;
			case 2:
				modificarAutor();
				break;
			case 3:
				modificarEditorial();
				break;
			case 4:
				modificarGenero();
				break;
		}
	} while (opcionSeleccionada != (cantOpciones - 1));
}


/**@brief Esta función muestra un menú en pantalla y permite al usuario navegar entre las opciones.
 *
 * @param om Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del menú (la posición 0 representa el titulo).
 * @param xy Una estructura 'Coordenada' que indica la posición en la que se dibujará el menú.
 * @param cantOpciones El número de opciones en el menú.
 *
 * @return La opción seleccionada por el usuario (comienza en 1).
 */
int menu(OpcionesMenu om[], Coordenada xy, int cantOpciones) {
	int opcion = 1;
	int key;
	_setcursortype(_NOCURSOR); // Oculta el cursor.
	clean();
	printMenu(om, xy, opcion, cantOpciones);

	do {
		key = getKey(); // Obtiene la tecla presionada por el usuario.
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
		printMenu(om, xy, opcion, cantOpciones); // Muestra la opción seleccionada.
	} while (key != ENTER && key != ESC); // Continúa el bucle hasta que se presione ENTER o ESC.
	_setcursortype(_SOLIDCURSOR); // Restablece el cursor a su estado sólido.
	return opcion; // Retorna el índice de la opción seleccionada por el usuario.
}

/**@brief Esta función dibuja un menú en pantalla, resaltando la opción seleccionada por el usuario.
 *
 * @param om Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del menú.
 * @param xy Una estructura 'Coordenada' que indica la posición en la que se dibujará el menú.
 * @param selector El índice de la opción seleccionada que debe resaltarse (comienza en 1).
 * @param cantOpciones El número total de opciones en el menú.
 */
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
	color(BLACK, WHITE);
}

/**@brief Esta función imprime una opción del menú en pantalla, ajustándose y rellenando con ' ' según el ancho del menú indicado.
 *
 * @param opc Cadena de caracteres que representa la opción del menú a imprimir.
 */
void printOpcion(string opc) {
	printf("%s", opc);
	insertarCaracteres(ANCHO_MENU - strlen(opc), ' ');
}

/**@brief Muestra un submenú en pantalla y permite al usuario navegar entre las opciones.
 *
 * @param om Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del submenú.
 * @param xy Una estructura 'Coordenada' que indica la posición en la que se dibujará el submenú.
 * @param cantOpciones El número de opciones en el submenú.
 *
 * @return El índice de la opción seleccionada por el usuario (comienza en 0).
 */
int subMenu(OpcionesMenu om[], Coordenada xy, int cantOpciones) {
	int opcion = 0;
	int key;
	_setcursortype(_NOCURSOR); // Oculta el cursor.
	printSubMenu(om, xy, opcion, cantOpciones);

	do {
		key = getKey(); // Obtiene la tecla presionada por el usuario.
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
		printSubMenu(om, xy, opcion, cantOpciones); // Muestra la opción seleccionada.
	} while (key != ENTER && key != ESC); // Continúa el bucle hasta que se presione ENTER o ESC.
	_setcursortype(_SOLIDCURSOR); // Restablece el cursor a su estado sólido.
	return opcion; // Retorna el índice de la opción seleccionada por el usuario.
}

/**@brief Muestra un submenú en pantalla con opciones resaltadas y colores.
 *
 * @param om Un arreglo de estructuras 'OpcionesMenu' que representa las opciones del submenú.
 * @param xy Una estructura 'Coordenada' que indica la posición en la que se dibujará el submenú.
 * @param selector El índice de la opción seleccionada que debe resaltarse (comienza en 0).
 * @param cantOpciones El número total de opciones en el submenú.
 */
void printSubMenu(OpcionesMenu om[], Coordenada xy, int selector, int cantOpciones) {
	int ancho = 0;
	for(int i = 0; i < cantOpciones; i++){
		ancho += strlen(om[i].opcion) + 2;
	}
	xy.x = posCentrado(ancho);
	gotoxy(0, xy.y);
	lineaDeColor(BLUE, WHITE); // Dibuja una línea horizontal de color.

	for (int i = 0; i < cantOpciones; i++) {
		if (i == selector) {
			color(WHITE, BLUE); // Resalta la opción seleccionada.

		} else {
			color(BLUE, WHITE); // Establece colores para las opciones no seleccionadas.
		}
		gotoxy(xy.x, xy.y);
		printf("%s", om[i].opcion); // Imprime la opción en la posición actual.
		xy.x += strlen(om[i].opcion) + 2;
	}
	color(BLACK, WHITE); // Restablece los colores predeterminados.
}

/**@brief Esta función calcula la posición horizontal centrada para imprimir una cadena en pantalla.
 *
 * @param ancho Cantidad de caracteres que ocupa el ancho de pantalla, para calcular la posición.
 *
 * @return La posición horizontal centrada (x) para imprimir la cadena en pantalla.
 */
int posCentrado(int ancho) {
	return (ANCHO_PANTALLA - ancho) / 2;
}

/**@brief Esta función calcula la posición horizontal para imprimir una cadena a la derecha de la pantalla.
 *
 * @param ancho Cantidad de caracteres que ocupa el ancho de pantalla, para calcular la posición.
 *
 * @return La posición horizontal a la derecha (x) para imprimir la cadena en pantalla.
 */
int posDerecha(int ancho) {
	return (ANCHO_PANTALLA - ancho) - 3;
}

/**@brief Esta función captura y devuelve la tecla presionada por el usuario.
 *
 * @return El valor entero que representa la tecla presionada por el usuario.
 */
int getKey() {
	int key = getch();
	if (!key) {
		key = getch();
		return key;
	} else {
		return key;
	}
}

/**@brief Esta función limpia la pantalla y restaura los colores predeterminados. */
void clean(){
	color(BLACK, WHITE);
	CLEAN();
}

/**@brief Captura un número entero ingresado por el usuario desde el teclado.
 *
 * @param cantCaracteres Cantidad máxima de caracteres permitidos para la entrada.
 * @param flagTopeCaracteres Un indicador que, si es verdadero (true), permite que la entrada finalice al presionar
 * ENTER. Si es falso (false), la entrada se limita a `cantCaracteres` incluso después de presionar ENTER.
 *
 * @return El número entero capturado desde el teclado.
 */
size_t capturaCaracter(int cantCaracteres, boolean flagTopeCaracteres) {
	char key;
	long long valorNumerico = 0;
	int digito = 0;
	boolean flagDelete = false;
	Coordenada xy = getCoordenada(); // Obtiene la posición actual del cursor.

	do{
		key = getKey(); // Captura la tecla presionada por el usuario.
		if (key >= '0' && key <= '9'){
			digito = key - '0';
			valorNumerico = (valorNumerico * 10) + digito;
			cantCaracteres--;
			flagDelete = true;
		}
		if(key == BACKSPACE && flagDelete){
			valorNumerico = (valorNumerico - digito) / 10;
			gotoxy(xy.x, xy.y);
			insertarCaracteres(13, ' '); // Borra el último carácter impreso.
			cantCaracteres++;
			flagDelete = false;
		}
		gotoxy(xy.x, xy.y);
		printf("%lld", valorNumerico); // Muestra el valor numérico actual en pantalla.
		if(key == ENTER && !flagTopeCaracteres){
			cantCaracteres = 0;
		}
	} while(cantCaracteres != 0);
	return valorNumerico;
}

/**@brief Muestra un aviso en pantalla con colores de fondo y texto personalizados.
 *
 * @param texto Una cadena de caracteres que representa el mensaje de aviso a mostrar.
 * @param bgd El color de fondo del aviso.
 * @param txt El color del texto del aviso.
 */

void aviso(string texto, int bgd, int txt) {
	lineaDeColor(bgd, txt);
	gotoxy(posCentrado(strlen(texto)), getCoordenada().y); // Posiciona el cursor en el centro horizontal del aviso.
	printf("%s\n", texto);
	color(BLACK, WHITE);
}
/**@brief Esta función muestra un mensaje de aviso corto en la pantalla con un fondo y color de texto personalizados.
 * El mensaje se muestra centrado en la pantalla.
 *
 * @param texto El texto del mensaje de aviso.
 * @param bgd El color de fondo del mensaje.
 * @param txt El color del texto del mensaje.
 */
void avisoCorto(string texto, int bgd, int txt) {
	lineaColorEn(bgd, txt, strlen(texto) + 4, posCentrado(strlen(texto)) - 2);

	gotoxy(posCentrado(strlen(texto)), getCoordenada().y);
	printf("%s\n", texto);

	color(BLACK, WHITE);
}

/**@brief Muestra un submenú con las opciones "GUARDAR" y "CANCELAR", y permite al usuario seleccionar una de ellas.
 *	Cualquiera sea el caso, se imprime por pantalla el aviso con el mensaje correspondiente a la opción elegida.
 *
 * @return Un valor booleano que indica el estado de la acción. Verdadero (true) si se seleccionó "GUARDAR" y falso (false) si se seleccionó "CANCELAR".
 */
boolean guardarCambios() {
	OpcionesMenu sm[] = {"GUARDAR", "CANCELAR"};

	gotoxy(0, ALTO_PANTALLA-5);
	boolean estado = subMenu(sm, getCoordenada(), SIZEOFARRAY(sm)); // Muestra el submenú y obtiene la opción seleccionada.

	if(!estado){
		guardar(); // Si se eligió "GUARDAR", se muestra por pantalla.
	}else{
		cancelar(); // Si se eligió "CANCELAR", se muestra por pantalla.
	}
	estado = !estado; // Invierte el estado para reflejar si se seleccionó "GUARDAR".
	return estado; // Retorna el estado de la acción (true para "GUARDAR", false para "CANCELAR").
}

/** @brief Muestra un aviso de operación cancelada en pantalla con colores personalizados. */
void cancelar(){
	aviso("OPERACION CANCELADA", RED, WHITE);
}

/** @brief Muestra un aviso de operación exitosa en pantalla con colores personalizados. */
void guardar(){
	aviso("OPERACION EXITOSA", GREEN, WHITE);
}

/** @brief Inserta una cantidad específica de líneas en blanco en la salida estándar.
 *
 * @param cantLineas La cantidad de líneas en blanco que se van a insertar.
 */
void insertarLineas(int cantLineas){
	for(int i = 0; i < cantLineas; i++){
		printf("\n");
	}
}

/**@brief Esta función imprime una secuencia de caracteres repetidos en pantalla.
 *
 * @param cant Cantidad de veces que se imprimirá el caracter especificado.
 * @param caracter Caracter que se imprimirá repetidamente.
 */
void insertarCaracteres(int cant, char caracter) {
	for (int i = 0; i < cant; i++) {
		printf("%c", caracter);
	}
}

/**@brief Dibuja una línea horizontal de colores en la pantalla con un ancho y posición inicial.
 *
 * @param bgd El color de fondo de la línea.
 * @param txt El color del texto de la línea.
 * @param ancho El ancho de la línea (número de caracteres).
 * @param xInicial La posición inicial en el eje X donde comienza la línea.
 */
void lineaColorEn(int bgd, int txt, int ancho, int xInicial) {
	gotoxy(xInicial, getCoordenada().y);
	color(bgd, txt);
	insertarCaracteres(ancho, ' ');
	gotoxy(xInicial, getCoordenada().y);
}
/**@brief Dibuja una línea horizontal de colores a lo ancho de la pantalla.
 *
 * @param bgd El color de fondo de la línea.
 * @param txt El color del texto de la línea.
 */
void lineaDeColor(int bgd, int txt){
	lineaColorEn(bgd, txt, ANCHO_PANTALLA, 0);
}

/**@brief Limpia la pantalla desde una fila específica hacia abajo.
 *
 * @param y La fila a partir de la cual se limpiará la pantalla.
 */
void clearScreenFrom(int y){
	_setcursortype(_NOCURSOR); // Oculta el cursor.
	gotoxy(0, y); // Posiciona el cursor en la fila especificada.
	for (int i = y; i < ALTO_PANTALLA; i++){
		insertarCaracteres(ANCHO_PANTALLA, ' '); // Inserta caracteres en blanco para limpiar la fila.
	}
	gotoxy(0, y); // Vuelve a posicionar el cursor en la fila.
	_setcursortype(_SOLIDCURSOR); // Restablece el cursor a su estado sólido.
}

/** @brief Esta función muestra un menú interactivo que presenta datos almacenados en un archivo y permite al usuario
 * seleccionar una opción. Los datos se imprimen en la pantalla usando la función 'printFunction', y el usuario puede
 * navegar por las opciones con las teclas de flecha (arriba, abajo, izquierda, derecha). Se utiliza para interactuar
 * con datos almacenados en un archivo.
 *
 * @param data Un puntero a los datos que se mostrarán en el menú.
 * @param path La ruta del archivo que contiene los datos.
 * @param dataSize El tamaño en bytes de cada dato en el archivo.
 * @param y La posición vertical en la que se iniciará la visualización del menú en la pantalla.
 * @param printFunction La función que se utilizará para imprimir los datos en la pantalla.
 *
 * @return El índice de la opción seleccionada por el usuario (comienza en 1), pudiendo ser -1 si se presionó ESC.
 */
int dataMenu(const string path, size_t dataSize, int y, void (*printFunction)(const void *, int, int, int)) {
	int opcion = -1;
	int key;
	int cantDatos = getCantDatos(path, dataSize); // Obtiene la cantidad de datos en el archivo.
	void *datos = malloc(cantDatos * dataSize); // Reserva memoria para almacenar todos los datos.
	getDatos(datos, path, dataSize); // Obtiene los datos del archivo y los almacena en 'datos'.

	clearScreenFrom(y);
	_setcursortype(_NOCURSOR); // Oculta el cursor.
	printFunction(datos, y, opcion, cantDatos);

	do {
		key = getKey(); // Obtiene la tecla presionada por el usuario.
		switch (key) {
			case DOWN_ARROW:
			case RIGHT_ARROW:
				opcion++;
				if (opcion >= cantDatos) {
					opcion--;
				}
				break;
			case UP_ARROW:
			case LEFT_ARROW:
				opcion--;
				if (opcion < -1) {
					opcion++;
				}
				break;
			case ESC:
				opcion = -1;
				break;
		}
		printFunction(datos, y, opcion, cantDatos);
	} while (key != ENTER && key != ESC); // Continúa el bucle hasta que se presione ENTER o ESC.
	_setcursortype(_SOLIDCURSOR); // Restablece el cursor a su estado sólido.
	clearScreenFrom(y);
	return opcion + 1; // Retorna el índice de la opción seleccionada por el usuario.
}
