#ifndef STACK_H
#define STACK_H

/*
 * ARCHIVO:
 *      stack.h
 * 		Última modificación: 2007/03/27 (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA PILA (STACK) 
 * DEPENDENCIAS:
 *		list.h Definición de TDA List, ya que el Stack es una lista
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original que define a la cola como una lista
 *		2007/03/27 (V. Macías):	Version con nombres en inglés.
 */

#include "list.h"

/*-----------------------------------------------------------------------------------------
							TDA PILA (STACK)
  -----------------------------------------------------------------------------------------*/

/****************
	NIVEL LÓGICO
 ****************

	Definición
	_____________________________________________________________________________________
	<cola> ::= <frente> + {<nodo>} + <final>
	_____________________________________________________________________________________
	Creación/Destrucción
		Stack_New()
		Stack_Delete(nombreStack)
	Comprobación de Estado
		Stack_isEmpty(nombreStack) : inteano
	Stack_Push y Stack_Pop
		Stack_Push(nombreStack, nodonuevo) :
		Stack_Pop(nombreStack) :referencia_nodo
*/

/*
 * Tipo: Stack
 * ---------------
 * Una pila es un conjunto de elementos, donde solo se conoce
 * el primer elemento
 */

typedef List Stack;

/*
 * Funcion: Stack_isEmpty
 * --------------------------
 * Modo de uso:
 * Stack *S;
 * if(Stack_isEmpty(S))...
 * Esta operacion recibe una pila y determina si esta o no vacia
 */
int Stack_isEmpty(Stack *S);

/*
 * Funcion: Stack_New
 * --------------------------
 * Modo de uso:
 * Stack *S;
 * S=Stack_New()...
 * Esta operacion crea una nueva Pila
 */
Stack * Stack_New();

/*
 * Funcion: Stack_Push
 * --------------------------
 * Modo de uso:
 * Stack *S;
 * NodeList *nuevo;
 * Stack_Push(S, nuevo);
 * Esta operacion recibe una Pila y aumenta al elemento nuevo
 * al Tope de la misma
 */
void Stack_Push(Stack *S, NodeList *nuevo);

/*
 * Funcion: Stack_Pop
 * --------------------------
 * Modo de uso:
 * Stack *S;
 * NodeList *nuevo;
 * nuevo = Stack_Pop(S)...
 * Esta operacion recibe una Pila y retira de la misma
 * el elemento del Tope, retornandolo
 */
NodeList *Stack_Pop(Stack *S);

/*
 * Funcion: Stack_Delete
 * --------------------------
 * Modo de uso:
 * Stack *S;
 * Stack_Delete(&S);
 * Esta operacion recibe una pila retirando uno a uno
 * los elementos de la misma hasta que quede vacia
 */
void Stack_Delete(Stack **S);

/*
 * Funcion: Stack_GetTop
 * --------------------------
 * Modo de uso:
 * Stack *S;
 * NodeList *nuevo;
 * nuevo = Stack_GetTop(S);
 * Esta operacion recibe una pila y retorna su elemento del tope
 */
NodeList *Stack_GetTop(Stack *S);

/*
 * Funcion: Stack_GetSize
 * --------------------------
 * Modo de uso:
 * Stack *S;
 * int size;
 * size = Stack_GetSize(S);
 * Esta operacion recibe una pila y retorna el número de elementos
 * que hay en la misma
 */
int Stack_GetSize(Stack *S);

#endif 