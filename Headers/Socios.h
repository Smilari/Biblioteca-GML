#ifndef SOCIOS_H_
#define SOCIOS_H_
#include "utils.h"

typedef struct {
	int ID_socio;
	string nombre;
	string apellido;
	size_t DNI;
	int telefono;
	string direccion;
	string mail;
} Socio;

void altaSocio();
void cargarDatosSocio();


boolean compareSocioDNI(const void *searchValue, const void *data);

#endif //SOCIOS_H_
