#ifndef LIST_H
#define LIST_H
/*
 * ARCHIVO:
 *      list.h
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA List
 *
 * DEPENDENCIAS:
 *		generic.h Definicion de Tipo de Dato Generico
 *		node_list.h  Definicion de nodo para lista
 */

#include "generico.h"
#include "nodos.h"

//	Definicion de TDA List
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
//Funcion para consultar el primer nodo de la lista
NodeList *List_GetHeader(List *L);
//Funcion para consultar el ultimo nodo de la lista
NodeList *List_GetLast(List *L);
//Funcion para consultar el nodo anterior al pasado como parametro
NodeList * List_GetPrevious(List *L, NodeList *p);
//Funcion para saber si una lista esta vacia
int List_isEmpty(List *L);
//Funcion para saber si un nodo especofico pertenece a la lista
int List_NodeExists(List *L, NodeList *p);
//Funcion para saber la posicion de un nodo en la lista
int List_GetNodeIndex(List *L, NodeList *p);
//cuenta las veces q se repite un nodo en una lista 
int List_CountNodeRepeat(List *L, NodeList *p, cmpfn f);

/* ---------------------------------------------------- 
 * Funciones para insercion de nodos
 * -----------------------------------------------------
 */
//Inserta un nuevo nodo al inicio de la lista
int List_InsertHeader(List *L, NodeList *pnuevo);
//Inserta un nuevo nodo al final de la lista
int List_InsertLast(List *L, NodeList *pnuevo);
//Inserta un nuevo nodo despues de otro nodo especifico de la lista
int List_InsertAfterNode(List *L, NodeList *p, NodeList *pnuevo);

/* ---------------------------------------------------- 
 * Funciones para remover nodos
 * -----------------------------------------------------
 */
//Remover nodo inicial
NodeList *List_RemoveHeader(List *L);
//Remover nodo final
NodeList *List_RemoveLast(List *L);
//Remover nodo especifico de la lista
int List_RemoveXPos(List *L, NodeList *p);
//
List * List_RemoveRepeat(List *L, cmpfn f);
/*
 * Funcion: List_Search
 * -------------------------------
 * Modo de uso:
 * NodeList *node;
 * List *L;
 * Generic G;
 * node = List_Search(L,G,funcion_comparacion);
 * Funcion que retorna el nodo cuyo contenido concuerde
 * con el enviado como parametro. Retorna NULL si ningun
 * elemento de la lista coincide segun la funcion de
 * comparacion.
 */
NodeList *List_Find(List *L, Generic G, cmpfn f);

/*
 * Funcion: List_Print
 * -------------------------------
 * Modo de uso:
 * List *L;
 * List_Print(L,funcion_impresion);
 * Funcion que recorre toda la lista e imprime los
 * campos del contenido que la funcion de impresion
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
 * Funci�n que lee cada l�nea de un archivo usando la funci�n de
 * lectura y retorna una lista llena con los datos le�dos
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
 * Funcion que retorna el nodo de la lista cuya posicion
 * es la que viene dada por index. Retorna NULL si no hay
 * un nodo en esa posicion.
 */
/*

*/
void Save_File(char *archivo, List *L, savefn f);

NodeList *List_GetNodeXIndex(List *L, int index);

/*
 * Funcion: List_GetSize
 * -------------------------------
 * Modo de uso:
 * List *L;
 * int size;
 * size = List_GetSize(L);
 * Funcion que retorna el numero de elementos que tiene la lista
 */
int List_GetSize(List *L);


/*
 * Funcion: List_InsertInOrder
 * -------------------------------
 * Modo de uso:
 * List *L;
 * NodeList *nuevo;
 * List_InsertInOrder(L,nuevo,funcion_comparacion);
 * Funcion que inserta un nuevo nodo en la lista, pero de forma
 * ordenada ya sea ascendente o descendente, segun la funcion de
 * comparacion.
 */
void List_InsertInOrder(List *L, NodeList *nuevo, cmpfn comp);

/*
 * Funcion: List_Order
 * -------------------------------
 * Modo de uso:
 * List *L;
 * List_Order(L,funcion_comparacion);
 * Funcion que ordena los elementos de una lista
 */
List * List_Order(List *L, cmpfn comp);
/*
 *Funcion: Funcion_Relacionar2Listas
 *-----------------------------------
 Relaciona dos listas con la particularidad de una relacion de varios a uno
 la primera lista es de uno y la segunda es a varios se envia callback de 
 comparacion y union  
 */
void Funcion_Relacionar2Listas(List *L1, List *L2, cmpfn cmp, linkfn link);
/*
 *Funcion:List_FindAll
 *-----------------------------------
 Retorna una lista de los elementos que coincidan con el parametro enviado
 */
List *List_FindAll(List *L, Generic g, cmpfn cmp);
#endif
