#include "Headers/Socios.h"

/**@brief Esta función muestra una interfaz para ingresar datos de un nuevo socio en la base de datos de socios.
 * Despliega un encabezado "ALTA DE REGISTRO" y "SOCIOS", y luego permite al usuario cargar los datos del socio.
 */
void altaSocio(){
	header("ALTA DE REGISTRO", "SOCIOS", LGREEN, WHITE);
	cargarDatosSocio();
	tecla();
}

/**@brief Esta función muestra una interfaz que permite al usuario cargar información sobre un socio en la base de datos de socios.
 * Si el socio ya existe en la base de datos (según su DNI), informa al respecto. Si no existe, registra un nuevo socio.
 */
void cargarDatosSocio() {
	FILE* fSocio = fopen(PATH_SOCIO, "r+b");
	Socio socio;

	socio.ID_socio = getCantDatos(PATH_SOCIO, sizeof(Socio)) + 1; // Asigna un ID de socio único y consecutivo al último registrado.

	printf("DNI: ");
	socio.DNI = capturaCaracter(8, true);

	Socio *socioPtr = getDato(&socio.DNI, PATH_SOCIO, sizeof(Socio), compareSocioDNI); // Busca el socio en la base de datos.

	if(!existeDato(socioPtr)){ // Si el socio no existe, permite la entrada de datos para cargar uno nuevo.
		leerString("\n\nNombre: ", socio.nombre);
		leerString("\nApellido: ", socio.apellido);
		leerString("\nDireccion: ", socio.direccion);
		printf("\nTelefono (Sin guiones y sin cod de area): ");
		socio.telefono = capturaCaracter(8, true);
		leerString("\n\nMail: ", socio.mail);

		while(!verificaMail(socio.mail)){
			clearScreenFrom(POS_Y_AFTER_HEADER);
			leerString("Ingrese un mail valido: ", socio.mail);
		}

		clearScreenFrom(POS_Y_AFTER_HEADER);

		fseek(fSocio, 0L, SEEK_END);

		aviso("REGISTRO DADO DE ALTA", BLUE, WHITE);
		listSocios(&socio, 1);

		if(guardarCambios()){ // Si el usuario confirma guardar los cambios, escribe los datos del socio en el archivo.
			fwrite(&socio, sizeof(Socio), 1, fSocio);
		}

	} else{ // Si el socio existe, avisa y sale del ingreso.
		clearScreenFrom(POS_Y_AFTER_HEADER);
		aviso("REGISTRO DUPLICADO", RED, WHITE);
		cancelar();
	}

	fclose(fSocio);
}

/**@brief Esta función muestra una interfaz que lista todos los socios registrados en la base de datos de socios.
 * Despliega un encabezado "LISTAR REGISTROS" y "SOCIOS", y luego obtiene y muestra todos los socios almacenados.
 */
void listAllSocios() {
	header("LISTAR REGISTROS", "SOCIOS", LBLUE, WHITE);
	int cantSocios = getCantDatos(PATH_SOCIO, sizeof(Socio));
	Socio socios[cantSocios];

	getDatos(socios, PATH_SOCIO, sizeof(Socio));
	listSocios(socios, cantSocios);
	tecla();
}

/**@brief Esta función muestra una interfaz que permite al usuario consultar la información de un socio en la base de datos de socios.
 * Despliega un encabezado "CONSULTAR REGISTRO" y "SOCIOS", y solicita al usuario que ingrese el DNI del socio a consultar.
 * Luego, busca el socio en la base de datos y, si se encuentra, muestra su información en pantalla.
 * Si el socio no existe, muestra un aviso de que este no se encontró.
 */
void consultarSocio(){
	header("CONSULTAR REGISTRO", "SOCIOS", LMAGENTA, WHITE);
	printf("DNI: ");
	size_t DNI = capturaCaracter(8, false);
	insertarLineas(2);

	Socio *socioPtr = getDato(&DNI, PATH_SOCIO, sizeof(Socio), compareSocioDNI);

	if(existeDato(socioPtr)){
		clearScreenFrom(POS_Y_AFTER_HEADER);
		listSocios(socioPtr, 1);
	} else{
		aviso("NO EXISTE ESE SOCIO", RED, WHITE);
		cancelar();
	}
	tecla();
}

/**@brief Esta función muestra una lista de socios en la pantalla, incluyendo su ID, nombre, DNI, telefono, direccion y mail.
 * Puede filtrar la lista para incluir o excluir libros con stock igual a cero según el valor de `incluirStockCero`.
 *
 * @param socios Un arreglo de socios que se va a listar.
 * @param cantSocios La cantidad de socios en el arreglo.
 */
void listSocios(Socio socios[], int cantSocios) {
	insertarLineas(1);
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tNombre\t\t\tDNI\t  Telefono\tDireccion\t Mail\n\n");
	color(BLACK, WHITE);
	for (int i = 0; i < cantSocios; i++) {
		mostrarSocio(socios[i]);
	}
	insertarLineas(3);
}

/**@brief Esta función muestra en la pantalla la información detallada de un socio, incluyendo su ID, nombre, DNI, telefono, direccion y mail.
 *
 * @param socio El socio cuya información se va a mostrar.
 */
void mostrarSocio(Socio socio){
	string nombreCompleto = "";
	strcat(nombreCompleto, socio.nombre);
	strcat(nombreCompleto, " ");
	strcat(nombreCompleto, socio.apellido);

	printf("%-2d\t%-23s %-8lld  %-8d\t%-16s %s\n", socio.ID_socio, nombreCompleto, socio.DNI, socio.telefono, socio.direccion, socio.mail);
}

/**@brief Esta función imprime una lista de socios en la pantalla, presentando información relevante sobre cada socio.
* Permite al usuario seleccionar una opción de socio resaltando la opción actual.
*
* @param data Un puntero a un arreglo de estructuras Socio que contiene los datos de los socios.
* @param y La posición vertical inicial en la que se mostrará la lista de socios en la pantalla.
* @param opcion La opción seleccionada por el usuario o la opción actual que se resaltará en la lista.
* @param cantDatos La cantidad total de socios en la lista.
*/
void printSocios(const void *data, int y, int opcion, int cantDatos){
	const Socio *socios =  (const Socio *)data;
	int x = posCentrado(ANCHO_PANTALLA);
	gotoxy(x, y);
	avisoCorto("Seleccione un socio", BLUE, WHITE);
	gotoxy(x, y = y + 2);
	lineaDeColor(WHITE, BLACK);
	printf("Id\tNombre\t\t\tDNI\t  Telefono\tDireccion\t Mail\n\n");
	y++;
	for (int i = opcion; i < (opcion + OPCIONES_A_MOSTRAR); ++i){
		if(i == opcion) {
			color(YELLOW, BLACK);
		}else{
			color(BLACK, WHITE);
		}
		gotoxy(x, y++);
		insertarCaracteres(ANCHO_PANTALLA, ' ');
		if(i < cantDatos){
			gotoxy(x, y - 1);
			if(i == -1){
				printf(" \tIngreso manual (Esc)");
			} else{
				mostrarSocio(socios[i]);
			}
		}
	}
}

boolean compareSocioDNI(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Socio *)data)->DNI;
}

boolean compareSocioID(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Socio *)data)->ID_socio;
}