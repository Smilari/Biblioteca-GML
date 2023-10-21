/**************************************************************************/
/** @brief Proyecto de Estructura y Base de Datos.                       **/
/** @version Pre-Alpha                                                   **/
/**************************************************************************/
// FALTA DOCUMENTAR

/** CABECERAS EXTERNAS DE FUNCIONES **/
#include "Headers/utils.h"

/* DEFINICIONES */


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
	bienvenida();
    verificaArchivos();
	menuPrincipal();
	salida();
	return 0;
}

void bienvenida(){
	clean();
	tecla();
}

void salida() {
	clean();
}