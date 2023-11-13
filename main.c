/**************************************************************************/
/** @brief Proyecto de Estructura y Base de Datos.                       **/
/** @version Pre-Alpha                                                   **/
/**************************************************************************/

/** CABECERAS EXTERNAS DE FUNCIONES **/
#include <locale.h>
#include "Headers/utils.h"

/* DEFINICIONES DE METODOS */
void configInicial();
void salida();

int main() {
	configInicial();
    verificaArchivos();
	menuPrincipal();
	salida();
	return 0;
}

void configInicial(){
	setlocale(LC_TIME, "spanish");
	HWND console = GetConsoleWindow();
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	system("MODE 120, 40");
	clean();
}

void salida() {
	clean();
}