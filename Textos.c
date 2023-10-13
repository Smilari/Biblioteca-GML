#include "Headers/Textos.h"

void t_verificandoArchivos(){
	const string VERIFICANDO_ARCHIVOS = "VERIFICANDO EXISTENCIA DE ARCHIVOS";

	color(WHITE, BLACK);
	for(int i = 1; i < 4; i++){
		gotoxy(0, i);
		insertCaracteres(ANCHO_PANTALLA, ' ');
	}
	gotoxy(posCentrado(VERIFICANDO_ARCHIVOS), 2);
	printf("%s", VERIFICANDO_ARCHIVOS);
	color(BLACK, WHITE);
}

int posCentrado(string str){
	return (ANCHO_PANTALLA - strlen(str))/2;
}