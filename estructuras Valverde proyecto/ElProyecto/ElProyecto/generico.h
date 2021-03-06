#ifndef GENERICO_H
#define GENERICO_H

/*
 * ARCHIVO:
 *      generic.h
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA Generic
 *
 * DEPENDENCIAS:
 *		stdio.h Definicion de Tipo de Dato FILE
 */

#include <stdio.h>

//Definicion del tipo de dato Generico
	typedef void * Generic;

	void Generic_Delete(Generic *G);
	void Generic_Interchange(Generic *G, Generic *G2);

//Definicion de funciones generales que se llamaran por callback
	typedef int (*cmpfn)(Generic g1, Generic g2);
	typedef void (*printfn)(Generic g1);
	typedef Generic (*leerfn)(FILE *F);
	typedef Generic (*clavefn)(Generic g1);

	typedef void (*savefn)(FILE *F, Generic G);
	typedef void (*linkfn)(Generic g1, Generic g2);

#endif