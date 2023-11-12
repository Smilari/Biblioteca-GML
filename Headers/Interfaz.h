#ifndef INTERFAZ_H
#define INTERFAZ_H
#include "utils.h"

#define ANCHO_MENU 30
#define ANCHO_PANTALLA 120
#define ALTO_PANTALLA 40
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define ESC 27
#define ENTER 13
#define BACKSPACE 8
#define ARROBA '@'
#define PUNTO '.'
#define POS_MENU_X ((ANCHO_PANTALLA - ANCHO_MENU)/2)
#define POS_MENU_Y 5
#define POS_Y_AFTER_HEADER 6
#define OPCIONES_A_MOSTRAR 10

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
void menuModificar();

// FUNCIONES DE UTILIDAD
void insertarCaracteres(int cant, char caracter);
int getKey();
size_t capturaCaracter(int cantCaracteres, boolean flagTopeCaracteres);
void header(string titulo, string etiqueta, int bgd, int txt);
int posCentrado(int ancho);
int posDerecha(int ancho);
void clean();
boolean guardarCambios();
void guardar();
void cancelar();
void insertarLineas(int cantLineas);
void aviso(string texto, int bgd, int txt);
void avisoCorto(string texto, int bgd, int txt);
void lineaColorEn(int bgd, int txt, int ancho, int xInicial);
void lineaDeColor(int bgd, int txt);
void clearScreenFrom(int y);
int dataMenu(const string path, size_t dataSize, int y, void (*printFunction)(const void *, int, int, int));
boolean verificaMail(string mail);
boolean esAlfanumerico(char c);

#include "../Interfaz.c"
#endif //INTERFAZ_H