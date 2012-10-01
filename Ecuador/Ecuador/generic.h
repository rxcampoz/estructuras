#ifndef GENERIC_H
#define GENERIC_H

/*
 * ARCHIVO:
 *      generic.h
 * 		Última modificación: 2007/03/20  (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA Generic
 *
 * DEPENDENCIAS:
 *		stdio.h Definición de Tipo de Dato FILE
 * MODIFICACIONES:
 *		2006/11/23 (M. Loor):	Versión inicial
 *		2007/03/20 (V. Macías): Cambio para incluir mas detalles en los comentarios
 */

#include <stdio.h>

//Definición del tipo de dato Genérico
	typedef void * Generic;

	void Generic_Delete(Generic *G);
	void Generic_Interchange(Generic *G, Generic *G2);

//Definición de funciones generales que se llamaran por callback
	typedef int (*cmpfn)(Generic g1, Generic g2);
	typedef void (*printfn)(Generic g1);
	typedef Generic (*leerfn)(FILE *F);
	typedef Generic (*clavefn)(Generic g1);

#endif