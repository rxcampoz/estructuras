#ifndef QUEUE_H
#define QUEUE_H

/*
 * ARCHIVO:
 *      queue.h
 * 		Última modificación: 2007/03/27 (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA COLA (Queue) 
 * DEPENDENCIAS:
 *		List.h Definición de TDA List, ya que la Queue es una lista
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original que define a la cola como una lista
 *		2007/03/27 (V. Macías):	Version con nombres en inglés.
 */

#include "list.h"

/*-----------------------------------------------------------------------------------------
							TDA COLA (QUEUE)
  -----------------------------------------------------------------------------------------*/

/****************
	NIVEL LÓGICO
 ****************

	Definición
	_____________________________________________________________________________________
	<cola> ::= {<nodo>} + <final>
	_____________________________________________________________________________________


	Creación/Destrucción
		Queue_New()
		Queue_Delete(nombreQueue)

	Comprobación de Estado
		Queue_isEmpty(nombreQueue) : inteano

	Queue_Push y Queue_Pop
		Queue_Push(nombreQueue, nodonuevo) :
		Queue_Pop(nombreQueue) :referencia_nodo
*/


/*
 * Tipo: Queue
 * ---------------
 * Una cola es un conjunto de elementos, donde solo se conocen
 * el primer y el ultimo elemento
 */

typedef List Queue;

/*
 * Funcion: Queue_isEmpty
 * --------------------------
 * Modo de uso:
 * Queue *Q;
 * if(Queue_isEmpty(Q))...
 * Esta operacion recibe una cola y determina si esta o no vacia
 */
int Queue_isEmpty(Queue *St);
/*
 * Funcion: Queue_New
 * --------------------------
 * Modo de uso:
 * Queue *Q;
 * Q = Queue_New()
 * Esta operacion crea una nueva Cola
 */
Queue *Queue_New();
/*
 * Funcion: Queue_Push
 * --------------------------
 * Modo de uso:
 * Queue *Q;
 * NodeList *nuevo;
 * Queue_Push(Q, nuevo);
 * Esta operacion recibe una Cola y aumenta al elemento nuevo
 * al final de la misma
 */
void Queue_Push(Queue *St, NodeList *nuevo);

/*
 * Funcion: Queue_Pop
 * --------------------------
 * Modo de uso:
 * Queue *Q;
 * NodeList *nuevo;
 * nuevo = Queue_Pop(Q)...
 * Esta operacion recibe una Cola y retira de la misma
 * el elemento del inicio, retornandolo
 */
NodeList *Queue_Pop(Queue *St);

/*
 * Funcion: Queue_Delete
 * --------------------------
 * Modo de uso:
 * Queue *Q;
 * Queue_Delete(&Q);
 * Esta operacion recibe una Cola, retira uno a uno
 * los elementos en la misma hasta que quede vacia
 */
void Queue_Delete(Queue **St);
/*
 * Funcion: Queue_GetFront
 * --------------------------
 * Modo de uso:
 * Queue *Q;
 * NodeList *nuevo;
 * nuevo = Queue_GetFront(Q);
 * Esta operacion recibe una Cola y retorna su elemento inicial(frente)
 */
NodeList *Queue_GetFront(Queue *St);

/*
 * Funcion: Queue_GetLast
 * --------------------------
 * Modo de uso:
 * Queue *Q;
 * NodeList *nuevo;
 * nuevo = Queue_GetLast(Q);
 * Esta operacion recibe una Cola y retorna su elemento final
 */
NodeList *Queue_GetLast(Queue *Q);
#endif 