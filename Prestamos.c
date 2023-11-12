#include "Headers/Prestamos.h"


void mostrarPrestamo(Prestamo param);

void altaPrestamo(){
	header("ALTA DE REGISTRO", "PRESTAMO", LGREEN, WHITE);
	size_t opcionLibro = dataMenu(PATH_LIBRO, sizeof(Libro),POS_Y_AFTER_HEADER ,printLibros);

	if(!opcionLibro){
		printf("ISBN: ");
		opcionLibro = capturaCaracter(13, true);
	}
	Libro *libroPtr = getDato(&opcionLibro, PATH_LIBRO, sizeof(Libro), compareLibroID);

	if(existeDato(libroPtr)){
		if (libroPtr->stock != 0){
			size_t opcionSocio = dataMenu(PATH_SOCIO, sizeof(Socio), POS_Y_AFTER_HEADER, printSocios);

			if(!opcionSocio){
				printf("DNI: ");
				opcionSocio = capturaCaracter(8, true);
			}
			Socio *socioPtr = getDato(&opcionSocio, PATH_SOCIO, sizeof(Socio), compareSocioID);

			if(existeDato(socioPtr)){
				generarPrestamo(libroPtr, socioPtr);
			} else{
				aviso("NO EXISTE ESE SOCIO", RED, WHITE);
				cancelar();
			}
		} else{
			aviso("LIBRO FUERA DE STOCK", RED, WHITE);
			cancelar();
		}
	} else{
		aviso("NO EXISTE ESE LIBRO", RED, WHITE);
		cancelar();
	}

	tecla();
}

void generarPrestamo(Libro *libroPtr, Socio *socioPtr) {
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	FILE* fPrestamo = fopen(PATH_PRESTAMO, "r+b");
	Prestamo prestamo;

	fseek(fPrestamo, 0L, SEEK_END);
	fseek(fLibro, getPosDato(&socioPtr, PATH_LIBRO, sizeof(Libro), compareLibroID), SEEK_SET);

	// Elimina del stock de libros una unidad.
	libroPtr->stock--;

	prestamo.ID_prestamo = getCantDatos(PATH_PRESTAMO, sizeof(Prestamo)) + 1; // Asigna un ID de prestamo único y consecutivo al último registrado.
	prestamo.ID_libro = libroPtr->ID_libro;
	prestamo.ID_socio = socioPtr->ID_socio;
	prestamo.fecha_adquirido = time(NULL);
	prestamo.fecha_entregado = FECHA_NO_ESTABLECIDA;

	listPrestamos(&prestamo, 1);
	if(guardarCambios()){
		fwrite(libroPtr, sizeof(Libro), 1, fLibro);
		fwrite(&prestamo, sizeof(Prestamo), 1, fPrestamo);
	}

	fclose(fLibro);
	fclose(fPrestamo);
}

void listAllPrestamos() {
	header("LISTAR REGISTROS", "PRESTAMOS", LBLUE, WHITE);
	int cantPrestamos = getCantDatos(PATH_PRESTAMO, sizeof(Prestamo));
	Prestamo prestamos[cantPrestamos];

	getDatos(prestamos, PATH_PRESTAMO, sizeof(Prestamo));

	listPrestamos(prestamos, cantPrestamos);
	tecla();
}


void listPrestamos(Prestamo prestamos[], int cantPrestamos) {
	insertarLineas(1);
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tNombre\t  Apellido\t  DNI\t  Titulo\t\tLibro\tISBN\n\n");
	color(BLACK, WHITE);
	for (int i = 0; i < cantPrestamos; i++) {
		mostrarPrestamo(prestamos[i]);
	}
	insertarLineas(3);
}

void mostrarPrestamo(Prestamo prestamo) {
	size_t id = prestamo.ID_libro;
	Libro libro = *(Libro*)getDato(&id, PATH_LIBRO, sizeof(Libro), compareLibroID);
	id = prestamo.ID_socio;
	Socio socio = *(Socio*)getDato(&id, PATH_SOCIO, sizeof(Socio), compareSocioID);

	printf("%-2lld\t%-10s%-10s%-10lld%-16s%-8lld\n\n", prestamo.ID_prestamo, socio.nombre, socio.apellido, socio.DNI, libro.titulo, libro.ISBN);
}
