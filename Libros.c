#include "Headers/Libros.h"

void altaLibro(){
	header("ALTA DE REGISTRO", "LIBROS");
	cargarDatos();
	Libro libros[5];
	getLibros(libros);
	//listAllLibros();
	tecla();
}

void cargarDatos() {
	FILE* fLibro = fopen(PATH_LIBRO, "r+b");
	Libro l;

	fseek(fLibro,0,SEEK_END);
	l.ID_libro = (ftell(fLibro) / sizeof(Libro)) + 1; // Calcula el ID del próximo libro a agregar al archivo basándose en la última posición del puntero de archivo.
	fseek(fLibro,0,SEEK_SET);
	l.ID_autor = 10; // Cambiar.
	l.ID_genero = 15; // Cambiar.
	l.ID_editorial = 20; // Cambiar.
	printf("ISBN: ");
	l.ISBN = capturaCaracter(13, 1);
	leerString("\nTitulo: ", l.titulo);
	l.stock = 1; // Cambiar.
	fwrite(&l, sizeof(l), 1, fLibro);
	fclose(fLibro);
}

int getLibros(Libro libros[]){
	FILE* fLibro = fopen(PATH_LIBRO, "rb");
	Libro l;
	int i = 0;
	fseek(fLibro, 0L, SEEK_SET);
	fread(&l, sizeof(l), 1, fLibro);
	while(!feof(fLibro)){
		libros[i] = l;
		fread(&l, sizeof(l), 1, fLibro);
		i++;
	}
	mostrarLibro(libros[0]);
	fclose(fLibro);
	return i;
}

void listLibros(Libro libros[], int cantLibros){
	printf("\nId Libro\tId Autor\tId Genero\tId Editorial\tISBN\tTitulo\tStock\n\n");
	for (int i = 0; i < cantLibros; i++) {
		mostrarLibro(libros[i]);
	}
}

void listAllLibros() {
	Libro libros[] = {};
	int cantLibros = getLibros(libros);

	printf("\nId Libro\tId Autor\tId Genero\tId Editorial\tISBN\tTitulo\tStock\n\n");
	for (int i = 0; i < cantLibros; i++) {
		mostrarLibro(libros[i]);
	}
}

void mostrarLibro(Libro l){
	printf("%d\t%d\t%d\t%d\t%lld\t%s\t%d\n", l.ID_libro, l.ID_autor, l.ID_genero, l.ID_editorial, l.ISBN, l.titulo, l.stock);
}