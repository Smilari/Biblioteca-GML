#include "Headers/Archivos.h"

/**@brief Esta función verifica la existencia de archivos en las rutas especificadas y los crea si no existen.
 * Luego, muestra un mensaje de estado para cada archivo.
 */
void verificaArchivos() {
	Archivo ar[] = {PATH_EDITORIAL, PATH_AUTOR, PATH_GENERO, PATH_LIBRO, PATH_SOCIO, PATH_PRESTAMO};
	int cantArchivos = SIZEOFARRAY(ar);
	FILE *pArch;
	crearDirectorio();
	clean();
	header("VERIFICANDO EXISTENCIA DE ARCHIVOS", "", WHITE, BLACK);

	for(int i = 0; i < cantArchivos; i++){
		pArch = fopen(ar[i].ruta,"rb"); // Intenta abrir el archivo en modo lectura.
		if (pArch == NULL){
			pArch = fopen(ar[i].ruta,"wb"); // Si el archivo no existe, lo crea en modo escritura binaria.
			fclose(pArch);
			printf("\n=>%-105s ", ar[i].ruta);
			color(RED,BLACK);
			printf(" CREADO ");
			color(BLACK,WHITE);
		}
		else{
			printf("\n=>%-105s ", ar[i].ruta);
			color(GREEN,BLACK);
			printf(" OK ");
			color(BLACK,WHITE);
		}
	}
	tecla(); // Espera a que el usuario presione una tecla.
}

/**@brief Esta función crea un subdirectorio 'Archivos' en la ruta actual. **/
void crearDirectorio() {
	static stringPath path;
	getcwd(path, sizeof(path)); // Obtiene el directorio de trabajo actual y lo almacena en 'path'.
	path[strlen(path)] = '\\'; // Reemplaza  el \0 por una \.
	strcat(path, "Archivos\\"); // Concatena el subdirectorio 'Archivos' a la ruta.
	CreateDirectory(path, NULL); // Crea el subdirectorio 'Archivos' si no existe.
}

/**@brief Obtiene el tamaño en bytes de un archivo especificado por su ruta.
 *
 * @param path La ruta al archivo del cual se desea obtener el tamaño.
 *
 * @return El tamaño en bytes del archivo o cero si no se pudo determinar el tamaño.
 */
size_t getSizeFromPath(const string path) {
	FILE *file = fopen(path, "rb");
	if (file == NULL) {
		return 0; // Si no se pudo abrir el archivo, retorna cero (0) como tamaño.
	}

	fseek(file, 0, SEEK_END); // Se mueve al final del archivo.
	size_t size = ftell(file); // Obtiene la posición actual, que es el tamaño en bytes.
	fclose(file);

	return size; // Retorna el tamaño en bytes del archivo.
}

/**@brief Obtiene la cantidad de datos que pueden almacenarse en un archivo específico, dado el tamaño de cada dato.
 *
 * @param path La ruta al archivo del cual se desea calcular la cantidad de datos.
 * @param dataSize El tamaño en bytes de cada dato.
 *
 * @return La cantidad de datos que pueden almacenarse en el archivo o cero si no se pudo determinar la cantidad.
 */
int getCantDatos(const string path, size_t dataSize) {
	size_t fileSize = getSizeFromPath(path); // Obtiene el tamaño del archivo.
	if (dataSize == 0 || fileSize == 0) {
		return 0; // Si el tamaño de los datos o el tamaño del archivo son cero, retorna cero.
	}

	return (int) (fileSize / dataSize); // Calcula la cantidad de datos que caben en el archivo.
}

/**@brief Lee datos desde un archivo binario y los almacena en un puntero de datos.
 *
 * @param data Un puntero a la ubicación de memoria donde se almacenarán los datos leídos.
 * @param path La ruta al archivo binario del cual se leerán los datos.}
 * @param dataSize El tamaño en bytes de cada dato a leer.
 */
void getDatos(void *data, const string path, size_t dataSize) {
	FILE* file = fopen(path, "rb");
	fread(data, dataSize, getCantDatos(path, dataSize), file); // Lee los datos desde el archivo y los almacena en 'data'.
	fclose(file);
}

/**@brief Busca un dato en un archivo binario y lo devuelve si coincide con un valor de búsqueda.
 *
 * @param searchValue El valor que se utilizará para buscar el dato en el archivo.
 * @param path La ruta al archivo binario en el que se realizará la búsqueda.
 * @param dataSize El tamaño en bytes de cada dato en el archivo.
 * @param comparar Un puntero a una función que compara el valor de búsqueda con los datos en el archivo.
 *
 * @return Un puntero al dato encontrado o NULL si no se encontró una coincidencia.
 */
void *getDato(const void *searchValue, const string path, size_t dataSize, boolean (*comparar)(const void *, const void *)) {
	FILE* file = fopen(path, "rb");
	void *dato = NULL;

	fseek(file, 0, SEEK_SET); // Se mueve al inicio del archivo.
	int cantDatos = getCantDatos(path, dataSize); // Obtiene la cantidad de datos en el archivo.
	for (int i = 0; i < cantDatos; i++) {
		void *temp = malloc(dataSize); // Reserva memoria temporal para almacenar un dato.
		fread(temp, dataSize, 1, file); // Lee un dato desde el archivo y lo almacena en 'temp'.
		if (comparar(searchValue, temp)) {
			dato = malloc(dataSize); // Si se encuentra una coincidencia, se reserva memoria para el dato.
			memcpy(dato, temp, dataSize); // Copia el dato encontrado en 'dato'.
		}
		free(temp); // Libera la memoria temporal.
	}
	fclose(file);

	return dato; // Retorna un puntero al dato encontrado o NULL si no se encontró una coincidencia.
}

/**@brief Busca la posición de un dato en un archivo binario que coincide con un valor de búsqueda.
 *
 * @param searchValue El valor que se utilizará para buscar la posición del dato en el archivo.
 * @param path La ruta al archivo binario en el que se realizará la búsqueda.
 * @param dataSize El tamaño en bytes de cada dato en el archivo.
 * @param comparar Un puntero a una función que compara el valor de búsqueda con los datos en el archivo.
 *
 * @return La posición en bytes del dato encontrado o -1 si no se encontró una coincidencia.
 */
int getPosDato(const void *searchValue, const string path, size_t dataSize, boolean (*comparar)(const void *, const void *)) {
	int cantDatos = getCantDatos(path, dataSize); // Obtiene la cantidad de datos en el archivo.
	void *datos = malloc(cantDatos * dataSize); // Reserva memoria para almacenar todos los datos.
	getDatos(datos, path, dataSize); // Obtiene los datos del archivo y los almacena en 'datos'.

	int pos = -1; // Inicializa la posición como -1 para indicar que no se encontró una coincidencia.
	for (int i = 0; i < cantDatos; i++) {
		const void *dato = (char *)datos + i * dataSize; // Obtiene un dato de 'datos'.
		if (comparar(searchValue, dato)) {
			pos = (int) (i * dataSize); // Si se encuentra una coincidencia, se registra la posición.
		}
	}

	free(datos); // Libera la memoria utilizada para almacenar los datos.
	return pos; // Retorna la posición en bytes del dato encontrado o -1 si no se encontró una coincidencia.
}

boolean existeDato(const void* dato){
	return dato != NULL;
}