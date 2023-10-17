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
#define POS_MENU_X ((ANCHO_PANTALLA - ANCHO_MENU)/2)
#define POS_MENU_Y 5

#define SIZEOFARRAY(arr) sizeof(arr) / sizeof(*arr)

typedef struct {
	string opcion;
} OpcionesMenu;

int menu(OpcionesMenu om[], Coordenada xy, int cantOpciones);
void printMenu(OpcionesMenu om[], Coordenada xy, int selector, int cantOpciones);
void printOpcion(string opc);
void insertCaracteres(int cant, char caracter);
int getKey();

void menuPrincipal();
void menuSocios();
void menuLibros();
void menuPrestamos();

void header(string titulo, string etiqueta);
int posCentrado(string str);


#include "../Interfaz.c"
#endif //INTERFAZ_H