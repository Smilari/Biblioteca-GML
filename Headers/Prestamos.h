#ifndef BIBLIOTECA_PRESTAMOS_H
#define BIBLIOTECA_PRESTAMOS_H
#include "utils.h"

#define FECHA_NO_ESTABLECIDA ((time_t)0)

typedef struct {
	size_t ID_prestamo;
	size_t ID_libro;
	size_t ID_socio;
	time_t fechaAdquirido;
	time_t fechaEntregado;
} Prestamo;

void altaPrestamo();
void generarPrestamo(Libro *libroPtr, Socio *socioPtr);
void listPrestamos(Prestamo prestamos[], int cantPrestamos);
void mostrarPrestamo(Prestamo param);
void revocarPrestamo();
boolean comparePrestamoID(const void *searchValue, const void *data);
void printPrestamos(const void *data, int y, int opcion, int cantDatos);

#include "../Prestamos.c"
#endif //BIBLIOTECA_PRESTAMOS_H
