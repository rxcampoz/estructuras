#include "queue.h"

/*
 * ARCHIVO:
 *      queue.h
 * 		�ltima modificaci�n: 2007/03/27 (V. Mac�as)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementaci�n del TDA PILA 
 * DEPENDENCIAS:
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original que define a la pila como una lista
 *		2007/03/27 (V. Mac�as):	Version con nombres en ingl�s.
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
