#include "generic_int.h"
#include <stdlib.h>


int * Int_Crear(int valor){
	int *nuevo;
	nuevo = malloc(sizeof(int));
	*nuevo = valor;
	return nuevo;
}
void Int_Set(int *p, int valor){
	*p = valor;
}
int Int_Get(int *p){
	return *p;
}
void Int_Print(int *valor){
	printf("%d\n", *valor);
}
int * Int_Leer(void){
	int *nuevo;
	nuevo = Int_Crear(0);

	scanf("%d",nuevo);
	return nuevo;
}
int Int_Comparar(int *v1, int *v2){
	if(*v1 == *v2) return 0;
	else if(*v1 > *v2) return 1;
	else return -1;
}
