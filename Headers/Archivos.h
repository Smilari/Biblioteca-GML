#ifndef ARCHIVOS_H_
#define ARCHIVOS_H_
#include "utils.h"

/* DEFINICIONES */
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

/* DEFINICIONES DE METODOS */
void verificaArchivos();
void crearDirectorio();

// MANEJO DE DATOS EN ARCHIVOS
size_t getSizeFromPath(const string path);
int getCantDatos(const string path, size_t dataSize);
void getDatos(void *data, const string path, size_t dataSize);
void *getDato(const void *searchValue, const string path, size_t dataSize, boolean (*comparar)(const void *, const void *));
int getPosDato(const void *searchValue, const string path, size_t dataSize, boolean (*comparar)(const void *, const void *));
boolean existeDato(const void* dato);

#include "../Archivos.c"
#endif /* ARCHIVOS_H_*/

