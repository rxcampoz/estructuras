#ifndef GENERIC_INT_H
#define GENERIC_INT_H

#include "generic.h"

int * Int_Crear(int valor);
int Int_Get(int *p);
void Int_Set(int *p, int valor);
void Int_Print(int *valor);
int* Int_Leer(void);
int Int_Comparar(int *v1, int *v2);

#endif