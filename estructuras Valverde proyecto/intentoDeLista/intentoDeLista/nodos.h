#ifndef NODOS_H
#define NODOS_H

/*
 * ARCHIVO:
 *      node_list.h
 * 		Última modificación: 2007/03/20  (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA NodeList
 *
 * DEPENDENCIAS:
 *		generic.h Definición de Tipo de Dato Genérico
 * MODIFICACIONES:
 *		2006/11/23 (M. Loor):	Versión inicial
 *		2007/03/20 (V. Macías): Cambio para incluir mas detalles en los comentarios
 */

#include "generico.h"
#include <stdlib.h>

//	Definición de TDA NodeList
typedef struct TNodeList
{
	Generic G;
	struct TNodeList *next;
}NodeList;

/*
 * Funcion: NodeList_New
 * -------------------------------
 * Modo de uso:
 * NodeList *p;
 * p = NodeList_New();
 * Reserva memoria para guardar un nodo, y retorna el puntero
 * a la memoria reservada
 */
NodeList *NodeList_New(Generic G);

/*
 * Funcion: NodeList_Delete
 * -------------------------------
 * Modo de uso:
 * NodeList *p;
 * NodeList_Delete(&p);
 * Libera la memoria apuntada por un puntero a NodeList
 */
void NodeList_Delete (NodeList **p);

/* ---------------------------------------------------- 
 * Funciones para consultar el estado de un nodo
 * -----------------------------------------------------
 */
//Función para consultar el contenido de un nodo
Generic NodeList_GetContent(NodeList *p);
//Función para consultar el puntero al nodo siguiente
NodeList *NodeList_GetNext(NodeList *p);

/* ---------------------------------------------------- 
 * Funciones para modificar el estado de un nodo
 * -----------------------------------------------------
 */
//Cambia el contenido de un nodo
void NodeList_SetContent(NodeList *p, Generic G);
//Cambia el valor del puntero al siguiente nodo
void NodeList_SetNext(NodeList *p, NodeList *next);

#endif
