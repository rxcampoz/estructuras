#include "stack.h"

/*
 * ARCHIVO:
 *      stack.c
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementacion de las operaciones
 *		para el manejo del TDA Stack (Pila)
 *
 * DEPENDENCIAS:
 *      stack.h:   la interfaz
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
	List_InsertHeader(S, nuevo);
}

NodeList *Stack_Pop(Stack *S){
	return(List_RemoveHeader(S));
}

void Stack_Delete(Stack **S){
	List_Delete(S);
}

NodeList *Stack_Top(Stack *S){
	return List_GetHeader(S);
}

int Stack_GetSize(Stack *S){
	return List_GetSize(S);
}