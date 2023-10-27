#include "Headers/Archivos.h"

/** @brief Esta función verifica la existencia de archivos en las rutas especificadas y los crea si no existen.
	Luego, muestra un mensaje de estado para cada archivo.*/

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

/** @brief Esta función crea un subdirectorio 'Archivos' en la ruta actual. **/

void crearDirectorio() {
	static stringPath path;
	getcwd(path, sizeof(path)); // Obtiene el directorio de trabajo actual y lo almacena en 'path'.
	path[strlen(path)] = '\\'; // Reemplaza  el \0 por una \.
	strcat(path, "Archivos\\"); // Concatena el subdirectorio 'Archivos' a la ruta.
	CreateDirectory(path, NULL); // Crea el subdirectorio 'Archivos' si no existe.
}

size_t getSizeFromPath(const string path) {
	FILE *file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fclose(file);
	return size;
}

int getCantDatos(const string path, size_t dataSize) {
	size_t fileSize = getSizeFromPath(path);
	return (int) (fileSize / dataSize);
}

void getDatos(void *data, size_t dataSize, const string path) {
	FILE* file = fopen(path, "rb");
	fread(data, dataSize, getCantDatos(path, dataSize), file);
	fclose(file);
}

void *getDato(size_t searchNumber, const string path, size_t dataSize, boolean (*comparar)(const size_t, const void*)) {
	FILE* file = fopen(path, "rb");
	void *dato = NULL;

	fseek(file, 0, SEEK_SET);
	int cantDatos = getCantDatos(path, dataSize);
	for (int i = 0; i < cantDatos; i++) {
		void *temp = malloc(dataSize);
		fread(temp, dataSize, 1, file);
		if (comparar(searchNumber, temp)) {
			dato = malloc(dataSize);
			memcpy(dato, temp, dataSize);
		}
		free(temp);
	}
	fclose(file);
	return dato;
}