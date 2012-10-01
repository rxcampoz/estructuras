#ifndef CAMINO_H
#define CAMINO_H

/*********************************************************************************
**																				**
**								TDA												**
**																				**
**********************************************************************************/

typedef struct{
	char nombre1[100];
	char nombre2[100];
	int dis;
}Camino;
/*
*FUNCION:Camino *Camino_Crear(char *nom1,char *nom2,int dis);
*DESCRIPCION: Crear un camino
* Uso:Camino_Crear(nom1,nom2,dis);
*/

Camino *Camino_Crear(char *nom1,char *nom2,int dis);
/*
*FUNCION:*Camino_Leer_Archivo(FILE *F);
*DESCRIPCION: Crear un camino que lo lee desde el archivo
* Uso: Camino_Leer_Archivo(F);
*/
Camino *Camino_Leer_Archivo(FILE *F);
/*
*FUNCION:int Camino_CompXV1(Camino *c,char *v1);
*DESCRIPCION: Compra un camino por medio de un vertice
* Uso:Camino_CompXV1(c,v1);
*/
int Camino_CompXV1(Camino *c,char *v1);
/*
*FUNCION:int Camino_CompXV2(Camino *c,char *v1);
*DESCRIPCION: Crear un camino por medio de un vertice
* Uso:Camino_CompXV2(c,v1);
*/
int Camino_CompXV2(Camino *c,char *v1);
/*
*FUNCION:char *Camino_GetDestino(Camino *c);
*DESCRIPCION: Crear un destino
* Uso:Camino_GetDestino(c);
*/
char *Camino_GetDestino(Camino *c);

#endif
