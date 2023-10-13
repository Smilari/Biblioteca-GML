#include "Headers/Archivos.h"

void verificaArchivos(Archivo ar[], int cantArchivos) {
    FILE *pArch;
    stringPath path = "";
    strcat(path, crearPath());
    asignarPath(path, ar, cantArchivos);
	CLEAN();
	t_verificandoArchivos();

	gotoxy(0, 5);
    for(int i = 0; i < cantArchivos; i++){
        pArch = fopen(ar[i].ruta,"rb");
        if (pArch == NULL){
            pArch = fopen(ar[i].ruta,"wb");
            fclose(pArch);
            printf("\n=>%-120s ", ar[i].ruta);
            color(RED,BLACK);
            printf(" CREADO ");
            color(BLACK,WHITE);
        }
        else{
            printf("\n=>%-120s ", ar[i].ruta);
            color(GREEN,BLACK);
            printf(" OK ");
            color(BLACK,WHITE);
        }
    }
	tecla();
}

void asignarPath(stringPath path, Archivo ar[], int cantArchivos) {
    stringPath aux;
    for(int i = 0; i < cantArchivos; i++){
        strcpy(aux, path);
        strcat(aux, ar[i].ruta);
        strcpy(ar[i].ruta, aux);
    }
}

char* crearPath() {
    static stringPath path;
    getcwd(path, sizeof(path));
    path[strlen(path)] = '\\';
    strcat(path, "Archivos\\");
    CreateDirectory(path, NULL);
    return path;
}