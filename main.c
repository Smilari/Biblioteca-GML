/**************************************************************************/
/** @brief Proyecto de Estructura y Base de Datos.                       **/
/** @version Pre-Alpha                                                   **/
/**************************************************************************/
// FALTA DOCUMENTAR Y ELIMINAR CONSTANTES.H

/** CABECERAS EXTERNAS DE FUNCIONES **/
#include "Headers/utils.h"
#include "Headers/Archivos.h"
#include "Headers/Interfaz.h"

/* DEFINICIONES */
#define PATH_SOCIO "Socio.dat"
#define PATH_LIBRO "Libro.dat"
#define PATH_PRESTAMO "Prestamo.dat"
#define PATH_EDITORIAL "Editorial.dat"
#define PATH_AUTOR "Autor.dat"
#define PATH_GENERO "Genero.dat"

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

typedef struct {
	int ID_socio;
	string nombre;
	string apellido;
	int DNI;
	int telefono;
	string direccion;
	string mail;
} Socio;

typedef struct {
	int ID_libro;
	int ID_autor;
	int ID_genero;
	int ID_editorial;
	string ISBN;
	string titulo;
	int stock;
} Libro;

typedef struct {
	int ID_prestamo;
	int ID_libro;
	int ID_socio;
	time_t fecha_adquirido;
	time_t fecha_entregado;
} Prestamo;

/* DEFINICIONES DE METODOS */
void bienvenida();

void salida();

int main() {
	system("MODE 80, 25");
	Archivo ar[] = {PATH_EDITORIAL, PATH_AUTOR, PATH_GENERO, PATH_LIBRO, PATH_SOCIO, PATH_PRESTAMO};
	int cantArchivos = SIZEOFARRAY(ar);
	bienvenida();
    verificaArchivos(ar, cantArchivos);
	menuPrincipal();
	salida();
	return 0;
}

void bienvenida(){
	color(BLACK, WHITE);
	CLEAN();
	tecla();
}

void salida() {
	CLEAN();
}

void listar(FILE *libros) {
	FILE *binario;
	char cad[81];
	if ((libros = fopen(binario, "r+")) == NULL) {
		printf("***ERROR***");
		exit(-1);
	}
}
