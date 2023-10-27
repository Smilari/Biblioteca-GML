#ifndef LIBROS_H_
#define LIBROS_H_
#include "utils.h"

typedef struct {
	int ID_libro;
	int ID_autor;
	int ID_genero;
	int ID_editorial;
	size_t ISBN;
	string titulo;
	int stock;
} Libro;

typedef struct {
	int ID_editorial;
	string nombre;
} Editorial;

typedef struct {
	int ID_genero;
	string tipo;
} Genero;

typedef struct {
	int ID_autor;
	string nombre;
	string apellido;
} Autor;


// OPCIONES DEL MENU
void altaLibro();
void bajaLibro();
void modificarLibro();
void listAllLibros();
void consultarLibro();


// FUNCIONES DE UTILIDAD PARA GENERO
void altaGenero();
boolean compareGeneroID(const size_t a, const void *b);
void listarGeneros();

// FUNCIONES DE UTILIDAD PARA LIBRO
void cargarDatos();
void listLibros(Libro libros[], int cantLibros);
void mostrarLibro(Libro libro);
int getPosLibro(size_t ISBN);
boolean existeLibro(size_t ISBN);
void borrarLibro (size_t ISBN);
boolean compareLibroISBN(size_t a, const void *b);

#include "../Libros.c"
#endif /*LIBROS_H_*/

