#include "Headers/Libros.h"

/**@brief Esta función muestra una interfaz para ingresar datos de un nuevo libro en la base de datos de libros.
 * Despliega un encabezado "ALTA DE REGISTRO" y "LIBROS", y luego permite al usuario cargar los datos del libro.
 */
void altaLibro(){
	header("ALTA DE REGISTRO", "LIBROS", LGREEN, WHITE);
	cargarDatos();
	tecla();
}

/**@brief Esta función muestra una interfaz para buscar y dar de baja un libro de la base de datos de libros.
 * Despliega un encabezado "BAJA DE REGISTRO" y "LIBROS", y solicita al usuario que ingrese el ISBN del libro a dar de baja.
 * Luego, busca el libro en la base de datos y, si se encuentra, procede a eliminarlo (lógicamente).
 * Si el libro no existe, muestra un aviso de que el libro no se encontró.
 */
void bajaLibro(){
	header("BAJA DE REGISTRO", "LIBROS", LRED, WHITE);
	Libro *libroPtr;

	size_t opcion = dataMenu(PATH_LIBRO, sizeof(Libro), POS_Y_AFTER_HEADER, printLibros);

	if(opcion == 0){
		printf("ISBN: ");
		size_t ISBN = capturaCaracter(13, false);
		libroPtr = getDato(&ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);
	} else{
		libroPtr = getDato(&opcion, PATH_LIBRO, sizeof(Libro), compareLibroID);
	}

	if(existeDato(libroPtr)){
		borrarLibro(libroPtr);
	} else{
		aviso("NO EXISTE ESE LIBRO", RED, WHITE);
		cancelar();
	}
	tecla();
}

void modificarLibro(){
	header("MODIFICAR REGISTRO", "LIBROS", BLUE, WHITE);
	tecla();
}

/**@brief Esta función muestra una interfaz que lista todos los libros registrados en la base de datos de libros.
 * Despliega un encabezado "LISTAR REGISTROS" y "LIBROS", y luego obtiene y muestra todos los libros almacenados.
 */
void listAllLibros() {
	header("LISTAR REGISTROS", "LIBROS", LBLUE, WHITE);
	int cantLibros = getCantDatos(PATH_LIBRO, sizeof(Libro));
	Libro libros[cantLibros];

	getDatos(libros, PATH_LIBRO, sizeof(Libro));

	listLibros(libros, cantLibros, false);
	tecla();
}

/**@brief Esta función muestra una interfaz que permite al usuario consultar la información de un libro en la base de datos de libros.
 * Despliega un encabezado "CONSULTAR REGISTRO" y "LIBROS", y solicita al usuario que ingrese el ISBN del libro a consultar.
 * Luego, busca el libro en la base de datos y, si se encuentra, muestra su información en pantalla.
 * Si el libro no existe, muestra un aviso de que el libro no se encontró.
 */
void consultarLibro(){
	header("CONSULTAR REGISTRO", "LIBROS", LMAGENTA, WHITE);
	printf("ISBN: ");
	size_t ISBN = capturaCaracter(13, false);
	insertarLineas(2);

	Libro *libroPtr = getDato(&ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);

	if(existeDato(libroPtr)){
		clearScreenFrom(POS_Y_AFTER_HEADER);
		listLibros(libroPtr, 1, true);
	} else{
		aviso("NO EXISTE ESE LIBRO", RED, WHITE);
		cancelar();
	}
	tecla();
}

/**@brief Esta función muestra una interfaz que permite al usuario cargar información sobre un libro en la base de datos de libros.
 * Si el libro ya existe en la base de datos (según su ISBN), actualiza el stock. Si no existe, registra un nuevo libro.
 */
void cargarDatos() {
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro libro;

	libro.ID_libro = getCantDatos(PATH_LIBRO, sizeof(Libro)) + 1; // Asigna un ID de libro único y consecutivo al último registrado.
	libro.stock = 1;

	printf("ISBN: ");
	libro.ISBN = capturaCaracter(13, true);

	Libro *libroPtr = getDato(&libro.ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN); // Busca el libro en la base de datos.

	if(!existeDato(libroPtr)){ // Si el libro no existe, permite la entrada de datos para cargar uno nuevo.
		libro.ID_genero = asignarGenero();
		libro.ID_autor = asignarAutor();
		libro.ID_editorial = asignarEditorial();

		clearScreenFrom(POS_Y_AFTER_HEADER);
		leerString("Titulo: ", libro.titulo);

		fseek(fLibro, 0L, SEEK_END);

		clearScreenFrom(POS_Y_AFTER_HEADER);
		aviso("REGISTRO DADO DE ALTA", BLUE, WHITE);
	} else{ // Si el libro existe, añade stock al registro.
		clearScreenFrom(POS_Y_AFTER_HEADER);
		aviso("REGISTRO ENCONTRADO, SE ACTUALIZO EL STOCK", BLUE, WHITE);
		libro = *libroPtr; // Copia los datos del libro encontrado.
		libro.stock++;

		fseek(fLibro, getPosDato(&libro.ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN), SEEK_SET); // Se mueve a la posición del libro en el archivo.
	}

	listLibros(&libro, 1, true); // Muestra la información del libro.

	if(guardarCambios()){ // Si el usuario confirma guardar los cambios, escribe los datos del libro en el archivo.
		fwrite(&libro, sizeof(libro), 1, fLibro);
	}

	fclose(fLibro);
}

/**@brief Muestra una lista de libros en la pantalla.
 * Esta función muestra una lista de libros en la pantalla, incluyendo su ID, título, stock, ISBN, género, editorial y autor.
 * Puede filtrar la lista para incluir o excluir libros con stock igual a cero según el valor de `incluirStockCero`.
 *
 * @param libros Un arreglo de libros que se va a listar.
 * @param cantLibros La cantidad de libros en el arreglo.
 * @param incluirStockCero Un valor booleano que determina si se deben incluir libros con stock igual a cero.
 */
void listLibros(Libro libros[], int cantLibros, boolean incluirStockCero) {
	insertarLineas(1);
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tTitulo\t\t\tStock\tISBN\t\tGenero\t\tAutor\t\t\tEditorial\n\n");
	color(BLACK, WHITE);
	for (int i = 0; i < cantLibros; i++) {
		if(incluirStockCero || libros[i].stock != 0){
			mostrarLibro(libros[i]);
		}
	}
	insertarLineas(3);
}


/**@brief Muestra la información detallada de un libro en la pantalla.
 * Esta función muestra en la pantalla la información detallada de un libro, incluyendo su ID, título, stock, ISBN, género, editorial y autor.
 * Para obtener la información de género, editorial y autor, se realizan búsquedas en las bases de datos correspondientes.
 *
 * @param libro El libro cuya información se va a mostrar.
 */
void mostrarLibro(Libro libro){
	size_t id = libro.ID_genero;
	Genero genero = *(Genero*)getDato(&id, PATH_GENERO, sizeof(Genero), compareGeneroID);

	id = libro.ID_editorial;
	Editorial editorial = *(Editorial*)getDato(&id, PATH_EDITORIAL, sizeof(Editorial), compareEditorialID);

	id = libro.ID_autor;
	Autor autor = *(Autor*)getDato(&id, PATH_AUTOR, sizeof(Autor), compareAutorID);

	printf("%-2d\t%-22s\t%d\t%-13lld\t%-14s\t%-22s\t%s\n", libro.ID_libro, libro.titulo, libro.stock, libro.ISBN, genero.nombre, autor.nombreCompleto, editorial.nombre);
}

/**@brief Esta función disminuye el stock de un libro en la base de datos de libros.
 * Si el libro tiene stock disponible, se reduce en 1 unidad y se actualizan los datos en la base de datos.
 * Si el libro no tiene más unidades disponibles, se muestra un mensaje de advertencia al usuario.
 *
 * @param libro Un puntero a la estructura de datos del libro que se desea actualizar en la base de datos.
 */
void borrarLibro(Libro *libro){
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	fseek(fLibro, getPosDato(&libro->ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN), SEEK_SET);
	// Se mueve a la posición del libro en el archivo.

	if(libro->stock > 0){ // Si el libro tiene stock disponible, lo disminuye en 1.
		libro->stock--;
		aviso("STOCK ACTUALIZADO", BLUE, WHITE);
		listLibros(libro, 1, true);
		if(guardarCambios()){ // Si el usuario confirma guardar los cambios, sobreescribe los datos en el archivo.
			fwrite(libro, sizeof(Libro), 1, fLibro);
		}
	}else{
		aviso("NO EXISTEN MAS UNIDADES DE ESTE LIBRO", RED, WHITE);
		cancelar();
	}
	fclose(fLibro);
}

/**@brief Esta función imprime una lista de libros en la pantalla, presentando información relevante sobre cada libro.
 * Permite al usuario seleccionar una opción de libro resaltando la opción actual.
 *
 * @param data Un puntero a un arreglo de estructuras Libro que contiene los datos de los libros.
 * @param y La posición vertical inicial en la que se mostrará la lista de libros en la pantalla.
 * @param opcion La opción seleccionada por el usuario o la opción actual que se resaltará en la lista.
 * @param cantDatos La cantidad total de libros en la lista.
 */
void printLibros(const void *data, int y, int opcion, int cantDatos){
	const Libro *libros =  (const Libro *)data;
	int x = posCentrado(ANCHO_PANTALLA);
	gotoxy(x, y);
	avisoCorto("Seleccione un libro", BLUE, WHITE);
	gotoxy(x, y = y + 2);
	lineaDeColor(WHITE, BLACK);
	printf("Id\tTitulo\t\t\tStock\tISBN\t\tGenero\t\tAutor\t\t\tEditorial\n\n");
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
				mostrarLibro(libros[i]);
			}
		}
	}
}

void headerRegistro(string aviso){
	const int ancho = 30;
	int x = posCentrado(ancho);
	int y = getCoordenada().y;
	gotoxy(x, y);
	avisoCorto(aviso, BLUE, WHITE);
	gotoxy(x, y = y + 2);
	lineaColorEn(WHITE, BLACK, ancho, x);
	printf("Id\tNombre");
	gotoxy(x, y + 1);
	color(BLACK, WHITE);
}

/**@brief Agrega un nuevo género a la base de datos de géneros o recupera un género existente.
 * Esta función permite al usuario agregar un nuevo género a la base de datos de géneros o recuperar un género existente si ya se encuentra en la base de datos.
 * El usuario ingresa el nombre del género, y se busca si ya existe en la base de datos. Si existe, se recupera ese género. Si no existe, se agrega uno nuevo.
 *
 * @return El ID del género agregado o recuperado.
 */
size_t altaGenero(){
	FILE* fGenero = fopen(PATH_GENERO, "r+b");
	Genero genero;

	clearScreenFrom(POS_Y_AFTER_HEADER);
	genero.ID_genero = getCantDatos(PATH_GENERO, sizeof(Genero)) + 1; // Asigna un ID de género único y consecutivo al último registrado.
	leerString("Genero: ", genero.nombre);

	Genero *generoPtr = getDato(&genero.nombre, PATH_GENERO, sizeof(Genero), compareGeneroNombre);

	if(existeDato(generoPtr)){ // Si el género ya existe en la base de datos, lo recupera.
		genero = *generoPtr;
	} else{ // Si el género no existe en la base de datos, lo escribe al final del archivo.
		fseek(fGenero, 0L, SEEK_END);
		fwrite(&genero, sizeof(genero), 1, fGenero);
	}

	fclose(fGenero);

	return genero.ID_genero; // Devuelve el ID del género agregado o recuperado.
}

/**@brief Esta función imprime una lista de géneros en la pantalla, presentando información relevante sobre cada genero.
 * Permite al usuario seleccionar una opción de genero resaltando la opción actual.
 *
 * @param data Un puntero a un arreglo de estructuras Genero que contiene los datos de los géneros.
 * @param y La posición vertical inicial en la que se mostrará la lista de géneros en la pantalla.
 * @param opción La opción seleccionada por el usuario o la opción actual que se resaltará en la lista.
 * @param cantDatos La cantidad total de géneros en la lista.
 */
void printGeneros(const void *data, int y, int opcion, int cantDatos){
	const Genero *generos =  (const Genero *)data;
	const int ancho = 30;
	gotoxy(0, y);
	headerRegistro("Seleccione un genero");
	int x = getCoordenada().x;
	y = getCoordenada().y;
	gotoxy(x,y + 1);
	for (int i = opcion; i < (opcion + OPCIONES_A_MOSTRAR); ++i){
		if(i == opcion) {
			color(YELLOW, BLACK);
		}else{
			color(BLACK, WHITE);
		}
		gotoxy(x, y++);
		insertarCaracteres(ancho, ' ');
		if(i < cantDatos){
			gotoxy(x, y - 1);
			if(i == -1){
				printf("   Ingreso manual (Esc)");
			} else{
				printf("%-2d\t%-25s\n", generos[i].ID_genero, generos[i].nombre);
			}
		}
	}
}

/**@brief Esta función muestra una lista de géneros disponibles en la base de datos de géneros y permite al usuario
 * seleccionar uno de ellos para asignarlo a un libro. Si el usuario decide agregar un nuevo género que no se encuentra
 * en la base de datos, la función permitirá agregarlo.
 *
 * @return El ID del género asignado al libro.
 */
size_t asignarGenero(){
	size_t opcion = dataMenu(PATH_GENERO, sizeof(Genero), POS_Y_AFTER_HEADER, printGeneros);
	if(opcion == 0){
		opcion = altaGenero();
	}
	return opcion;
}

void modificarGenero(){
	header("MODIFICAR REGISTRO", "GENERO", BLUE, WHITE);
	Genero *generoPtr;
	FILE* fGenero = fopen(PATH_GENERO, "r+b");

	size_t opcion = dataMenu(PATH_GENERO, sizeof(Genero), POS_Y_AFTER_HEADER, printGeneros);
	generoPtr = getDato(&opcion, PATH_GENERO, sizeof(Genero), compareGeneroID);

	if(opcion == 0){
		string nombre;
		leerString("Genero: ", nombre);
		generoPtr = getDato(nombre, PATH_GENERO, sizeof(Genero), compareGeneroNombre);
		clearScreenFrom(POS_Y_AFTER_HEADER);
	}
	if(existeDato(generoPtr)){
		leerString("Ingrese el nuevo nombre: ", generoPtr->nombre);
		clearScreenFrom(POS_Y_AFTER_HEADER);
		headerRegistro("NOMBRE ACTUALIZADO");
		printf("%-2d\t%-25s\n\n", generoPtr->ID_genero, generoPtr->nombre);
		if(guardarCambios()){
			fseek(fGenero, getPosDato(&generoPtr->ID_genero, PATH_GENERO, sizeof(Genero), compareGeneroID), SEEK_SET);
			fwrite(generoPtr, sizeof(Genero), 1, fGenero);
		}
	} else{
		aviso("NO EXISTE ESE GENERO", RED, WHITE);
		cancelar();
	}
	tecla();
	fclose(fGenero);
}

/**@brief Agrega una nueva editorial a la base de datos de editoriales o recupera una editorial existente.
 * Esta función permite al usuario agregar una nueva editorial a la base de datos de editoriales o recuperar una editorial existente si ya se encuentra en la base de datos.
 * El usuario ingresa el nombre de la editorial, y se busca si ya existe en la base de datos. Si existe, se recupera esa editorial. Si no existe, se agrega una nueva.
 *
 * @return El ID de la editorial agregada o recuperada.
 */
size_t altaEditorial(){
	FILE* fEditorial = fopen(PATH_EDITORIAL, "r+b");
	Editorial editorial;

	clearScreenFrom(POS_Y_AFTER_HEADER);
	editorial.ID_editorial = getCantDatos(PATH_EDITORIAL, sizeof(Editorial)) + 1; // Asigna un ID de editorial único y consecutivo al último registrado.
	leerString("Editorial: ", editorial.nombre);

	Editorial *editorialPtr = getDato(&editorial.nombre, PATH_EDITORIAL, sizeof(Editorial), compareEditorialNombre);

	if(existeDato(editorialPtr)){ // Si la editorial ya existe en la base de datos, lo recupera.
		editorial = *editorialPtr;
	} else{ // Si la editorial no existe en la base de datos, lo escribe al final del archivo.
		fseek(fEditorial, 0L, SEEK_END);
		fwrite(&editorial, sizeof(editorial), 1, fEditorial);
	}

	fclose(fEditorial);

	return editorial.ID_editorial; // Devuelve el ID de la editorial agregada o recuperada.
}

/**@brief Esta función imprime una lista de editoriales en la pantalla, presentando información relevante sobre cada editorial.
 * Permite al usuario seleccionar una opción de editorial resaltando la opción actual.
 *
 * @param data Un puntero a un arreglo de estructuras Editorial que contiene los datos de las editoriales.
 * @param y La posición vertical inicial en la que se mostrará la lista de editoriales en la pantalla.
 * @param opción La opción seleccionada por el usuario o la opción actual que se resaltará en la lista.
 * @param cantDatos La cantidad total de editoriales en la lista.
 */
void printEditoriales(const void *data, int y, int opcion, int cantDatos){
	const Editorial *editoriales =  (const Editorial *)data;
	const int ancho = 30;
	gotoxy(0, y);
	headerRegistro("Seleccione una editorial");
	int x = getCoordenada().x;
	y = getCoordenada().y;
	for (int i = opcion; i < (opcion + OPCIONES_A_MOSTRAR); ++i){
		if(i == opcion) {
			color(YELLOW, BLACK);
		}else{
			color(BLACK, WHITE);
		}
		gotoxy(x, y++);
		insertarCaracteres(ancho, ' ');
		if(i < cantDatos){
			gotoxy(x, y - 1);
			if(i == -1){
				printf("   Ingreso manual (Esc)");
			} else{
				printf("%-2d\t%-25s\n", editoriales[i].ID_editorial, editoriales[i].nombre);
			}
		}
	}
}

/**@brief Esta función muestra una lista de editoriales disponibles en la base de datos de editoriales y permite al usuario
 * seleccionar uno de ellos para asignarlo a un libro. Si el usuario decide agregar un nuevo editorial que no se encuentra
 * en la base de datos, la función permitirá agregarlo.
 *
 * @return El ID de la editorial asignado al libro.
 */
size_t asignarEditorial(){
	size_t opcion = dataMenu(PATH_EDITORIAL, sizeof(Editorial), POS_Y_AFTER_HEADER, printEditoriales);
	if(opcion == 0){
		opcion = altaEditorial();
	}
	return opcion;
}

void modificarEditorial(){
	header("MODIFICAR REGISTRO", "EDITORIAL", BLUE, WHITE);
	Editorial *editorialPtr;
	FILE* fEditorial = fopen(PATH_EDITORIAL, "r+b");

	size_t opcion = dataMenu(PATH_EDITORIAL, sizeof(Editorial), POS_Y_AFTER_HEADER, printEditoriales);
	editorialPtr = getDato(&opcion, PATH_EDITORIAL, sizeof(Editorial), compareEditorialID);

	if(opcion == 0){
		string nombre;
		leerString("Editorial: ", nombre);
		editorialPtr = getDato(nombre, PATH_EDITORIAL, sizeof(Editorial), compareEditorialNombre);
		clearScreenFrom(POS_Y_AFTER_HEADER);
	}
	if(existeDato(editorialPtr)){
		leerString("Ingrese el nuevo nombre: ", editorialPtr->nombre);
		clearScreenFrom(POS_Y_AFTER_HEADER);
		headerRegistro("NOMBRE ACTUALIZADO");
		printf("%-2d\t%-25s\n\n", editorialPtr->ID_editorial, editorialPtr->nombre);
		if(guardarCambios()){
			fseek(fEditorial, getPosDato(&editorialPtr->ID_editorial, PATH_EDITORIAL, sizeof(Editorial), compareEditorialID), SEEK_SET);
			fwrite(editorialPtr, sizeof(Editorial), 1, fEditorial);
		}
	} else{
		aviso("NO EXISTE ESA EDITORIAL", RED, WHITE);
		cancelar();
	}
	tecla();
	fclose(fEditorial);
}

/** @brief Agrega un nuevo autor a la base de datos de autores o recupera un autor existente.
 * Esta función permite al usuario agregar un nuevo autor a la base de datos de autores o recuperar un autor existente si ya se encuentra en la base de datos.
 * El usuario ingresa el nombre completo del autor, y se busca si ya existe en la base de datos. Si existe, se recupera ese autor. Si no existe, se agrega uno nuevo.
 *
 * @return El ID del autor agregado o recuperado.
 */
size_t altaAutor(){
	FILE* fAutor = fopen(PATH_AUTOR, "r+b");
	Autor autor;

	clearScreenFrom(POS_Y_AFTER_HEADER);
	autor.ID_autor = getCantDatos(PATH_AUTOR, sizeof(Autor)) + 1; // Asigna un ID de autor único y consecutivo al último registrado.
	leerString("Autor: ", autor.nombreCompleto);

	Autor *autorPtr = getDato(&autor.nombreCompleto, PATH_AUTOR, sizeof(Autor), compareAutorNombre); // Busca el autor en la base de datos.

	if(existeDato(autorPtr)){ // Si el autor ya existe en la base de datos, lo recupera.
		autor = *autorPtr;
	} else{ // Si el autor no existe en la base de datos, lo escribe al final del archivo.
		fseek(fAutor, 0L, SEEK_END);
		fwrite(&autor, sizeof(autor), 1, fAutor);
	}

	fclose(fAutor);

	return autor.ID_autor; // Devuelve el ID del autor agregado o recuperado.
}

/**@brief Esta función imprime una lista de autores en la pantalla, presentando información relevante sobre cada autor.
 * Permite al usuario seleccionar una opción de autor resaltando la opción actual.
 *
 * @param data Un puntero a un arreglo de estructuras Autor que contiene los datos de los autores.
 * @param y La posición vertical inicial en la que se mostrará la lista de autores en la pantalla.
 * @param opcion La opción seleccionada por el usuario o la opción actual que se resaltará en la lista.
 * @param cantDatos La cantidad total de autores en la lista.
 */
void printAutores(const void *data, int y, int opcion, int cantDatos){
	const Autor *autores =  (const Autor *)data;
	const int ancho = 30;
	gotoxy(0, y);
	headerRegistro("Seleccione un autor");
	int x = getCoordenada().x;
	y = getCoordenada().y;
	for (int i = opcion; i < (opcion + OPCIONES_A_MOSTRAR); ++i){
		if(i == opcion) {
			color(YELLOW, BLACK);
		}else{
			color(BLACK, WHITE);
		}
		gotoxy(x, y++);
		insertarCaracteres(ancho, ' ');
		if(i < cantDatos){
			gotoxy(x, y - 1);
			if(i == -1){
				printf("   Ingreso manual (Esc)");
			} else{
				printf("%-2d\t%-25s\n", autores[i].ID_autor, autores[i].nombreCompleto);
			}
		}
	}
}

/**@brief Esta función muestra una lista de autores disponibles en la base de datos de autores y permite al usuario
 * seleccionar uno de ellos para asignarlo a un libro. Si el usuario decide agregar un nuevo autor que no se encuentra
 * en la base de datos, la función permitirá agregarlo.
 *
 * @return El ID del autor asignado al libro.
 */
size_t asignarAutor(){
	size_t opcion = dataMenu(PATH_AUTOR, sizeof(Autor), POS_Y_AFTER_HEADER, printAutores);
	if(opcion == 0){
		opcion = altaAutor();
	}
	return opcion;
}

void modificarAutor(){
	header("MODIFICAR REGISTRO", "AUTOR", BLUE, WHITE);
	Autor *autorPtr;
	FILE* fAutor = fopen(PATH_AUTOR, "r+b");

	size_t opcion = dataMenu(PATH_AUTOR, sizeof(Autor), POS_Y_AFTER_HEADER, printAutores);
	autorPtr = getDato(&opcion, PATH_AUTOR, sizeof(Autor), compareAutorID);

	if(opcion == 0){
		string nombre;
		leerString("Autor: ", nombre);
		autorPtr = getDato(nombre, PATH_AUTOR, sizeof(Autor), compareAutorNombre);
		clearScreenFrom(POS_Y_AFTER_HEADER);
	}
	if(existeDato(autorPtr)){
		leerString("Ingrese el nuevo nombre: ", autorPtr->nombreCompleto);
		clearScreenFrom(POS_Y_AFTER_HEADER);
		headerRegistro("NOMBRE ACTUALIZADO");
		printf("%-2d\t%-25s\n\n", autorPtr->ID_autor, autorPtr->nombreCompleto);
		if(guardarCambios()){
			fseek(fAutor, getPosDato(&autorPtr->ID_autor, PATH_AUTOR, sizeof(Autor), compareAutorID), SEEK_SET);
			fwrite(autorPtr, sizeof(Autor), 1, fAutor);
		}
	} else{
		aviso("NO EXISTE ESA EDITORIAL", RED, WHITE);
		cancelar();
	}
	tecla();
	fclose(fAutor);
}

boolean compareAutorID(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Autor *)data)->ID_autor;
}

boolean compareAutorNombre(const void *searchValue, const void *data) {
	return sonIguales((char *)searchValue, ((Autor *)data)->nombreCompleto, true);
}

boolean compareEditorialNombre(const void *searchValue, const void *data) {
	return sonIguales((char *)searchValue, ((Editorial *)data)->nombre, true);
}

boolean compareEditorialID(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Editorial *)data)->ID_editorial;
}

boolean compareGeneroNombre(const void *searchValue, const void *data) {
	return sonIguales((char *)searchValue, ((Genero *)data)->nombre, true);
}

boolean compareLibroISBN(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Libro *)data)->ISBN;
}

boolean compareGeneroID(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Genero *)data)->ID_genero;
}

boolean compareLibroID(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Libro *)data)->ID_libro;
}