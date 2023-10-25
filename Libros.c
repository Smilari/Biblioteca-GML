#include "Headers/Libros.h"

void altaLibro(){
	header("ALTA DE REGISTRO", "LIBROS");
	cargarDatos();
	tecla();
}

void bajaLibro(){
	header("BAJA DE REGISTRO", "LIBROS");
	printf("ISBN: ");
	long long ISBN = capturaCaracter(13, false);
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
	int cantLibros = getCantLibros() - 1;
	Libro libros[cantLibros];

	getDatos(libros, sizeof(Libro), cantLibros, PATH_LIBRO);
	listLibros(libros, cantLibros);
	tecla();
}

void consultarLibro(){
	header("CONSULTAR REGISTRO", "LIBROS");
	printf("ISBN: ");
	long long ISBN = capturaCaracter(13, false);
	insertarLineas(2);
	if(existeLibro(ISBN)){
		lineaDeColor(YELLOW, BLACK);
		printf("Id\tTitulo\t\t\t\tStock\tISBN\n\n");
		color(BLACK, WHITE);
		mostrarLibro(getLibro(ISBN));
	} else{
		aviso("NO EXISTE ESE LIBRO", RED, WHITE);
		cancelar();
	}
	tecla();
}

void cargarDatos() {
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro libro;

	libro.ID_libro = getCantLibros();
	libro.ID_autor = 10; // Cambiar.
	libro.ID_genero = 15; // Cambiar.
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
		libro = getLibro(libro.ISBN);
		libro.stock++;
		fseek(fLibro, getPosLibro(libro.ISBN), SEEK_SET);
	}

	if(guardarCambios()){
		fwrite(&libro, sizeof(libro), 1, fLibro);
	}
	fclose(fLibro);
}

int getCantLibros(){
	FILE* fLibro = fopen(PATH_LIBRO, "rb");
	fseek(fLibro,0L,SEEK_END);
	int cantLibros = (ftell(fLibro) / sizeof(Libro)) + 1;
	fclose(fLibro);
	return cantLibros; // Determina la posición del último libro agregado basándose en la última posición del puntero de archivo.
}

void getLibros(Libro libros[]){
	FILE* fLibro = fopen(PATH_LIBRO, "rb");
	Libro libro;
	int i = 0;
	fseek(fLibro, 0L, SEEK_SET);
	fread(&libro, sizeof(libro), 1, fLibro);
	while(!feof(fLibro)){
		libros[i] = libro;
		fread(&libro, sizeof(libro), 1, fLibro);
		i++;
	}
	fclose(fLibro);
}

void getDatos(void *data, size_t data_size, size_t num_items, const char *path) {
	FILE* file = fopen(path, "rb");
	fread(data, data_size, num_items, file);
	fclose(file);
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

int getPosLibro(long long ISBN){
	FILE* fLibro = fopen(PATH_LIBRO, "rb");
	Libro libro;
	int pos = -1;
	fseek(fLibro, 0L, SEEK_SET);
	while(fread(&libro, sizeof(libro), 1, fLibro)){
		if(libro.ISBN == ISBN){
			pos = ftell(fLibro) - sizeof(Libro);
		}
	}
	fclose(fLibro);
	return pos; //Devuelve la posición dentro del archivo del libro buscado, y devuelve -1 si no lo encuentra.
}

Libro getLibro(long long ISBN){
	FILE* fLibro = fopen(PATH_LIBRO, "rb");
	Libro libro = {0, 0, 0, 0, 0, "NULL", 0, false };
	fseek(fLibro, getPosLibro(ISBN), SEEK_SET);
	if(getPosLibro(ISBN) != -1){
		fread(&libro, sizeof(Libro), 1, fLibro);
	}
	fclose(fLibro);
	return libro;
}

boolean existeLibro(long long ISBN){
	boolean estado = true;
	Libro libro = getLibro(ISBN);
	if(sonIguales(libro.titulo, "NULL")){
		estado = false;
	}
	return estado;
}

void borrarLibro (long long ISBN){
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro libro = getLibro(ISBN);
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

void altaGenero(){

}