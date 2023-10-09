/**************************************************************************/
/** @brief Proyecto de Estructura y Base de Datos.                       **/
/** @version Pre-Alpha                                                   **/
/**************************************************************************/

/** CABECERAS EXTERNAS DE FUNCIONES **/

#include "../Headers/utils.h"
#include "../Headers/Archivos.h"

/* DEFINICIONES */
#define PATH_SOCIO "Socio.dat"
#define PATH_LIBRO "Libro.dat"
#define PATH_PRESTAMO "Prestamo.dat"
#define PATH_EDITORIAL "Editorial.dat"
#define PATH_AUTOR "Autor.dat"
#define PATH_GENERO "Genero.dat"


typedef struct{
    string opcion;
} OpcionesMenu;

typedef struct{
    int ID_editorial;
    string nombre;
} Editorial;

typedef struct{
    int ID_genero;
    string tipo;
} Genero;

typedef struct{
    int ID_autor;
    string nombre;
    string apellido;
} Autor;

typedef struct{
    int ID_socio;
    string nombre;
    string apellido;
    int DNI;
    int telefono;
    string direccion;
    string mail;
} Socio;

typedef struct{
    int ID_libro;
    int ID_autor;
    int ID_genero;
    int ID_editorial;
    string ISBN;
    string titulo;
    int stock;
} Libro;

typedef struct{
    int ID_prestamo;
    int ID_libro;
    int ID_socio;
    time_t fecha_adquirido;
    time_t fecha_entregado;
} Prestamo;

/* DEFINICIONES DE METODOS */
void bienvenida();

void listar(FILE *libros)
{
    /*FILE *binario;
    char cad[81];
    if((libros = fopen(nompArch,"r+")) == NULL)
    {
        p("***ERROR***"); exit(-1);
    }
*/


}

int main(){
    Archivo ar[] = {PATH_EDITORIAL, PATH_AUTOR, PATH_GENERO, PATH_LIBRO, PATH_SOCIO, PATH_PRESTAMO};
    OpcionesMenu om[] = {};
    int cantArchivos = sizeof(ar)/MAX_PATH;
    bienvenida();
    verificaArchivos(ar, cantArchivos);
}


void bienvenida() {
}


void recuadro(int pos,int largo){
    int j;
    char borde[7]={218,191,195,180,192,217,179};
    printf("%c",borde[pos]);
    for(j=0;j<largo;j++)
        printf("%c",196);
    printf("%c",borde[pos+1]);
}

void menu(int *opcion, OpcionesMenu m[],int r){
    char tecla;
    int pos_x=27,posicion=1,i,largo=25;
    do
    {
        CLEAN();
        gotoxy(pos_x,1);
        color(BLUE,YELLOW);
        recuadro(0,largo);
        gotoxy(pos_x,2);
        printf("%c%s%c",179,m[0].opcion,179);
        gotoxy(pos_x,3);
        recuadro(2,largo);
        color(BLUE,YELLOW);
        for(i=1;i<r;i++)
        {
            if (posicion>=1 && posicion<=r)
            {
                if (posicion==i)
                {
                    gotoxy(pos_x,i+3);
                    printf("%c",179);
                    color(YELLOW,BLUE);
                    printf("%s",m[i].opcion);
                    color(BLUE,YELLOW);
                    printf("%c",179);
                    color(BLACK,WHITE);
                }
                else
                {
                    gotoxy(pos_x,i+3);
                    color(BLUE,YELLOW);
                    printf("%c%s%c\n",179,m[i].opcion,179);
                }
            }
        }
        gotoxy(pos_x,r+3);
        color(BLUE,YELLOW);
        recuadro(4,largo);
        color(BLACK,WHITE);
        tecla=getch();
        switch (tecla)
        {
            case 80:    posicion++;
                        if (posicion>r-1)
                            posicion=1;
                        break;
            case 72:    posicion--;
                        if (posicion<1)
                            posicion=r-1;
                        break;
            case 13:    if (r-1!=posicion)
                            *opcion=posicion;
                        else
                            *opcion=0;
                        break;
        }
    } while (tecla!=13);
}


/*void submenu(int *menu,OpcionesMenu m[],int r,int y)
{
    char tecla;
    int posicion=1,i;
    gotoxy(0,y);
    color(BLUE,YELLOW);
    printf("                                                                                ");
    gotoxy(0,y);
    printf("%s",m[0].opcion);
    do
    {
        for(i=1;i<r;i++)
        {
            if (posicion>=1 && posicion<=r)
            {
                if (posicion==i)
                {
                    gotoxy(i*11,y);
                    color(YELLOW,BLUE);
                    printf("[%s]",m[i].opcion);
                }
                else
                {
                    gotoxy(i*11,y);
                    color(BLUE,YELLOW);
                    printf(" %s ",m[i].opcion);
                }
            }
        }
        color(BLACK,WHITE);
        printf("\n");
        linea(Largo);
        tecla=getch();
        switch (tecla)
        {
            case 77:    posicion++;
                        if (posicion>r-1)
                            posicion=1;
                        break;
            case 75:    posicion--;
                        if (posicion<1)
                            posicion=r-1;
                        break;
            case 13:    if (r!=posicion)
                            *opcion=posicion;
                        break;
            case 27:    *opcion=0;
                        break;
        }
    } while (tecla!=13 && tecla!=27);
}*/
