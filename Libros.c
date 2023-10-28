#include "Headers/Libros.h"

/** @brief Interfaz para registrar un nuevo libro en la base de datos.
	Esta función muestra una interfaz para ingresar datos de un nuevo libro en la base de datos de libros.
	Despliega un encabezado "ALTA DE REGISTRO" y "LIBROS", y luego permite al usuario cargar los datos del libro. */

void altaLibro(){
	header("ALTA DE REGISTRO", "LIBROS");
	cargarDatos();
	tecla();
}

/** @brief Interfaz para dar de baja un libro de la base de datos.
	Esta función muestra una interfaz para buscar y dar de baja un libro de la base de datos de libros.
	Despliega un encabezado "BAJA DE REGISTRO" y "LIBROS", y solicita al usuario que ingrese el ISBN del libro a dar de baja.
	Luego, busca el libro en la base de datos y, si se encuentra, procede a eliminarlo (lógicamente).
	Si el libro no existe, muestra un aviso de que el libro no se encontró. */

void bajaLibro(){
	header("BAJA DE REGISTRO", "LIBROS");
	printf("ISBN: ");
	size_t ISBN = capturaCaracter(13, false);
	Libro *libroPtr = getDato(&ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);

	clearScreenFrom(POS_Y_AFTER_HEADER); // Limpia la pantalla después del encabezado.

	if(existeDato(libroPtr)){
		borrarLibro(ISBN);
	} else{
		aviso("NO EXISTE ESE LIBRO", RED, WHITE);
		cancelar();
	}
	tecla();
}

void modificarLibro(){
	header("MODIFICAR REGISTRO", "LIBROS");
	tecla();
}

/** @brief Interfaz para listar todos los registros de libros en la base de datos.
	Esta función muestra una interfaz que lista todos los libros registrados en la base de datos de libros.
	Despliega un encabezado "LISTAR REGISTROS" y "LIBROS", y luego obtiene y muestra todos los libros almacenados. */

void listAllLibros() {
	header("LISTAR REGISTROS", "LIBROS");
	int cantLibros = getCantDatos(PATH_LIBRO, sizeof(Libro));
	Libro libros[cantLibros];

	getDatos(libros, PATH_LIBRO, sizeof(Libro));

	listLibros(libros, cantLibros, false);
	tecla();
}

/** @brief Interfaz para consultar la información de un libro en la base de datos.
	Esta función muestra una interfaz que permite al usuario consultar la información de un libro en la base de datos de libros.
	Despliega un encabezado "CONSULTAR REGISTRO" y "LIBROS", y solicita al usuario que ingrese el ISBN del libro a consultar.
	Luego, busca el libro en la base de datos y, si se encuentra, muestra su información en pantalla.
	Si el libro no existe, muestra un aviso de que el libro no se encontró. */

void consultarLibro(){
	header("CONSULTAR REGISTRO", "LIBROS");
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

/** @brief Interfaz para cargar información de un libro en la base de datos.
	Esta función muestra una interfaz que permite al usuario cargar información sobre un libro en la base de datos de libros.
	Si el libro ya existe en la base de datos (según su ISBN), actualiza el stock. Si no existe, registra un nuevo libro. */

void cargarDatos() {
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro libro;

	libro.ID_libro = getCantDatos(PATH_LIBRO, sizeof(Libro)) + 1; // Asigna un ID de libro único y consecutivo al último registrado.
	libro.stock = 1;

	printf("ISBN: ");
	libro.ISBN = capturaCaracter(13, true);

	Libro *libroPtr = getDato(&libro.ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN); // Busca el libro en la base de datos.

	if(!existeDato(libroPtr)){ // Si el libro no existe, permite la entrada de datos para cargar uno nuevo.
		libro.ID_autor = altaAutor();
		libro.ID_genero = altaGenero();
		libro.ID_editorial = altaEditorial();

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

/** @brief Muestra una lista de libros en la pantalla.
	Esta función muestra una lista de libros en la pantalla, incluyendo su ID, título, stock, ISBN, género, editorial y autor.
	Puede filtrar la lista para incluir o excluir libros con stock igual a cero según el valor de `incluirStockCero`.

	@param libros Un arreglo de libros que se va a listar.
	@param cantLibros La cantidad de libros en el arreglo.
	@param incluirStockCero Un valor booleano que determina si se deben incluir libros con stock igual a cero. */

void listLibros(Libro libros[], int cantLibros, boolean incluirStockCero) {
	insertarLineas(1);
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tTitulo\t\t\t\tStock\tISBN\t\tGenero\t\tEditorial\t\tAutor\n\n");
	color(BLACK, WHITE);
	for (int i = 0; i < cantLibros; i++) {
		if(incluirStockCero || libros[i].stock != 0){
			mostrarLibro(libros[i]);
		}
	}
	insertarLineas(3);
}

/** @brief Muestra la información detallada de un libro en la pantalla.
	Esta función muestra en la pantalla la información detallada de un libro, incluyendo su ID, título, stock, ISBN, género, editorial y autor.
	Para obtener la información de género, editorial y autor, se realizan búsquedas en las bases de datos correspondientes.
	@param libro El libro cuya información se va a mostrar. */

void mostrarLibro(Libro libro){
	size_t id = libro.ID_genero;
	Genero genero = *(Genero*)getDato(&id, PATH_GENERO, sizeof(Genero), compareGeneroID);

	id = libro.ID_editorial;
	Editorial editorial = *(Editorial*)getDato(&id, PATH_EDITORIAL, sizeof(Editorial), compareEditorialID);

	id = libro.ID_autor;
	Autor autor = *(Autor*)getDato(&id, PATH_AUTOR, sizeof(Autor), compareAutorID);

	printf("%d\t%-25s\t%d\t%-13lld\t%-14s\t%-22s\t%s\n", libro.ID_libro, libro.titulo, libro.stock, libro.ISBN, genero.tipo, editorial.nombre, autor.nombreCompleto);
}

/** @brief Reduce el stock de un libro en la base de datos.
	Esta función disminuye el stock de un libro en la base de datos cuando se realiza una operación de "borrado" de una unidad de ese libro.
	Se busca el libro con el ISBN proporcionado y, si tiene stock disponible, se disminuye en una unidad.
	Luego se actualiza la información en la base de datos y se muestra un aviso al usuario.
	@param ISBN El ISBN del libro cuyo stock se va a disminuir. */

void borrarLibro(const size_t ISBN){
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro *libroPtr = getDato(&ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);
	Libro libro = *libroPtr;
	fseek(fLibro, getPosDato(&ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN), SEEK_SET); // Se mueve a la posición del libro en el archivo.

	if(libro.stock > 0){ // Si el libro tiene stock disponible, lo disminuye en 1.
		libro.stock--;
		aviso("STOCK ACTUALIZADO", BLUE, WHITE);
		listLibros(&libro, 1, true);
		if(guardarCambios()){ // Si el usuario confirma guardar los cambios, sobreescribe los datos en el archivo.
			fwrite(&libro, sizeof(Libro), 1, fLibro);
		}
	}else{
		aviso("NO EXISTEN MAS UNIDADES DE ESTE LIBRO", RED, WHITE);
		cancelar();
	}
	fclose(fLibro);
}

/** @brief Agrega un nuevo género a la base de datos de géneros o recupera un género existente.
	Esta función permite al usuario agregar un nuevo género a la base de datos de géneros o recuperar un género existente si ya se encuentra en la base de datos.
	El usuario ingresa el nombre del género, y se busca si ya existe en la base de datos. Si existe, se recupera ese género. Si no existe, se agrega uno nuevo.
	@return El ID del género agregado o recuperado. */

int altaGenero(){
	FILE* fGenero = fopen(PATH_GENERO, "r+b");
	Genero genero;

	genero.ID_genero = getCantDatos(PATH_GENERO, sizeof(Genero)) + 1; // Asigna un ID de género único y consecutivo al último registrado.

	listarGeneros();

	leerString("Genero: ", genero.tipo);

	Genero *generoPtr = getDato(&genero.tipo, PATH_GENERO, sizeof(Genero), compareGeneroTipo);

	if(existeDato(generoPtr)){ // Si el género ya existe en la base de datos, lo recupera.
		genero = *generoPtr;
	} else{ // Si el género no existe en la base de datos, lo escribe al final del archivo.
		fseek(fGenero, 0L, SEEK_END);
		fwrite(&genero, sizeof(genero), 1, fGenero);
	}

	fclose(fGenero);

	return genero.ID_genero; // Devuelve el ID del género agregado o recuperado.
}

/** @brief Muestra una lista de géneros desde la base de datos de géneros.
	Esta función muestra una lista de géneros que se encuentran en la base de datos de géneros. Para cada género, se muestra su ID y tipo (nombre).
	La lista se muestra en la pantalla y es utilizada para que el usuario pueda seleccionar un género al agregar un libro. */

void listarGeneros() {
	int	cantGeneros = getCantDatos(PATH_GENERO, sizeof(Genero));
	Genero generos[cantGeneros];
	getDatos(generos, PATH_GENERO, sizeof(Genero));

	clearScreenFrom(POS_Y_AFTER_HEADER);
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tTipo\t\n\n");
	color(BLACK, WHITE);

	for (int i = 0; i < cantGeneros; i++) {
		printf("%d\t%-25s\n", generos[i].ID_genero, generos[i].tipo);
	}
	insertarLineas(3);
}

/** @brief Agrega una nueva editorial a la base de datos de editoriales o recupera una editorial existente.
	Esta función permite al usuario agregar una nueva editorial a la base de datos de editoriales o recuperar una editorial existente si ya se encuentra en la base de datos.
	El usuario ingresa el nombre de la editorial, y se busca si ya existe en la base de datos. Si existe, se recupera esa editorial. Si no existe, se agrega una nueva.
	@return El ID de la editorial agregada o recuperada. */

int altaEditorial(){
	FILE* fEditorial = fopen(PATH_EDITORIAL, "r+b");
	Editorial editorial;

	editorial.ID_editorial = getCantDatos(PATH_EDITORIAL, sizeof(Editorial)) + 1; // Asigna un ID de editorial único y consecutivo al último registrado.

	listarEditoriales();

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

/** @brief Muestra una lista de editoriales desde la base de datos de editoriales.
	Esta función muestra una lista de editoriales que se encuentran en la base de datos de editoriales. Para cada editorial, se muestra su ID y nombre.
	La lista se muestra en la pantalla y es utilizada para que el usuario pueda seleccionar una editorial al agregar un libro. */

void listarEditoriales() {
	int	cantEditoriales = getCantDatos(PATH_EDITORIAL, sizeof(Editorial));
	Editorial editoriales[cantEditoriales];
	getDatos(editoriales, PATH_EDITORIAL, sizeof(Editorial));

	clearScreenFrom(POS_Y_AFTER_HEADER);
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tNombre\t\n\n");
	color(BLACK, WHITE);

	for (int i = 0; i < cantEditoriales; i++) {
		printf("%d\t%-25s\n", editoriales[i].ID_editorial, editoriales[i].nombre);
	}
	insertarLineas(3);
}

/** @brief Agrega un nuevo autor a la base de datos de autores o recupera un autor existente.
	Esta función permite al usuario agregar un nuevo autor a la base de datos de autores o recuperar un autor existente si ya se encuentra en la base de datos.
	El usuario ingresa el nombre completo del autor, y se busca si ya existe en la base de datos. Si existe, se recupera ese autor. Si no existe, se agrega uno nuevo.
	@return El ID del autor agregado o recuperado. */

int altaAutor(){
	FILE* fAutor = fopen(PATH_AUTOR, "r+b");
	Autor autor;

	autor.ID_autor = getCantDatos(PATH_AUTOR, sizeof(Autor)) + 1; // Asigna un ID de autor único y consecutivo al último registrado.

	listarAutores();

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

/** @brief Muestra una lista de autores desde la base de datos de autores.
 	Esta función muestra una lista de autores que se encuentran en la base de datos de autores. Para cada autor, se muestra su ID y nombre completo.
	La lista se muestra en la pantalla y es utilizada para que el usuario pueda seleccionar un autor al agregar un libro. */

void listarAutores() {
	int	cantAutores = getCantDatos(PATH_AUTOR, sizeof(Autor));
	Autor autores[cantAutores];
	getDatos(autores, PATH_AUTOR, sizeof(Autor));

	clearScreenFrom(POS_Y_AFTER_HEADER);
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tNombre\t\n\n");
	color(BLACK, WHITE);

	for (int i = 0; i < cantAutores; i++) {
		printf("%d\t%-25s\n", autores[i].ID_autor, autores[i].nombreCompleto);
	}
	insertarLineas(3);
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

boolean compareGeneroTipo(const void *searchValue, const void *data) {
	return sonIguales((char *)searchValue, ((Genero *)data)->tipo, true);
}

boolean compareLibroISBN(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Libro *)data)->ISBN;
}

boolean compareGeneroID(const void *searchValue, const void *data) {
	return *(const size_t*) searchValue == ((Genero *)data)->ID_genero;
}