#ifndef LIBROS_H_
#define LIBROS_H_
#include "utils.h"

/* DEFINICIONES */
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
	string nombreCompleto;
} Autor;

/* DEFINICIONES DE METODOS */
// OPCIONES DEL MENU
void altaLibro();
void bajaLibro();
void modificarLibro();
void listAllLibros();
void consultarLibro();

// FUNCIONES DE UTILIDAD PARA AUTOR
int altaAutor();
int asignarAutor();
void printAutores(const void *data, int y, int opcion, int cantDatos);

// FUNCIONES DE UTILIDAD PARA EDITORIAL
int altaEditorial();
int asignarEditorial();
void printEditoriales(const void *data, int y, int opcion, int cantDatos);


// FUNCIONES DE UTILIDAD PARA GENERO
int altaGenero();
int asignarGenero();
void printGeneros(const void *data, int y, int opcion, int cantDatos);


// FUNCIONES DE UTILIDAD PARA LIBRO
void cargarDatos();
void listLibros(Libro libros[], int cantLibros, boolean incluirStockCero);
void mostrarLibro(Libro libro);
void borrarLibro (Libro *libro);
void printLibros(const void *data, int y, int opcion, int cantDatos);

// FUNCIONES DE COMPARACIÓN
boolean compareLibroISBN(const void *searchValue, const void *data);
boolean compareLibroID(const void *searchValue, const void *data);
boolean compareGeneroTipo(const void *searchValue, const void *data);
boolean compareGeneroID(const void *searchValue, const void *data);
boolean compareEditorialNombre(const void *searchValue, const void *data);
boolean compareEditorialID(const void *searchValue, const void *data);
boolean compareAutorNombre(const void *searchValue, const void *data);
boolean compareAutorID(const void *searchValue, const void *data);

#include "../Libros.c"
#endif /*LIBROS_H_*/

