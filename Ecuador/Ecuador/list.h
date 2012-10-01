#ifndef LIST_H
#define LIST_H
/*
 * ARCHIVO:
 *      list.h
 * 		�ltima modificaci�n: 2007/03/20  (V. Mac�as)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA List
 *
 * DEPENDENCIAS:
 *		generic.h Definici�n de Tipo de Dato Gen�rico
 *		node_list.h  Definici�n de nodo para lista
 * MODIFICACIONES:
 *		2006/11/23 (M. Loor):	Versi�n inicial
 *		2007/03/20 (V. Mac�as): Cambio para trabajar con cabecera y final
 */

#include "generic.h"
#include "node_list.h"

//	Definici�n de TDA List
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
//Funci�n para consultar el primer nodo de la lista
NodeList *List_GetHeader(List *L);
//Funci�n para consultar el �ltimo nodo de la lista
NodeList *List_GetLast(List *L);
//Funci�n para consultar el nodo anterior al pasado como par�metro
NodeList * List_GetNodeBefore(List *L, NodeList *p);
//Funci�n para saber si una lista est� vac�a
int List_isEmpty(List *L);
//Funci�n para saber si un nodo espec�fico pertenece a la lista
int List_isNodeExist(List *L, NodeList *p);
//Funci�n para saber la posici�n de un nodo en la lista
int List_GetNodeIndex(List *L, NodeList *p);

/* ---------------------------------------------------- 
 * Funciones para inserci�n de nodos
 * -----------------------------------------------------
 */
//Inserta un nuevo nodo al inicio de la lista
int List_InsertBeforeHeader(List *L, NodeList *pnuevo);
//Inserta un nuevo nodo al final de la lista
int List_InsertAfterLast(List *L, NodeList *pnuevo);
//Inserta un nuevo nodo despu�s de otro nodo espec�fico de la lista
int List_InsertAfterNode(List *L, NodeList *p, NodeList *pnuevo);

/* ---------------------------------------------------- 
 * Funciones para remover nodos
 * -----------------------------------------------------
 */
//Remover nodo inicial
NodeList *List_RemoveHeader(List *L);
//Remover nodo final
NodeList *List_RemoveLast(List *L);
//Remover nodo espec�fico de la lista
int List_RemoveXPos(List *L, NodeList *p);

/*
 * Funcion: List_Search
 * -------------------------------
 * Modo de uso:
 * NodeList *node;
 * List *L;
 * Generic G;
 * node = List_Search(L,G,funcion_comparacion);
 * Funci�n que retorna el nodo cuyo contenido concuerde
 * con el enviado como par�metro. Retorna NULL si ning�n
 * elemento de la lista coincide seg�n la funci�n de
 * comparaci�n.
 */
NodeList *List_Search(List *L, Generic G, cmpfn f);

/*
 * Funcion: List_Print
 * -------------------------------
 * Modo de uso:
 * List *L;
 * List_Print(L,funcion_impresion);
 * Funci�n que recorre toda la lista e imprime los
 * campos del contenido que la funci�n de impresi�n
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
 * Funci�n que retorna el nodo de la lista cuya posici�n
 * es la que viene dada por index. Retorna NULL si no hay
 * un nodo en esa posici�n.
 */
NodeList *List_GetNodeXIndex(List *L, int index);

/*
 * Funcion: List_GetSize
 * -------------------------------
 * Modo de uso:
 * List *L;
 * int size;
 * node = List_GetSize(L);
 * Funci�n que retorna el n�mero de elementos que tiene la lista
 */
int List_GetSize(List *L);

/*
 * Funcion: List_SearchAll
 * -------------------------------
 * Modo de uso:
 * List *L, *LNew;
 * Generic G;
 * LNew = List_SearchAll(L,G,funcion_comparacion);
 * Funci�n que retorna una lista nueva que contiene todos los
 * elementos de la lista L que conten�an el dato G seg�n la
 * funci�n de comparaci�n.
 */
List *List_SearchAll(List *L, Generic G, cmpfn f);

/*
 * Funcion: List_InsertInOrder
 * -------------------------------
 * Modo de uso:
 * List *L;
 * NodeList *nuevo;
 * List_InsertInOrder(L,nuevo,funcion_comparacion);
 * Funci�n que inserta un nuevo nodo en la lista, pero de forma
 * ordenada ya sea ascendente o descendente, seg�n la funci�n de
 * comparaci�n.
 */
void List_InsertInOrder(List *L, NodeList *nuevo, cmpfn comp);

/*
 * Funcion: List_Order
 * -------------------------------
 * Modo de uso:
 * List *L;
 * List_Order(L,funcion_comparacion);
 * Funci�n que ordena los elementos de una lista
 */
List * List_Order(List *L, cmpfn comp);

List* List_Copy(List *Lorig);

#endif