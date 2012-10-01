/*
 * ARCHIVO:
 *      list.c
 * 		Última modificación: 2007/03/20  (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementación de las operaciones del TDA List
 *
 * DEPENDENCIAS:
 *		list.h:	Declaración de tipos y funciones
 *		stdlib.h		Declaración de malloc
 * MODIFICACIONES:
 *		2006/11/23 (M. Loor):	Versión inicial
 *		2007/03/20 (V. Macías): Cambio para trabajar con cabecera y final
*/

#include "list.h"

List * List_New(){
	List *nuevalista;
	nuevalista = malloc(sizeof(List));
	//tanto el primero como el ultimo van a referencia invalida
	nuevalista->header = nuevalista->last = NULL;
	return nuevalista;
}

void List_Delete(List **L){
   	NodeList *retirado;
	if(!(*L)) return;
    if((*L)->header)
    {
		//Si hay elementos, eliminar cada uno de ellos
        while(!List_isEmpty(*L))
        {
			retirado = List_RemoveHeader(*L);
			NodeList_Delete(&retirado);
        }
    }
	free(*L);
	*L = NULL;
}

NodeList *List_GetHeader(List *L){
	return (L->header);
}

NodeList *List_GetLast(List *L){
	return (L->last);
}

NodeList * List_GetNodeBefore(List *L, NodeList *p){
	NodeList *q;
	if(List_isEmpty(L)) return NULL;

	//Si justo p es el nodo header, no hay anterior
	if(L->header == p) return NULL;

	//Buscar el anterior
	for(q=L->header; q!=NULL;q=NodeList_GetNext(q)){
		//Pregunta: q, eres el anterior a p?
		if(NodeList_GetNext(q)==p) return(q);
    }
    return(NULL);
}

int List_isEmpty(List *L){
	return (L->header == L->last && L->header == NULL);
}

int List_InsertBeforeHeader(List *L, NodeList *nuevo){
	if (!nuevo) return 0;
	if(List_isEmpty(L)){ //si esta vacia, el nuevo nodo sera el unico en la lista
        L->header = L->last = nuevo;
    } else{ //Si no esta vacia, enlazar el nuevo nodo
        NodeList_SetNext(nuevo,L->header);
        L->header = nuevo;
    }
    return(1);
}

int List_InsertAfterLast(List *L, NodeList *pnuevo){
	if(!pnuevo) return 0;
    if(List_isEmpty(L)){
        L->header = L->last = pnuevo;
    } else{
        NodeList_SetNext(L->last, pnuevo);
        L->last = pnuevo;
    }
    return(1);
}

int List_InsertAfterNode(List *L, NodeList *p, NodeList *nuevo){
	//Si p es justo el ultimo nodo, Insertar el nodo nuevo al final
	if(L->last==p){
        return(List_InsertAfterLast(L, nuevo));
    }else{ 	//Sino, enlazarlo
        if(!p || !List_isNodeExist(L,p)) return 0;
        if(List_isEmpty(L))
            L->header = L->last = nuevo;
        else{
            NodeList_SetNext(nuevo,NodeList_GetNext(p));
            NodeList_SetNext(p,nuevo);
        }
    }
    return(1);
}

int List_isNodeExist(List *L, NodeList *p){
	NodeList *q;
	//Busca a p dentro de la lista, aqui la comparacion es entre refe. a nodos
	for(q = L->header; q!=NULL; q = NodeList_GetNext(q)){
		if(q == p) return 1;
	}
	return 0;
}

NodeList *List_RemoveHeader(List *L){
	//tmp se ubica al inicio de la lista
	NodeList *tmp = List_GetHeader(L);

    if(List_isEmpty(L)) return NULL;
    //Si la lista esta vacia, solo inicializarla y retornar tmp
    if(L->header == L->last)
        L->header = L->last = NULL;
    else {      //Si la lista no esta vacia, solo retroceder el primero
        L->header = NodeList_GetNext(L->header);
    }
	NodeList_SetNext(tmp,NULL);
    return(tmp);
}

NodeList *List_RemoveLast(List *L){
	NodeList *tmp=L->header;
    if(List_isEmpty(L)) return NULL;
    if(L->header == L->last)
        L->header = L->last = NULL;
    else{
        tmp = L->last;
        L->last = List_GetNodeBefore(L, L->last);
        NodeList_SetNext(L->last,NULL);
    }
    return(tmp);
}

int List_RemoveXPos(List *L, NodeList *p){
    NodeList *p_ant;
    if(List_isEmpty(L)) return 0;
    if(!p || !List_isNodeExist(L, p)) return 0;
    if(p==L->header)
		List_RemoveHeader(L);
    else if(p == L->last)
		List_RemoveLast(L);
    else {
		p_ant = List_GetNodeBefore(L,p);
    	NodeList_SetNext(p_ant, NodeList_GetNext(p));
	}
	NodeList_SetNext(p,NULL);
	return(1);
}

NodeList *List_Search(List *L, Generic G, cmpfn f){
    NodeList *p;
    for(p = List_GetHeader(L); p!= NULL; p = NodeList_GetNext(p)){
        if(f(NodeList_GetContent(p),G) ==0) return(p);
    }
    return(NULL);
}

void List_Print(List *L, printfn fn){
	NodeList *p;
	for (p = List_GetHeader(L); p!=NULL; p = NodeList_GetNext(p)){
		fn(NodeList_GetContent(p));
	}
}

List* List_Copy(List *Lorig){
	NodeList *p, *nuevo;
	List *Lcopia;
	int i;

	Lcopia=List_New();
	for (p = List_GetHeader(Lorig); p!=NULL; p = NodeList_GetNext(p)){
		nuevo=NodeList_New(NodeList_GetContent(p));
		i=List_InsertAfterLast(Lcopia,nuevo);
	}
	return(Lcopia);
}

List *List_ReadFile(char *archivo, leerfn f){
	FILE *F;
	List *L;
	Generic G;
	NodeList *nuevo;
	L = List_New();
	F = fopen(archivo,"r");
	if(!F) return NULL;
	while(!feof(F)){
		G = f(F);
		nuevo = NodeList_New(G);
		List_InsertAfterLast(L, nuevo);
	}
	fclose(F);
	return L;
}

NodeList *List_GetNodeXIndex(List *L, int index){
	int i=0;
	NodeList *p;
	for(p = List_GetHeader(L); p!=NULL; p = NodeList_GetNext(p)){
		if(i == index) return p;
		i++;
	}
	return NULL;
}

int List_GetSize(List *L){
	NodeList *p;
	int cont = 0;
	for (p = List_GetHeader(L); p!=NULL; p = NodeList_GetNext(p)){
		cont++;
	}
	return cont;
}

List *List_SearchAll(List *L, Generic G, cmpfn f){
	List *Lnew;
	NodeList *nuevo, *p;
	Lnew = List_New();

    for(p = List_GetHeader(L); p!= NULL; p = NodeList_GetNext(p)){
		if(f(NodeList_GetContent(p),G)==0) {
			nuevo = NodeList_New(NodeList_GetContent(p));
			List_InsertAfterLast(Lnew, nuevo);
		}
	}
	return Lnew;
}

int List_GetNodeIndex(List *L, NodeList *p) {
	NodeList *q;
	int i=0;

	for(q=List_GetHeader(L);q!=NULL;q=NodeList_GetNext(q))
	{
		if (q==p)
			return(i);
		i++;
	}

	return(-1);
}

void List_InsertInOrder(List *L, NodeList *nuevo, cmpfn comp){

	NodeList *q, *pant;
	for(q=List_GetHeader(L); q!=NULL; q=NodeList_GetNext(q)){
		if(comp(NodeList_GetContent(nuevo), NodeList_GetContent(q)) < 0){
			if(q == L->header) {
				List_InsertBeforeHeader(L,nuevo);
			}else{
				pant = List_GetNodeBefore(L,q);
				List_InsertAfterNode(L,pant,nuevo);
			}
			return;
		}
	}
	List_InsertAfterLast(L,nuevo);
}

List * List_Order(List *L, cmpfn comp){
	List *Lordena;
	NodeList *q, *nuevo;
	Lordena = List_New();
	for(q=List_GetHeader(L); q!=NULL; q=NodeList_GetNext(q)){
		nuevo = NodeList_New(NodeList_GetContent(q));
		List_InsertInOrder(Lordena, nuevo,comp);
	}
	return Lordena;
}
