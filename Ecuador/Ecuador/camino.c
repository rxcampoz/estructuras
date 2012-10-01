#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "camino.h"
Camino *Camino_Leer_Archivo(FILE *F){
	
	Camino *C=malloc(sizeof(Camino));
	char  nom1[100],nom2[100];
	int dis;
	
	
	fscanf(F,"%[^|]|%[^|]|%d\n",nom1,nom2,&dis);
	C=Camino_Crear(nom1,nom2,dis);
	return C;
}

Camino *Camino_Crear(char *nom1,char *nom2,int dis){
	Camino *C=malloc(sizeof(Camino));
	
	strcpy(C->nombre1,nom1);
	strcpy(C->nombre2,nom2);
	C->dis=dis;
	return C;

}

int Camino_CompXV1(Camino *c,char *v1){
	return (strcmp(c->nombre1,v1));

}
int Camino_CompXV2(Camino *c,char *v1){
	return (strcmp(c->nombre2,v1));

}
char *Camino_GetDestino(Camino *c){
	return (c->nombre2);
}