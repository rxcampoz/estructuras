#ifndef LIST_H
#define LIST_H
/*
 * ARCHIVO:
 *      list.h
 * 		Última modificación: 2007/03/20  (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA List
 *
 * DEPENDENCIAS:
 *		generic.h Definición de Tipo de Dato Genérico
 *		node_list.h  Definición de nodo para lista
 * MODIFICACIONES:
 *		2006/11/23 (M. Loor):	Versión inicial
 *		2007/03/20 (V. Macías): Cambio para trabajar con cabecera y final
 */

#include "generic.h"
#include "node_list.h"

//	Definición de TDA List
typedef struct {
	NodeList *header;
	NodeList *last;
}List;

/*
 * Funcion: List_New
 * -------------------------------
 * Modo de uso:
 * List *L;
 * L = List_New();
 * Reserva memoria para guardar una Lista, y retorna el puntero
 * a la memoria reservada
 */
List *List_New();

/*
 * Funcion: List_Delete
 * -------------------------------
 * Modo de uso:
 * List *L;
 * List_Delete(&L);
 * Libera la memoria apuntada por un puntero a Lista
 */
void List_Delete(List **L);

/* ---------------------------------------------------- 
 * Funciones para consultar el estado de una lista
 * -----------------------------------------------------
 */
//Función para consultar el primer nodo de la lista
NodeList *List_GetHeader(List *L);
//Función para consultar el último nodo de la lista
NodeList *List_GetLast(List *L);
//Función para consultar el nodo anterior al pasado como parámetro
NodeList * List_GetNodeBefore(List *L, NodeList *p);
//Función para saber si una lista está vacía
int List_isEmpty(List *L);
//Función para saber si un nodo específico pertenece a la lista
int List_isNodeExist(List *L, NodeList *p);
//Función para saber la posición de un nodo en la lista
int List_GetNodeIndex(List *L, NodeList *p);

/* ---------------------------------------------------- 
 * Funciones para inserción de nodos
 * -----------------------------------------------------
 */
//Inserta un nuevo nodo al inicio de la lista
int List_InsertBeforeHeader(List *L, NodeList *pnuevo);
//Inserta un nuevo nodo al final de la lista
int List_InsertAfterLast(List *L, NodeList *pnuevo);
//Inserta un nuevo nodo después de otro nodo específico de la lista
int List_InsertAfterNode(List *L, NodeList *p, NodeList *pnuevo);

/* ---------------------------------------------------- 
 * Funciones para remover nodos
 * -----------------------------------------------------
 */
//Remover nodo inicial
NodeList *List_RemoveHeader(List *L);
//Remover nodo final
NodeList *List_RemoveLast(List *L);
//Remover nodo específico de la lista
int List_RemoveXPos(List *L, NodeList *p);

/*
 * Funcion: List_Search
 * -------------------------------
 * Modo de uso:
 * NodeList *node;
 * List *L;
 * Generic G;
 * node = List_Search(L,G,funcion_comparacion);
 * Función que retorna el nodo cuyo contenido concuerde
 * con el enviado como parámetro. Retorna NULL si ningún
 * elemento de la lista coincide según la función de
 * comparación.
 */
NodeList *List_Search(List *L, Generic G, cmpfn f);

/*
 * Funcion: List_Print
 * -------------------------------
 * Modo de uso:
 * List *L;
 * List_Print(L,funcion_impresion);
 * Función que recorre toda la lista e imprime los
 * campos del contenido que la función de impresión
 * mande a imprimir.
 */
void List_Print(List *L, printfn f);

/*
 * Funcion: List_ReadFile
 * -------------------------------
 * Modo de uso:
 * List *L;
 * char nombre_archivo[MAX_NOM];
 * L = List_ReadFile(nombre_archivo,funcion_lectura_desde_archivo);
 * Función que lee cada línea de un archivo usando la función de
 * lectura y retorna una lista llena con los datos leídos
 */
List *List_ReadFile(char *archivo, leerfn f);

/*
 * Funcion: List_GetNodeXIndex
 * -------------------------------
 * Modo de uso:
 * NodeList *node;
 * List *L;
 * int index;
 * node = List_GetNodeXIndex(L,index);
 * Función que retorna el nodo de la lista cuya posición
 * es la que viene dada por index. Retorna NULL si no hay
 * un nodo en esa posición.
 */
NodeList *List_GetNodeXIndex(List *L, int index);

/*
 * Funcion: List_GetSize
 * -------------------------------
 * Modo de uso:
 * List *L;
 * int size;
 * node = List_GetSize(L);
 * Función que retorna el número de elementos que tiene la lista
 */
int List_GetSize(List *L);

/*
 * Funcion: List_SearchAll
 * -------------------------------
 * Modo de uso:
 * List *L, *LNew;
 * Generic G;
 * LNew = List_SearchAll(L,G,funcion_comparacion);
 * Función que retorna una lista nueva que contiene todos los
 * elementos de la lista L que contenían el dato G según la
 * función de comparación.
 */
List *List_SearchAll(List *L, Generic G, cmpfn f);

/*
 * Funcion: List_InsertInOrder
 * -------------------------------
 * Modo de uso:
 * List *L;
 * NodeList *nuevo;
 * List_InsertInOrder(L,nuevo,funcion_comparacion);
 * Función que inserta un nuevo nodo en la lista, pero de forma
 * ordenada ya sea ascendente o descendente, según la función de
 * comparación.
 */
void List_InsertInOrder(List *L, NodeList *nuevo, cmpfn comp);

/*
 * Funcion: List_Order
 * -------------------------------
 * Modo de uso:
 * List *L;
 * List_Order(L,funcion_comparacion);
 * Función que ordena los elementos de una lista
 */
List * List_Order(List *L, cmpfn comp);

List* List_Copy(List *Lorig);

#endif