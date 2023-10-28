/**************************************************************************/
/** @brief Proyecto de Estructura y Base de Datos.                       **/
/** @version Pre-Alpha                                                   **/
/**************************************************************************/

/** CABECERAS EXTERNAS DE FUNCIONES **/
#include "Headers/utils.h"

/* DEFINICIONES */
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
	bienvenida();
    verificaArchivos();
	menuPrincipal();
	salida();
	return 0;
}

void bienvenida(){
	HWND console = GetConsoleWindow();
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	system("MODE 120, 40");
	clean();
}

void salida() {
	clean();
}