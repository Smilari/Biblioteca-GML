#ifndef SOCIOS_H_
#define SOCIOS_H_
#include "utils.h"

typedef struct {
	size_t ID_socio;
	string nombre;
	string apellido;
	size_t DNI;
	int telefono;
	string direccion;
	string mail;
} Socio;

void altaSocio();
void cargarDatosSocio();
void listSocios(Socio socios[], int cantSocios);
void listAllSocios();
void mostrarSocio(Socio socio);
void consultarSocio();


boolean compareSocioDNI(const void *searchValue, const void *data);

#include "../Socios.c"
#endif //SOCIOS_H_
