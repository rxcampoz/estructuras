/*
 * ARCHIVO:
 *      generic.h
 *
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA Generic
 *
 * DEPENDENCIAS:
 *		stdio.h Definici�n de Tipo de Dato FILE
 * MODIFICACIONES:
 *		2006/11/23 (M. Loor):	Versi�n inicial
 *		2007/03/20 (V. Mac�as): Cambio para incluir mas detalles en los comentarios
 *             
 */
#include <stdio.h>
#include <stdlib.h>
#include "generico.h"
void Generic_Delete(Generic *G){
	free(*G);
	*G = NULL;
}

void Generic_Interchange(Generic *G, Generic *G2){
	Generic tmp;
	tmp = *G;
	*G = *G2;
	*G2 = tmp;
}
