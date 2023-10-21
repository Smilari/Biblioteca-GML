#ifndef LIBROS_H_
#define LIBROS_H_
#include "utils.h"

typedef struct {
	int ID_libro;
	int ID_autor;
	int ID_genero;
	int ID_editorial;
	long long ISBN;
	string titulo;
	int stock;
} Libro;

void altaLibro();
void mostrarLibro(Libro l);
void listLibros(Libro libros[], int cantLibros);
void listAllLibros();
int getLibros(Libro libros[]);
void cargarDatos();

#include "../Libros.c"
#endif /*LIBROS_H_*/

