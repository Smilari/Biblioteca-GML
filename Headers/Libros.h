#ifndef LIBROS_H_
#define LIBROS_H_
#include "utils.h"

/* DEFINICIONES */
typedef struct {
	size_t ID_libro;
	size_t ID_autor;
	size_t ID_genero;
	size_t ID_editorial;
	size_t ISBN;
	string titulo;
	int stock;
} Libro;

typedef struct {
	size_t ID_editorial;
	string nombre;
} Editorial;

typedef struct {
	size_t ID_genero;
	string nombre;
} Genero;

typedef struct {
	size_t ID_autor;
	string nombreCompleto;
} Autor;

/* DEFINICIONES DE METODOS */
// OPCIONES DEL MENU
void altaLibro();
void bajaLibro();
void modificarLibro();
void listAllLibros();
void consultarLibro();

void headerRegistro(string aviso);

// FUNCIONES DE UTILIDAD PARA AUTOR
size_t altaAutor();
size_t asignarAutor();
void printAutores(const void *data, int y, int opcion, int cantDatos);
void modificarAutor();

// FUNCIONES DE UTILIDAD PARA EDITORIAL
size_t altaEditorial();
size_t asignarEditorial();
void printEditoriales(const void *data, int y, int opcion, int cantDatos);
void modificarEditorial();

// FUNCIONES DE UTILIDAD PARA GENERO
size_t altaGenero();
size_t asignarGenero();
void printGeneros(const void *data, int y, int opcion, int cantDatos);
void modificarGenero();


// FUNCIONES DE UTILIDAD PARA LIBRO
void cargarDatos();
void listLibros(Libro libros[], int cantLibros, boolean incluirStockCero);
void mostrarLibro(Libro libro);
void borrarLibro (Libro *libro);
void printLibros(const void *data, int y, int opcion, int cantDatos);

// FUNCIONES DE COMPARACIÓN
boolean compareLibroISBN(const void *searchValue, const void *data);
boolean compareLibroID(const void *searchValue, const void *data);
boolean compareGeneroNombre(const void *searchValue, const void *data);
boolean compareGeneroID(const void *searchValue, const void *data);
boolean compareEditorialNombre(const void *searchValue, const void *data);
boolean compareEditorialID(const void *searchValue, const void *data);
boolean compareAutorNombre(const void *searchValue, const void *data);
boolean compareAutorID(const void *searchValue, const void *data);

#include "../Libros.c"
#endif /*LIBROS_H_*/

