#ifndef ARCHIVOS_H_
#define ARCHIVOS_H_
#include "utils.h"


#define PATH_EDITORIAL "Archivos/Editorial.dat"
#define PATH_AUTOR "Archivos/Autor.dat"
#define PATH_GENERO "Archivos/Genero.dat"
#define PATH_LIBRO "Archivos/Libro.dat"
#define PATH_SOCIO "Archivos/Socio.dat"
#define PATH_PRESTAMO "Archivos/Prestamo.dat"

typedef char stringPath[MAX_PATH]; // String con tope maximo para rutas de archivos

typedef struct{
	stringPath ruta;
} Archivo;

void verificaArchivos();
void crearDirectorio();

size_t getSizeFromPath(const string path);
int getCantDatos(const string path, size_t dataSize);
void getDatos(void *data, size_t dataSize, const string path);
void *getDato(size_t searchNumber, const string path, size_t dataSize, boolean (*comparar)(const size_t, const void*));

#include "../Archivos.c"
#endif /* ARCHIVOS_H_*/

