#include "Headers/Libros.h"

void altaLibro(){
	header("ALTA DE REGISTRO", "LIBROS");
	cargarDatos();
	tecla();
}

void bajaLibro(){
	header("BAJA DE REGISTRO", "LIBROS");
	printf("ISBN: ");
	size_t ISBN = capturaCaracter(13, false);
	insertarLineas(2);
	if(existeLibro(ISBN)){
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

void listAllLibros() {
	header("LISTAR REGISTROS ", "LIBROS");
	int cantLibros = getCantDatos(PATH_LIBRO, sizeof(Libro));
	Libro libros[cantLibros];

	getDatos(libros, sizeof(Libro), PATH_LIBRO);
	listLibros(libros, cantLibros);
	tecla();
}

void consultarLibro(){
	header("CONSULTAR REGISTRO", "LIBROS");
	printf("ISBN: ");
	size_t ISBN = capturaCaracter(13, false);
	insertarLineas(2);
	if(existeLibro(ISBN)){
		Libro *libroPtr = getDato(ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);
		lineaDeColor(YELLOW, BLACK);
		printf("Id\tTitulo\t\t\t\tStock\tISBN\n\n");
		color(BLACK, WHITE);
		mostrarLibro(*libroPtr);
	} else{
		aviso("NO EXISTE ESE LIBRO", RED, WHITE);
		cancelar();
	}
	tecla();
}

void cargarDatos() {
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro libro;

	libro.ID_libro = getCantDatos(PATH_LIBRO, sizeof(Libro)) + 1;
	libro.ID_autor = 10; // Cambiar.
	altaGenero();
	listarGeneros();
	Genero *generoPtr = (Genero *)getDato(2, PATH_GENERO, sizeof(Genero), compareGeneroID);
	if (generoPtr != NULL){
		Genero g = *generoPtr;
		libro.ID_genero = g.ID_genero;
		printf("id genero: %d\n", libro.ID_genero);
	}
	libro.ID_genero = 15;
	libro.ID_editorial = 20; // Cambiar.
	libro.stock = 1; // Cambiar.

	printf("ISBN: ");
	libro.ISBN = capturaCaracter(13, true);
	if(!existeLibro(libro.ISBN)){
		leerString("\nTitulo: ", libro.titulo);
		fseek(fLibro, 0L, SEEK_END);
	} else{
		insertarLineas(2);
		aviso("REGISTRO ENCONTRADO, SE ACTUALIZO EL STOCK", BLUE, WHITE);
		libro = *(Libro*)getDato(libro.ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);
		libro.stock++;
		fseek(fLibro, getPosLibro(libro.ISBN), SEEK_SET);
	}

	if(guardarCambios()){
		fwrite(&libro, sizeof(libro), 1, fLibro);
	}
	fclose(fLibro);
}

void listLibros(Libro libros[], int cantLibros){
	lineaDeColor(YELLOW, BLACK);
	printf("Id\tTitulo\t\t\t\tStock\tISBN\n\n");
	color(BLACK, WHITE);
	for (int i = 0; i < cantLibros; i++) {
		if(libros[i].stock != 0){
			mostrarLibro(libros[i]);
		}
	}
}

void mostrarLibro(Libro libro){
	printf("%d\t%-25s\t%d\t%lld\n", libro.ID_libro, libro.titulo, libro.stock, libro.ISBN);
}

int getPosLibro(size_t ISBN){
	int cantLibros = getCantDatos(PATH_LIBRO, sizeof(Libro));
	Libro libros[cantLibros];
	int pos = -1;
	getDatos(libros, sizeof(Libro), PATH_LIBRO);

	for(int i = 0; i < cantLibros; i++){
		if(libros[i].ISBN == ISBN){
			pos = (int) (i * sizeof(Libro));
		}
	}
	return pos; //Devuelve la posición dentro del archivo del libro buscado, y devuelve -1 si no lo encuentra.
}

boolean existeLibro(size_t ISBN){
	boolean estado = true;
	Libro *libroPtr = getDato(ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);
	if(libroPtr == NULL){
		estado = false;
	}
	return estado;
}

void borrarLibro(const size_t ISBN){
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro *libroPtr = getDato(ISBN, PATH_LIBRO, sizeof(Libro), compareLibroISBN);
	Libro libro = *libroPtr;
	fseek(fLibro, getPosLibro(ISBN), SEEK_SET);

	if(libro.stock > 0){
		libro.stock--;
		aviso("STOCK ACTUALIZADO", BLUE, WHITE);
		if(guardarCambios()){
			fwrite(&libro, sizeof(Libro), 1, fLibro);
		}
	}else{
		aviso("NO EXISTEN MAS UNIDADES DE ESTE LIBRO", RED, WHITE);
		cancelar();
	}
	fclose(fLibro);
}

boolean compareLibroISBN(const size_t a, const void *b) {
	return a == ((Libro *)b)->ISBN;
}

void altaGenero(){
	FILE* fGenero = fopen(PATH_GENERO, "r+b");
	Genero genero;
	fseek(fGenero, 0, SEEK_END);
	genero.ID_genero = getCantDatos(PATH_GENERO, sizeof(Genero)) + 1;
	leerString("Ingrese el nombre del genero: ", genero.tipo);
	fwrite(&genero, sizeof(genero), 1, fGenero);
	fclose(fGenero);
}

boolean compareGeneroID(const size_t a, const void *b) {
	return a == ((Genero *)b)->ID_genero;
}

void listarGeneros(){
	int	cantGeneros = getCantDatos(PATH_GENERO, sizeof(Genero));
	Genero generos[cantGeneros];
	getDatos(generos, sizeof(Genero), PATH_GENERO);

	lineaDeColor(YELLOW, BLACK);
	printf("Id\tTipo\t\n\n");
	color(BLACK, WHITE);
	for (int i = 0; i < cantGeneros; i++) {
		printf("%d\t%-25s\n", generos[i].ID_genero, generos[i].tipo);
	}
}