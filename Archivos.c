#include "Headers/Archivos.h"

/*  Descripción: Esta función verifica la existencia de archivos en las rutas especificadas y los crea si no existen.
 * Luego, muestra un mensaje de estado para cada archivo.*/

void verificaArchivos() {
	Archivo ar[] = {PATH_EDITORIAL, PATH_AUTOR, PATH_GENERO, PATH_LIBRO, PATH_SOCIO, PATH_PRESTAMO};
	int cantArchivos = SIZEOFARRAY(ar);
	FILE *pArch;
	crearDirectorio();
	clean();
	header("VERIFICANDO EXISTENCIA DE ARCHIVOS", "");

	for(int i = 0; i < cantArchivos; i++){
		pArch = fopen(ar[i].ruta,"rb"); // Intenta abrir el archivo en modo lectura.
		if (pArch == NULL){
			pArch = fopen(ar[i].ruta,"wb"); // Si el archivo no existe, lo crea en modo escritura binaria.
			fclose(pArch);
			printf("\n=>%-65s ", ar[i].ruta);
			color(RED,BLACK);
			printf(" CREADO ");
			color(BLACK,WHITE);
		}
		else{
			printf("\n=>%-65s ", ar[i].ruta);
			color(GREEN,BLACK);
			printf(" OK ");
			color(BLACK,WHITE);
		}
	}
	tecla(); // Espera a que el usuario presione una tecla.
}

/*  Descripción: Esta función crea un subdirectorio 'Archivos' en la ruta actual.*/

void crearDirectorio() {
	static stringPath path;
	getcwd(path, sizeof(path)); // Obtiene el directorio de trabajo actual y lo almacena en 'path'.
	path[strlen(path)] = '\\'; // Reemplaza  el \0 por una \.
	strcat(path, "Archivos\\"); // Concatena el subdirectorio 'Archivos' a la ruta.
	CreateDirectory(path, NULL); // Crea el subdirectorio 'Archivos' si no existe.
}