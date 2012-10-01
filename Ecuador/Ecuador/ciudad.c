#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ciudad.h"


Ciudad *Ciudad_Crear(char *cod, char *nom){
	Ciudad *C=malloc(sizeof(Ciudad));
	strcpy(C->cod,cod);
	strcpy(C->nombre,nom);
	return C;
}

char *Get_Codigo(Ciudad *C){
	return C->cod;
}
char *Get_nombre(Ciudad *C){
	return C->nombre;
}

int Ciudad_cmpXNombre(Ciudad *a,Ciudad *B){
	return strcmp(a->nombre,B->nombre);
}

Ciudad *Ciudad_Leer_Archivo(FILE *F){

	Ciudad *C=malloc(sizeof(Ciudad));
	char  cod[50];
	char  or[50];
	
	fscanf(F,"%[^|]|%[^|\n]\n",cod,or);
	C=Ciudad_Crear(cod,or);
	return C;
}

/**/
int Ciudad_CompararXNombre(Ciudad *p1,Ciudad*p2){
	return (strcmp(p1->nombre,p2->nombre));
}
char *Ciudad_GetNombre(Ciudad *C){
	return (C->nombre);

}/**/
void Ciudad_Imprimir(Ciudad *C){
	printf("\n\n\t%s",C->nombre);
}