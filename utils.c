int leerEntero(string mensaje) {
/* Muestra el mensaje al usuario, lee un int y lo retorna */

	int a;
	printf("%s", mensaje);
	fflush(stdin);
	scanf("%d", &a);
	return a;
}

float leerFloat(string mensaje) {
/* Muestra el mensaje al usuario, lee un float y lo retorna */

	float a;
	printf("%s", mensaje);
	fflush(stdin);
	scanf("%f", &a);
	return a;
}

char leerCaracter(string mensaje) {
/* Muestra el mensaje al usuario, lee un char y lo retorna */

	char a;
	printf("%s", mensaje);
	fflush(stdin);
	scanf("%c", &a);
	return a;
}

int leerEnteroEntre(int valorMin, int valorMax, string mensaje) {
/* Muestra el mensaje al usuario, lee ints mientras �stos est�n
fuera del rango [valorMin, valorMax] informando al usuario de
su error. Cuando tenga un int v�lido, lo retorna */

	int a = leerEntero(mensaje);
	while (a < valorMin || a > valorMax) {
		printf("[ERROR] El valor debe estar comprendido en un rango de %d a %d.\n", valorMin, valorMax);
		a = leerEntero(mensaje);
	}
	return a;
}

float leerFloatEntre(float valorMin, float valorMax, string mensaje) {
/* Muestra el mensaje al usuario, lee floats mientras �stos est�n
fuera del rango [valorMin, valorMax] informando al usuario de
su error. Cuando tenga un float v�lido, lo retorna */

	float a = leerFloat(mensaje);
	while (a < valorMin || a > valorMax) {
		printf("[ERROR] El valor debe estar comprendido en un rango de %.2f a %.2f.\n", valorMin, valorMax);
		a = leerFloat(mensaje);
	}
	return a;
}

void leerString(string mensaje, string str) {
/* Muestra el mensaje al usuario y luego lee un
string por referencia usando la funci�n 'gets()' */

	printf("%s", mensaje);
	fflush(stdin);
	gets(str);
}

void leerStringEntre(int minLength, int maxLength, string mensaje, string str) {
/* Muestra el mensaje al usuario y luego lee una
string por referencia usando la funci�n 'gets()' mientras
su longitud no est� dentro del rango [minLength, maxLength] */

	leerString(mensaje, str);
	while (strlen(str) > maxLength || strlen(str) < minLength) {
		printf("[ERROR] %s", mensaje);
		gets(str);
	}
}

void leerVectorDeEnteros(string mensaje, int vec[], int cant) {
/* Muestra el mensaje al usuario y lee 'cant' enteros,
aloj�ndolos en cada posici�n de 'vec' */

	for (int i = 0; i < cant; i++) {
		printf("[%d] ", i);
		vec[i] = leerEntero(mensaje);
	}
}

void leerVectorDeFloats(string mensaje, float vec[], int cant) {
/* Muestra el mensaje al usuario y lee 'cant' floats,
aloj�ndolos en cada posici�n de 'vec' */

	for (int i = 0; i < cant; i++) {
		printf("[%d] ", i);
		vec[i] = leerFloat(mensaje);
	}
}

void leerVectorDeCaracteres(string mensaje, char vec[], int cant) {
/* Muestra el mensaje al usuario y lee 'cant' caracteres,
aloj�ndolos en cada posici�n de 'vec' */

	for (int i = 0; i < cant; i++) {
		printf("[%d] ", i);
		fflush(stdin);
		vec[i] = leerCaracter(mensaje);
	}
}

void leerVectorDeEnterosEntre(int valorMin, int valorMax, string mensaje, int vec[], int cant) {
/* Muestra el mensaje al usuario y lee 'cant' enteros, aloj�ndolos en cada posici�n de 'vec' siempre
que �stos est�n dentro del rango [valorMin, valorMax] */

	for (int i = 0; i < cant; i++) {
		printf("[%d] ", i);
		vec[i] = leerEntero(mensaje);
		while (vec[i] < valorMin || vec[i] > valorMax) {
			printf("[ERROR] El valor debe estar comprendido en un rango de %d a %d.\n", valorMin, valorMax);
			printf("[%d] ", i);
			vec[i] = leerEntero(mensaje);
		}
	}
}

void leerVectorDeFloatsEntre(float valorMin, float valorMax, string mensaje, float vec[], int cant) {
/* Muestra el mensaje al usuario y lee 'cant' floats,
aloj�ndolos en cada posici�n de 'vec' siempre
que �stos est�n dentro del rango [valorMin, valorMax] */

	for (int i = 0; i < cant; i++) {
		printf("[%d] ", i);
		vec[i] = leerFloat(mensaje);
		while (vec[i] < valorMin || vec[i] > valorMax) {
			printf("[ERROR] El valor debe estar comprendido en un rango de %.2f a %.2f.\n", valorMin, valorMax);
			printf("[%d] ", i);
			vec[i] = leerFloat(mensaje);
		}
	}
}

void mostrarVectorDeEnteros(int vec[], int cant) {
/* Muestra el contenido de 'vec' en renglones separados,
numerando desde cero cada uno */

	for (int i = 0; i < cant; i++) {
		printf("\n[%d]: %d", i, vec[i]);
	}
}

void mostrarVectorDeFloats(float vec[], int cant) {
/* Muestra el contenido de 'vec' en renglones separados,
numerando desde cero cada uno */

	for (int i = 0; i < cant; i++) {
		printf("\n[%d]: %.2f", i, vec[i]);
	}
}

void mostrarVectorDeCaracteres(char vec[], int cant) {
/* Muestra el contenido de 'vec' en renglones separados,
numerando desde cero cada uno */

	for (int i = 0; i < cant; i++) {
		printf("\n[%d]: %c", i, vec[i]);
	}
}

int generarNumAleatorio(int valorMin, int valorMax) {
	//srand(time(NULL));
	return (valorMin + (rand() % (valorMax - valorMin + 1)));
}

int sonIguales(string texto, string texto2) {
	return strcmp(texto, texto2) == 0;
}

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

bool confirmaUsuario(string mensaje) {
/* Muestra el mensaje al usuario junto a la leyenda "[S/N]" que
representa "Si" o "No". Lee chars mientras �stos no sean los
previstos ('S' o 'N', incluyendo min�sculas) informando al
    usuario de su error. Retorna si el usuario seleccion� que s�. */

	char a;
	printf("%s[S/N]: ", mensaje);
	fflush(stdin);
	scanf("%c", &a);
	while (toupper(a) != 'S' && toupper(a) != 'N') {
		fflush(stdin);
		printf("[ERROR] %s[S/N]: ", mensaje);
		scanf("%c", &a);
	}
	return toupper(a) == 'S';
}


void bubbleSortAsc(int numeros[], int cant) {
	for (int i = 0; i < cant - 1; i++) {
		for (int j = 0; j < cant - i - 1; j++) {
			if (numeros[j] > numeros[j + 1]) {
				swap(&numeros[j], &numeros[j + 1]);
			}
		}
	}
}

void bubbleSortDesc(int numeros[], int cant) {
	for (int i = 0; i < cant - 1; i++) {
		for (int j = 0; j < cant - i - 1; j++) {
			if (numeros[j] < numeros[j + 1]) {
				swap(&numeros[j], &numeros[j + 1]);
			}
		}
	}
}

int buscarLineal(int vec[], int cant, int valorB) {
	int i = cant - 1;
	while (i >= 0 && vec[i] != valorB) {
		i--;
	}
	return i;
}

int buscarBinario(int vec[], int min, int max, int valorB) {
// El vector debe estar ordenado

	while (min <= max) {
		int med = (min + max) / 2;
		if (vec[med] == valorB) {
			return med;
		}

		if (vec[med] > valorB) {
			max = med - 1;
		} else {
			min = med + 1;
		}
	}
	return -1;
}

void leerMatrizDeEnteros(string mensaje, int f, int c, int mat[f][c]) {
/* Muestra el mensaje al usuario y lee 'f * c' enteros,
aloj�ndolos en cada posici�n de 'mat' */

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			printf("[%d] [%d] ", i, j);
			mat[i][j] = leerEntero(mensaje);
		}
	}
}

void leerMatrizDeFloats(string mensaje, int f, int c, float mat[f][c]) {
/* Muestra el mensaje al usuario y lee 'f * c' floats,
aloj�ndolos en cada posici�n de 'mat' */

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			printf("[%d] [%d] ", i, j);
			mat[i][j] = leerFloat(mensaje);
		}
	}
}

void leerMatrizDeCaracteres(string mensaje, int f, int c, char mat[f][c]) {
/* Muestra el mensaje al usuario y lee 'f * c' chars,
aloj�ndolos en cada posici�n de 'mat' */

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			printf("[%d] [%d] ", i, j);
			mat[i][j] = leerCaracter(mensaje);
		}
	}
}

void mostrarMatrizDeEnteros(int f, int c, int mat[f][c]) {
/* Muestra el contenido de 'mat' en forma de matriz,
anteponiendo a cada valor los �ndices [f][c]
Ejemplo:
[0][0] = 18     [0][1] = 52     [0][2] = 33
[1][0] = 47     [1][1] = 29     [1][2] = 82 */

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			printf("[%d] [%d]: %d\t", i, j, mat[i][j]);
		}
		printf("\n");
	}
}

void mostrarMatrizDeFloats(int f, int c, float mat[f][c]) {
/* Muestra el contenido de 'mat' en forma de matriz,
anteponiendo a cada valor los �ndices [f][c]
Ejemplo:
[0][0] = 18.2     [0][1] = 52.3     [0][2] = 33.0
[1][0] = 47.5     [1][1] = 29.7     [1][2] = 82.9 */

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			printf("[%d] [%d]: %.2f\t", i, j, mat[i][j]);
		}
		printf("\n");
	}
}

void mostrarMatrizDeCaracteres(int f, int c, char mat[f][c]) {
/* Muestra el contenido de 'mat' en forma de matriz,
anteponiendo a cada valor los �ndices [f][c]
Ejemplo:
[0][0] = C     [0][1] = A     [0][2] = L
[1][0] = E     [1][1] = M     [1][2] = O */

	for (int i = 0; i < f; i++) {
		for (int j = 0; j < c; j++) {
			printf("[%d] [%d]: %c\t", i, j, mat[i][j]);
		}
		printf("\n");
	}
}

void retardo(float seg) {
	printf("CARGANDO");
	for (int i = 0; i < 3; i++) {
		Sleep(seg * 1000);
		printf(".");
	}
	Sleep(0.1 * 1000);
	printf("\n");
}

void cargar() {
	retardo(0.5);
	CLEAN();
}

int error(string path) {
	fprintf(stderr, "***NO SE PUDO ABRIR EL ARCHIVO '%s'***\n", path);
	return 1;
}

void tecla(void) {
	printf("\nPresione una tecla para continuar...");
	getch();
}

FILE *abrirArchivo(string path, string tipo) {
	FILE *archivo = fopen(path, tipo);
	retardo(0.7);
	if (existeArchivo(archivo)) {
		printf("***ARCHIVO '%s' ABIERTO CORRECTAMENTE***\n", path);
	} else {
		exit(error(path));
	}

	return archivo;
}

FILE *abrirArchivoBinario(string path, string tipo) {
	FILE *archivo = fopen(path, tipo);
	retardo(0.7);
	if (existeArchivo(archivo)) {
		printf("***ARCHIVO '%s' ABIERTO CORRECTAMENTE***\n", path);
	} else {
		archivo = fopen(path, "w+b");
		printf("***ARCHIVO INEXISTENTE '%s', SE HA CREADO CORRECTAMENTE***");
	}

	return archivo;
}

void cerrarArchivo(FILE *pArch, char path[]) {
	int result = fclose(pArch);
	if (!result) {
		printf("***ARCHIVO '%s' CERRADO CORRECTAMENTE***\n", path);
	} else {
		printf("***NO SE PUDO CERRAR EL ARCHIVO '%s'***\n", path);
	}
}

int existeArchivo(FILE *pArch) {
	return pArch != NULL;
}

void agregarTXT(string archiveName) {
	strcat(archiveName, ".txt");
}

void insertarEnter(int x) {
	for (int i = 0; i < x; i++) {
		printf("\n");
	}
}


void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

void color(int Background, int Texto) {
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	int New_Color = Texto + (Background * 16);
	SetConsoleTextAttribute(Console, New_Color);
}

int wherex() {
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi)) {
		return cbsi.dwCursorPosition.X + 1;
	}
	return -1;
}

int wherey() {
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi)) {
		return cbsi.dwCursorPosition.Y;
	}
	return -1;
}

void lineaHorizontal(int largo, int cod) {
	largo -= 2;
	char borde[6] = {SUPERIOR_IZQ, SUPERIOR_DER, MEDIO_IZQ, MEDIO_DER, INFERIOR_IZQ, INFERIOR_DER};
	printf("%c", borde[cod]);
	for (int j = 0; j < largo; j++)
		printf("%c", LINEA_MEDIO);
	printf("%c", borde[cod + 1]);
}

void lineaHorizontalEn(Coordenada xy, int largo, int cod){
	gotoxy(xy.x, xy.y);
	lineaHorizontal(largo, cod);
}

void lineaVertical(int largo){
	Coordenada xy = getCoordenada();
	for(int i = 0; i < largo; i++){
		gotoxy(xy.x, xy.y);
		printf("%c", LINEA_VERTICAL);
		xy.y++;
	}
}

void lineaVerticalEn(Coordenada xy, int largo){
	gotoxy(xy.x, xy.y);
	lineaVertical(largo);
}

Coordenada getCoordenada() {
	Coordenada xy;
	xy.x = wherex()-1;
	xy.y = wherey();
	return xy;
}

void recuadroSimple(int alto, int ancho) {
	Coordenada xy;
	alto = (alto - 3) / 2;

	//Genera la linea horizontal superior en la posicion actual (La cual tambien obtiene y se guarda en una variable)
	xy = getCoordenada();
	lineaHorizontalEn(xy, ancho, 0);

	//Ajusta la posicion y genera los laterales superiores
	xy.y++;
	lineaVerticalEn(xy, alto);
	xy.x += ancho-1;
	lineaVerticalEn(xy, alto);

	//Ajusta la posicion y genera la linea horizontal del medio
	xy.x -= ancho - 1;
	xy.y += alto;
	lineaHorizontalEn(xy, ancho, 2);

	//Ajusta la posicion y genera los laterales inferiores
	xy.y++;
	lineaVerticalEn(xy, alto);
	xy.x += ancho - 1;
	lineaVerticalEn(xy, alto);

	//Ajusta la posicion y genera la linea horizontal inferior
	xy.x -= ancho - 1;
	xy.y += alto;
	lineaHorizontalEn(xy, ancho, 4);
}

void _setcursortype(int cur_t) {
	CONSOLE_CURSOR_INFO ci;

	switch (cur_t) {
		case _NOCURSOR://     (turns off the cursor)
			ci.bVisible = FALSE;
			ci.dwSize = 1;
			break;

		case _SOLIDCURSOR://  (solid block cursor)
			ci.bVisible = TRUE;
			ci.dwSize = 100;
			break;

		default:
		case _NORMALCURSOR: // (normal underscore cursor)
			ci.bVisible = TRUE;
			ci.dwSize = 50;
			break;
	}
}
