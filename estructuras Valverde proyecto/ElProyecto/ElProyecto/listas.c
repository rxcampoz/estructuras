/*
 * ARCHIVO:
 *      list.c
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementacion de las operaciones del TDA List
 *
 * DEPENDENCIAS:
 *		list.h:	Declaracion de tipos y funciones
 *		stdlib.h		Declaracion de malloc
*/

#include "listas.h"
#include <stdio.h>
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

NodeList * List_GetPrevious(List *L, NodeList *p){
	NodeList *q;
    if(List_isEmpty(L)) return NULL;

	//Si justo p es el nodo header, no hay anterior
    if(L->header == p) return NULL;

	//Buscar el anterior
    for(q=L->header; q!=NULL;q=q->next){
        //Pregunta: q, eres el anterior a p?
	    if(q->next ==p) return(q);
    }
    return(NULL);
}

int List_isEmpty(List *L){
	return (L->header == L->last && L->header == NULL);
}

int List_InsertHeader(List *L, NodeList *nuevo){
	if (nuevo == NULL) return 0;
	if(List_isEmpty(L)){ //si esta vacia, el nuevo nodo sera el unico en la lista
        L->header = L->last = nuevo;
    } else{ //Si no esta vacia, enlazar el nuevo nodo
        nuevo->next = L->header;
        L->header = nuevo;
    }
    return(1);
}

int List_InsertLast(List *L, NodeList *pnuevo){
	if(pnuevo == NULL) return 0;
    if(List_isEmpty(L)){
        L->header = L->last = pnuevo;
    } else{
        L->last->next = pnuevo;
        L->last = pnuevo;
    }
    return(1);

}

int List_InsertAfterNode(List *L, NodeList *p, NodeList *nuevo){
	//Si p es justo el ultimo nodo, Insertar el nodo nuevo al final
	if(L->last==p){
        return(List_InsertLast(L, nuevo));
    }else{ 	//Sino, enlazarlo
        if(p==NULL || ! List_NodeExists(L,p)) return 0;
        if(List_isEmpty(L))
            L->header = L->last = nuevo;
        else{
            nuevo->next = p->next;
            p->next = nuevo;
        }
    }
    return(1);
}

int List_NodeExists(List *L, NodeList *p){
	NodeList *q;
	//Busca a p dentor de la lista, aqui la comparacion es entre refe. a nodos
	for(q = L->header; q!=NULL; q = q->next){
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
        L->header = L->header->next;
    }
	tmp->next = NULL;
    return(tmp);
}

NodeList *List_RemoveLast(List *L){
	NodeList *tmp=L->header;
    if(List_isEmpty(L)) return NULL;
    if(L->header == L->last)
        L->header = L->last = NULL;
    else{
        tmp = L->last;
        L->last = List_GetPrevious(L, L->last);
        L->last->next = NULL;
    }
    return(tmp);
}

int List_RemoveXPos(List *L, NodeList *p){
    NodeList *p_ant;
    if(List_isEmpty(L)) return 0;
    if(p==NULL || !List_NodeExists(L, p)) return 0;
    if(p==L->header)
		List_RemoveHeader(L);
    else if(p == L->last)
		List_RemoveLast(L);
    else {
		p_ant = List_GetPrevious(L,p);
    	p_ant->next = p->next;
	}
	p->next = NULL;
	return(1);
}

NodeList *List_Find(List *L, Generic G, cmpfn f){
    NodeList *p;
    for(p = List_GetHeader(L); p!= NULL; p = NodeList_GetNext(p)){
        if(f(p->G,G) ==0) return(p);
    }
    return(NULL);
}

void List_Print(List *L, printfn fn){
	NodeList *p;
	for (p = List_GetHeader(L); p!=NULL; p = NodeList_GetNext(p)){
		fn(p->G);
	}
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
		List_InsertLast(L, nuevo);
	}
	fclose(F);
	return L;
}

void Save_File(char *archivo, List *L, savefn f)
{
	FILE *F;
	NodeList *p;
	F = fopen(archivo,"w");
	if(!F) return NULL;
	
	for(p=L->header;p!=NULL;p=p->next){
		f(F,p->G);
		if(p!=L->last) fprintf(F,"\n");
	}

	fclose(F);
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
		if(comp(nuevo->G, q->G) < 0){
			if(q == L->header) {
				List_InsertHeader(L,nuevo);
			}else{
				pant = List_GetPrevious(L,q);
				List_InsertAfterNode(L,pant,nuevo);
			}
			return;
		}
	}
	List_InsertLast(L,nuevo);
}

List * List_Order(List *L, cmpfn comp){
	List *Lordena;
	NodeList *q, *nuevo;
	Lordena = List_New();
	for(q=List_GetHeader(L); q!=NULL; q=NodeList_GetNext(q)){
		nuevo = NodeList_New(q->G);
		List_InsertInOrder(Lordena, nuevo,comp);
	}
	return Lordena;
}

int List_CountNodeRepeat(List *L, NodeList *p,cmpfn f){
    int cont=0;
    NodeList *q;
    for(q=List_GetHeader(L);q!=NULL;q=NodeList_GetNext(q)){
        if (f(q->G,p->G)==0) cont++;
    }
    return cont;
}

List * List_RemoveRepeat(List *L, cmpfn f){
    NodeList *p;
    for(p=List_GetHeader(L);p!=NULL;p=NodeList_GetNext(p)){
        if(List_CountNodeRepeat(L,p,f)>1){
            List_RemoveXPos(L,p);
            p=List_GetHeader(L);
        }
    }
    return L;
}

void Funcion_Relacionar2Listas(List *L1, List *L2, cmpfn cmp, linkfn link){
    NodeList *p,*q;
    for(q=List_GetHeader(L2);q!=NULL;q=NodeList_GetNext(q)){
        p=List_Find(L1,q->G,cmp);
        if(cmp(p->G,q->G)==0) link(p->G,q->G);        
    }
}

List *List_FindAll(List *L, Generic g, cmpfn cmp){
    NodeList *p;
    List *nueva=List_New();
    for(p=List_GetHeader(L);p!=NULL;p=NodeList_GetNext(p)){
        if(cmp(p->G,g)==0) List_InsertLast(nueva,NodeList_New(p->G));
    }
    return nueva;
}
/////////////////////////////////////////////////