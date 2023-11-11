#include "Socios.h"

/**@brief Esta función muestra una interfaz para ingresar datos de un nuevo socio en la base de datos de socios.
 * Despliega un encabezado "ALTA DE REGISTRO" y "SOCIOS", y luego permite al usuario cargar los datos del socio.
 */
void altaSocio(){
	header("ALTA DE REGISTRO", "SOCIOS", LGREEN, WHITE);
	cargarDatosSocio();
	tecla();
}

void cargarDatosSocio() {
	FILE* fSocio = fopen(PATH_SOCIO, "r+b");
	Socio socio;

	socio.ID_socio = getCantDatos(PATH_SOCIO, sizeof(Socio)) + 1; // Asigna un ID de socio único y consecutivo al último registrado.

	printf("DNI: ");
	socio.DNI = capturaCaracter(8, true);

	Socio *socioPtr = getDato(&socio.DNI, PATH_SOCIO, sizeof(Socio), compareSocioDNI); // Busca el libro en la base de datos.

	if(!existeDato(socioPtr)){ // Si el socio no existe, permite la entrada de datos para cargar uno nuevo.
		leerString("\nNombre: ", socio.nombre);
		leerString("\nApellido: ", socio.apellido);
		leerString("\nDireccion: ", socio.direccion);

		clearScreenFrom(POS_Y_AFTER_HEADER);
		fseek(fSocio, 0L, SEEK_END);

		aviso("REGISTRO DADO DE ALTA", BLUE, WHITE);


		if(guardarCambios()){ // Si el usuario confirma guardar los cambios, escribe los datos del socio en el archivo.
//			fwrite(&socio, sizeof(Socio), 1, fSocio);
		}

	} else{ // Si el socio existe, avisa y sale del menu.
		clearScreenFrom(POS_Y_AFTER_HEADER);
		aviso("REGISTRO DUPLICADO", RED, WHITE);
		cancelar();

	}

	fclose(fSocio);
}

boolean compareSocioDNI(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Socio *)data)->DNI;
}