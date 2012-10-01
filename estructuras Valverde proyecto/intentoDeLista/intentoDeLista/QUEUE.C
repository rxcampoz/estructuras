#include "queue.h"

/*
 * ARCHIVO:
 *      queue.h
 * 		Última modificación: 2007/03/27 (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementación del TDA PILA 
 * DEPENDENCIAS:
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original que define a la pila como una lista
 *		2007/03/27 (V. Macías):	Version con nombres en inglés.
 */

int Queue_isEmpty(Queue *St){
	return List_isEmpty(St);
}
Queue *Queue_New(){
	return(List_New());
}
void Queue_Push(Queue *St, NodeList *nuevo){
	List_InsertAfterLast(St, nuevo);
}
NodeList *Queue_Pop(Queue *St){
	return List_RemoveHeader(St);
}
void Queue_Delete(Queue **St){
	List_Delete(St);
}
NodeList *Queue_GetFront(Queue *St){
	return List_GetHeader(St);
}

NodeList *Queue_GetLast(Queue *Q){
	return List_GetLast(Q);
}
