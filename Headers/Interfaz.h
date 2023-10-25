#ifndef INTERFAZ_H
#define INTERFAZ_H
#include "utils.h"

#define ANCHO_MENU 30
#define ANCHO_PANTALLA 80
#define ALTO_PANTALLA 25
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define POS_MENU_X ((ANCHO_PANTALLA - ANCHO_MENU)/2)
#define POS_MENU_Y 5

#define SIZEOFARRAY(arr) sizeof(arr) / sizeof(*arr)

typedef struct{
	string opcion;
} OpcionesMenu;

// INTERFAZ DE MENUS
int menu(OpcionesMenu om[], Coordenada xy, int cantOpciones);
void printMenu(OpcionesMenu om[], Coordenada xy, int selector, int cantOpciones);
void printOpcion(string opc);
int subMenu(OpcionesMenu om[], Coordenada xy, int cantOpciones);
void printSubMenu(OpcionesMenu om[], Coordenada xy, int selector, int cantOpciones);

// MENUS CON OPCIONES DE USUARIO
void menuPrincipal();
void menuSocios();
void menuLibros();
void menuPrestamos();

// FUNCIONES DE UTILIDAD
void insertarCaracteres(int cant, char caracter);
int getKey();
long long int capturaCaracter(int cantCaracteres, boolean flagTopeCaracteres);
void header(string titulo, string etiqueta);
int posCentrado(int ancho);
void clean();
boolean guardarCambios();
void guardar();
void cancelar();
void insertarLineas(int cantLineas);
void aviso(string texto, int bgd, int txt);
void lineaDeColor(int bgd, int txt);

#include "../Interfaz.c"
#endif //INTERFAZ_H