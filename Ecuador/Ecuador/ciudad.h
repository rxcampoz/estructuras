#ifndef CIUDAD_H
#define CIUDAD_H


/*********************************************************************************
**																				**
**									CONSTANTES									**
**																				**
**********************************************************************************/

#define CODIGO 10
#define NOMBRE 50

/*********************************************************************************
**																				**
**								TDA												**
**																				**
**********************************************************************************/
typedef struct{
	char cod[CODIGO];
	char nombre[NOMBRE];
}Ciudad;

/*
**FUNCION: 
**DESCRIPCION:
**
*/
Ciudad *Ciudad_Crear(char *cod, char *nom);
/**/

Ciudad *Ciudad_Leer_Archivo(FILE *F);

char *Get_Codigo(Ciudad *C);
char *Get_nombre(Ciudad *C);

int Ciudad_cmpXNombre(Ciudad *a,Ciudad *B);


char *Ciudad_GetNombre(Ciudad *C);
void Ciudad_Imprimir(Ciudad *C);
#endif
