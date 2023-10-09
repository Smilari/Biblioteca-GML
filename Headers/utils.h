#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <direct.h>
#define CLEAN() system("cls")
#define PAUSE() system("pause")

typedef char string[50];

enum Colors {BLACK=0,BLUE=1,GREEN=2,CYAN=3,RED=4,MAGENTA=5,BROWN=6,LGREY=7,DGREY=8,LBLUE=9,LGREEN=10,LCYAN=11,LRED=12,LMAGENTA=13,YELLOW=14,WHITE=15};

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
void retardo(float seg);
void linea(int x);
int error(string path);
void tecla(void);
void cargar();
void gotoxy(int x,int y);
void color(int Background, int Texto);

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

#include "../Sources/utils.c"
#endif // UTILS_H_INCLUDED
