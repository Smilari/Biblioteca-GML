#include "Headers/Prestamos.h"

/**@brief Esta función guía al usuario a través del proceso de alta para un préstamo.
 * Permite seleccionar un libro y un socio, y genera el préstamo correspondiente
 * si ambos existen y si hay stock disponible del libro.
*/
void altaPrestamo() {
	header("ALTA DE REGISTRO", "PRESTAMO", LGREEN, WHITE);

	size_t opcionLibro = allDataMenu(PATH_LIBRO, sizeof(Libro), POS_Y_AFTER_HEADER, printLibros);

	if (!opcionLibro) {
		printf("ISBN: ");
		opcionLibro = capturaCaracter(13, true);
	}

	Libro *libroPtr = getDato(&opcionLibro, PATH_LIBRO, sizeof(Libro), compareLibroID);

	if (existeDato(libroPtr)) {
		if (libroPtr->stock != 0) {
			size_t opcionSocio = allDataMenu(PATH_SOCIO, sizeof(Socio), POS_Y_AFTER_HEADER, printSocios);

			if (!opcionSocio) {
				printf("DNI: ");
				opcionSocio = capturaCaracter(8, true);
			}

			Socio *socioPtr = getDato(&opcionSocio, PATH_SOCIO, sizeof(Socio), compareSocioID);

			if (existeDato(socioPtr)) {
				generarPrestamo(libroPtr, socioPtr);
			} else {
				aviso("NO EXISTE ESE SOCIO", RED, WHITE);
				cancelar();
			}
		} else {
			aviso("LIBRO FUERA DE STOCK", RED, WHITE);
			cancelar();
		}
	} else {
		aviso("NO EXISTE ESE LIBRO", RED, WHITE);
		cancelar();
	}

	tecla();
}

/**@brief Esta función permite al usuario revocar un préstamo asociado a su DNI.
 * Muestra los préstamos activos del socio y permite seleccionar uno para revocar.
 * Actualiza el stock del libro y establece la fecha de entrega del préstamo.
*/
void revocarPrestamo() {
	header("REVOCAR REGISTRO", "PRESTAMO", LGREEN, WHITE);
	printf("Ingrese su DNI: ");
	size_t DNI = capturaCaracter(8, false);

	Socio *socioPtr = getDato(&DNI, PATH_SOCIO, sizeof(Socio), compareSocioDNI);

	if (existeDato(socioPtr)) {
		int cantPrestamos = getCantDatos(PATH_PRESTAMO, sizeof(Prestamo));
		int cantPrestamosEncontrados = 0;
		Prestamo *prestamos = (Prestamo *)malloc(cantPrestamos * sizeof(Prestamo));

		for (size_t i = 1; i <= cantPrestamos; i++) {
			Prestamo *prestamoPtr = getDato(&i, PATH_PRESTAMO, sizeof(Prestamo), comparePrestamoID);

			if (prestamoPtr->fechaEntregado == FECHA_NO_ESTABLECIDA) {
				socioPtr = getDato(&prestamoPtr->ID_socio, PATH_SOCIO, sizeof(Socio), compareSocioID);

				if (socioPtr->DNI == DNI) {
					prestamos[cantPrestamosEncontrados] = *prestamoPtr;
					cantPrestamosEncontrados++;
				}
			}
		}

		if (cantPrestamosEncontrados != 0) {
			int opcion = dataMenu(prestamos, cantPrestamosEncontrados, POS_Y_AFTER_HEADER, printPrestamos);

			if (opcion != 0) {
				Prestamo prestamo = prestamos[opcion - 1];
				Libro *libroPtr = getDato(&prestamos->ID_libro, PATH_LIBRO, sizeof(Libro), compareLibroID);
				libroPtr->stock++;
				prestamo.fechaEntregado = time(NULL);

				lineaDeColor(YELLOW, BLACK);
				printf("Id  DNI \tLibro\t\t\tISBN\t\tFecha adquirido \t    Fecha Entrega\n\n");
				color(BLACK, WHITE);
				mostrarPrestamo(prestamo);

				if (guardarCambios()) {
					FILE *fPrestamo = fopen(PATH_PRESTAMO, "r+b");
					fseek(fPrestamo, getPosDato(&prestamo.ID_prestamo, PATH_PRESTAMO, sizeof(Prestamo), comparePrestamoID), SEEK_SET);
					fwrite(&prestamo, sizeof(Prestamo), 1, fPrestamo);
					fclose(fPrestamo);

					FILE *fLibro = fopen(PATH_LIBRO, "r+b");
					fseek(fLibro, getPosDato(&libroPtr->ID_libro, PATH_LIBRO, sizeof(Libro), compareLibroID), SEEK_SET);
					fwrite(libroPtr, sizeof(Libro), 1, fLibro);
					fclose(fLibro);
				}
			} else {
				aviso("NO ES POSIBLE LA ENTRADA MANUAL", RED, WHITE);
				cancelar();
			}
		} else {
			aviso("NO HAY PRESTAMOS ASOCIADOS A ESE SOCIO", RED, WHITE);
			cancelar();
		}
		free(prestamos);
	} else {
		aviso("NO EXISTE ESE SOCIO", RED, WHITE);
		cancelar();
	}

	tecla();
}

/** @brief Genera un nuevo préstamo y actualiza los archivos correspondientes.
    Esta función realiza las siguientes acciones:
    1. Decrementa el stock del libro en una unidad.
    2. Asigna un ID de préstamo único y consecutivo al último registrado.
    3. Registra el préstamo con la información proporcionada.
    4. Muestra la información del préstamo en la lista de préstamos.
    5. Actualiza los cambios en los archivos de libros y préstamos.
    @param libroPtr Puntero al libro asociado al préstamo.
    @param socioPtr Puntero al socio asociado al préstamo.
*/
void generarPrestamo(Libro *libroPtr, Socio *socioPtr) {
	FILE *fLibro = fopen(PATH_LIBRO, "r+b");
	FILE *fPrestamo = fopen(PATH_PRESTAMO, "r+b");
	Prestamo prestamo;

	fseek(fPrestamo, 0L, SEEK_END);
	fseek(fLibro, getPosDato(&libroPtr->ID_libro, PATH_LIBRO, sizeof(Libro), compareLibroID), SEEK_SET);

	// 1. Elimina del stock de libros una unidad.
	libroPtr->stock--;

	// 2. Asigna un ID de préstamo único y consecutivo al último registrado.
	prestamo.ID_prestamo = getCantDatos(PATH_PRESTAMO, sizeof(Prestamo)) + 1;

	// 3. Registra el préstamo con la información proporcionada.
	prestamo.ID_libro = libroPtr->ID_libro;
	prestamo.ID_socio = socioPtr->ID_socio;
	prestamo.fechaAdquirido = time(NULL);
	prestamo.fechaEntregado = FECHA_NO_ESTABLECIDA;

	// 4. Muestra la información del préstamo en la lista de préstamos.
	listPrestamos(&prestamo, 1);

	// 5. Actualiza los cambios en los archivos de libros y préstamos.
	if (guardarCambios()) {
		fwrite(libroPtr, sizeof(Libro), 1, fLibro);
		fwrite(&prestamo, sizeof(Prestamo), 1, fPrestamo);
	}

	fclose(fLibro);
	fclose(fPrestamo);
}

/**@brief Esta función obtiene todos los préstamos almacenados en el archivo correspondiente y los muestra en la pantalla.
*/
void listAllPrestamos() {
	header("LISTAR REGISTROS", "PRESTAMOS", LBLUE, WHITE);
	int cantPrestamos = getCantDatos(PATH_PRESTAMO, sizeof(Prestamo));
	Prestamo prestamos[cantPrestamos];

	getDatos(prestamos, PATH_PRESTAMO, sizeof(Prestamo));
	listPrestamos(prestamos, cantPrestamos);
	tecla();
}

/**@brief Esta función muestra en la pantalla la información de los préstamos dados en un array.
 *
 * @param prestamos El array de préstamos a mostrar.
 * @param cantPrestamos La cantidad de préstamos en el array.
*/
void listPrestamos(Prestamo prestamos[], int cantPrestamos) {
	insertarLineas(1);
	lineaDeColor(YELLOW, BLACK);
	printf("Id  DNI \tLibro\t\t\tISBN\t\tFecha adquirido \t    Fecha Entrega\n\n");
	color(BLACK, WHITE);
	for (int i = 0; i < cantPrestamos; i++) {
		mostrarPrestamo(prestamos[i]);
	}
	insertarLineas(3);
}

/**@brief Esta función imprime en la pantalla la información detallada de un préstamo, incluyendo las fechas
 * de adquisición y entrega (si está disponible).
 *
 * @param prestamo El préstamo cuya información se va a mostrar.
*/
void mostrarPrestamo(Prestamo prestamo) {
	// Obtiene la información del libro asociado al préstamo.
	size_t idLibro = prestamo.ID_libro;
	Libro libro = *(Libro*)getDato(&idLibro, PATH_LIBRO, sizeof(Libro), compareLibroID);

	// Obtiene la información del socio asociado al préstamo.
	size_t idSocio = prestamo.ID_socio;
	Socio socio = *(Socio*)getDato(&idSocio, PATH_SOCIO, sizeof(Socio), compareSocioID);

	// Obtiene y formatea la fecha de adquisición.
	char fechaAdquirido[30];
	strftime(fechaAdquirido, sizeof(fechaAdquirido), "%Y-%m-%d %H:%M:%S", localtime(&prestamo.fechaAdquirido));

	// Imprime la información principal del préstamo.
	printf("%-4lld%-12lld%-24s%-16lld%-28s", prestamo.ID_prestamo, socio.DNI, libro.titulo, libro.ISBN, fechaAdquirido);

	// Verifica si el préstamo fue entregado y muestra la fecha de entrega si está disponible.
	if (prestamo.fechaEntregado != FECHA_NO_ESTABLECIDA) {
		char fechaEntregado[30];
		strftime(fechaEntregado, sizeof(fechaEntregado), "%Y-%m-%d %H:%M:%S", localtime(&prestamo.fechaEntregado));
		printf("%-26s\n", fechaEntregado);
	} else {
		printf("----\n");
	}
}

/**@brief Esta función imprime en la pantalla una lista de préstamos, permitiendo al usuario seleccionar uno.
 *
 * @param data Puntero a los datos de los préstamos.
 * @param y Posición vertical en la que comenzar la impresión.
 * @param opcion Índice de la opción seleccionada.
 * @param cantDatos Cantidad total de préstamos.
*/
void printPrestamos(const void *data, int y, int opcion, int cantDatos){
	const Prestamo *prestamos =  (const Prestamo *)data;
	int x = posCentrado(ANCHO_PANTALLA);
	gotoxy(x, y);
	avisoCorto("Seleccione un prestamo", BLUE, WHITE);
	gotoxy(x, y = y + 2);
	lineaDeColor(WHITE, BLACK);
	printf("Id  DNI \tLibro\t\t\tISBN\t\tFecha adquirido \t    Fecha Entrega\n\n");
	y++;
	for (int i = opcion; i < (opcion + OPCIONES_A_MOSTRAR); ++i){
		if(i == opcion) {
			color(YELLOW, BLACK);
		}else{
			color(BLACK, WHITE);
		}
		gotoxy(x, y++);
		insertarCaracteres(ANCHO_PANTALLA, ' ');
		if(i < cantDatos){
			gotoxy(x, y - 1);
			if(i == -1){
				printf(" \tIngreso manual (Esc)");
			} else{
				mostrarPrestamo(prestamos[i]);
			}
		}
	}
}

boolean comparePrestamoID(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Prestamo *)data)->ID_prestamo;
}