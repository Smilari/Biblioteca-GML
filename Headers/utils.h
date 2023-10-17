#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <limits.h>
#define CLEAN() system("cls")
#define PAUSE() system("pause")

// LINEAS SIMPLES
/*
#define LINEA_MEDIO 196 // ─
#define LINEA_VERTICAL "179" // │
#define INFERIOR_IZQ 192 // └
#define INFERIOR_DER 217 // ┘
#define SUPERIOR_IZQ 218 // ┌
#define SUPERIOR_DER 191 // ┐
#define MEDIO_IZQ 195 // ├
#define MEDIO_DER 180 // ┤
 */
// LINEAS DOBLES
#define LINEA_MEDIO 205 // ═
#define INFERIOR_IZQ 200 // ╚
#define INFERIOR_DER 188 // ╝
#define LINEA_VERTICAL 186 // ║
#define SUPERIOR_IZQ 201// ╔
#define SUPERIOR_DER 187 // ╗
#define MEDIO_IZQ 204 // ╠
#define MEDIO_DER 185 // ╣

// Structs
typedef struct {
	int x;
	int y;
} Coordenada;
typedef char string[50];

enum Colors {BLACK=0,BLUE=1,GREEN=2,CYAN=3,RED=4,MAGENTA=5,BROWN=6,LGREY=7,DGREY=8,LBLUE=9,LGREEN=10,LCYAN=11,LRED=12,LMAGENTA=13,YELLOW=14,WHITE=15};

enum CURSORTYPE{
	_NOCURSOR,//     turns off the cursor
	_SOLIDCURSOR,//  solid block cursor
	_NORMALCURSOR // normal underscore cursor
};

// Lectura de datos
int leerEntero(string mensaje);
float leerFloat(string mensaje);
char leerCaracter(string mensaje);
int leerEnteroEntre(int valorMin, int valorMax, string mensaje);
float leerFloatEntre(float valorMin, float valorMax, string mensaje);
void leerString(string mensaje, string str);
void leerStringEntre(int minLength, int maxLength, string mensaje, string str);

// Vectores
void leerVectorDeEnteros(string mensaje, int vec[], int cant);
void leerVectorDeFloats(string mensaje, float vec[], int cant);
void leerVectorDeCaracteres(string mensaje, char vec[], int cant);
void leerVectorDeEnterosEntre(int valorMin, int valorMax, string mensaje, int vec[], int cant);
void leerVectorDeFloatsEntre(float valorMin, float valorMax, string mensaje, float vec[], int cant);
void mostrarVectorEnteros(int vec[], int cant);
void mostrarVectorFloats(float vec[], int cant);
void mostrarVectorDeCaracteres(char vec[], int cant);

// Utilidad
int generarNumAleatorio(int valorMin, int valorMax);
int sonIguales(string texto, string texto2);
void swap(int *a, int *b);
bool confirmaUsuario(string mensaje);
void insertarEnter(int x);
int error(string path);
void tecla(void);

// Visual / Estetico
void lineaVertical(int largo);
void lineaVerticalEn(Coordenada xy, int largo);
void lineaHorizontal(int largo, int cod);
void lineaHorizontalEn(Coordenada xy, int largo, int cod);
void retardo(float seg);
void cargar();
void color(int Background, int Texto);
void recuadroSimple(int alto, int ancho);
void _setcursortype(int cur_t);

// Posicion
void gotoxy(int x,int y);
int wherex(void);
int wherey(void);
Coordenada getCoordenada();

// Ordenamiento
void bubbleSortAsc (int numeros[], int cant);
void bubbleSortDesc (int numeros[], int cant);

// Busqueda
int buscarLineal(int vec[], int cant, int valorB);
int buscarBinario(int vec[], int min, int max, int valorB);

// Matrices
void leerMatrizDeEnteros(string mensaje, int f, int c, int mat[f][c]);
void leerMatrizDeFloats(string mensaje, int f, int c, float mat[f][c]);
void leerMatrizDeCaracteres(string mensaje, int f, int c, char mat[f][c]);
void mostrarMatrizDeEnteros(int f, int c, int mat[f][c]);
void mostrarMatrizDeFloats(int f, int c, float mat[f][c]);
void mostrarMatrizDeCaracteres(int f, int c, char mat[f][c]);

// Archivos
FILE* abrirArchivo(string path, string tipo);
void cerrarArchivo(FILE* pArch, char path[]);
int existeArchivo(FILE* pArch);
void agregarTXT(string archiveName);
FILE* abrirArchivoBinario(string path, string tipo);

#include "../utils.c"
#endif // UTILS_H_INCLUDED
