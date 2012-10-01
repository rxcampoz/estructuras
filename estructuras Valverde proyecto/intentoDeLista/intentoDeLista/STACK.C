#include "stack.h"

/*
 * ARCHIVO:
 *      stack.c
 * 		Última modificación: 2007/03/27 (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementacion de las operaciones
 *		para el manejo del TDA Stack (Pila)
 *
 * DEPENDENCIAS:
 *      stack.h:   la interfaz
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original 
 *		2007/03/27 (V. Macías):	Version con nombres en inglés.
 */

int Stack_isEmpty(Stack *S){
	return List_isEmpty(S);
}

Stack* Stack_New(){
	Stack *S;
	S = List_New();
	return S;
}

void Stack_Push(Stack *S, NodeList *nuevo){
	List_InsertAfterLast(S, nuevo);
}

NodeList *Stack_Pop(Stack *S){
	return(List_RemoveLast(S));
}

void Stack_Delete(Stack **S){
	List_Delete(S);
}

NodeList *Stack_GetFront(Stack *S){
	return List_GetLast(S);
}

int Stack_GetSize(Stack *S){
	return List_GetSize(S);
}