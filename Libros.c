#include "Headers/Libros.h"

void altaLibro(){
	header("ALTA DE REGISTRO", "LIBROS");
	cargarDatos();
	listAllLibros();

	tecla();
}

void bajaLibro(){

}

void cargarDatos() {
	FILE* fLibro;
	Libro l;

	l.ID_libro = getCantLibros();
	l.ID_autor = 10; // Cambiar.
	l.ID_genero = 15; // Cambiar.
	l.ID_editorial = 20; // Cambiar.
	l.stock = 1; // Cambiar.

	printf("ISBN: ");
	l.ISBN = capturaCaracter(13, true);
	leerString("\nTitulo: ", l.titulo);

	fLibro = fopen(PATH_LIBRO, "r+b");
	fseek(fLibro,0L,SEEK_END);
	fwrite(&l, sizeof(l), 1, fLibro);
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
	Libro l;
	int i = 0;
	fseek(fLibro, 0L, SEEK_SET);
	fread(&l, sizeof(l), 1, fLibro);
	while(!feof(fLibro)){
		libros[i] = l;
		fread(&l, sizeof(l), 1, fLibro);
		i++;
	}
	fclose(fLibro);
}

void listLibros(Libro libros[], int cantLibros){
	printf("\nId Libro\tId Autor\tId Genero\tId Editorial\tISBN\tTitulo\tStock\n\n");
	for (int i = 0; i < cantLibros; i++) {
		mostrarLibro(libros[i]);
	}
}

void listAllLibros() {
	int cantLibros = getCantLibros() - 1;
	Libro libros[cantLibros];
	getLibros(libros);

	printf("\nId Libro\tId Autor\tId Genero\tId Editorial\tISBN\tTitulo\tStock\n\n");
	for (int i = 0; i < cantLibros; i++) {
		mostrarLibro(libros[i]);
	}
}

void mostrarLibro(Libro l){
	printf("%d\t%d\t%d\t%d\t%lld\t%s\t%d\n", l.ID_libro, l.ID_autor, l.ID_genero, l.ID_editorial, l.ISBN, l.titulo, l.stock);
}