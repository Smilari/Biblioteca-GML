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

// FUNCIONES DE UTILIDAD
void cargarDatos();
int getCantLibros();
void getLibros(Libro libros[]);
void getDatos(void *data, size_t data_size, size_t num_items, const char *path);
void listLibros(Libro libros[], int cantLibros);
void mostrarLibro(Libro libro);
int getPosLibro(long long ISBN);
Libro getLibro(long long ISBN);
boolean existeLibro(long long ISBN);
void borrarLibro (long long ISBN);

#include "../Libros.c"
#endif /*LIBROS_H_*/

