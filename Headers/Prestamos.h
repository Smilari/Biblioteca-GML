#ifndef BIBLIOTECA_PRESTAMOS_H
#define BIBLIOTECA_PRESTAMOS_H
#include "utils.h"

#define FECHA_NO_ESTABLECIDA ((time_t)-1)

typedef struct {
	size_t ID_prestamo;
	size_t ID_libro;
	size_t ID_socio;
	time_t fecha_adquirido;
	time_t fecha_entregado;
} Prestamo;

void altaPrestamo();
void generarPrestamo(Libro *libroPtr, Socio *socioPtr);
void listPrestamos(Prestamo prestamos[], int cantPrestamos);

#include "../Prestamos.c"
#endif //BIBLIOTECA_PRESTAMOS_H
