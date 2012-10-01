#include <stdlib.h>
#include "graph.h"

/*
 * ARCHIVO:
 *      graph.c
 * 		Última modificación: 2007/04/11  (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la implementación del TDA GRAPH
 * DEPENDENCIAS:
 *		stdlib.h	Funciones para manejo de memoria
 *		graph.h		Interfaz del TDA GRAPH
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original que define al grafo como una lista
 *		2007/04/11 (V. Macías): Versión en inglés
 */


GRAPH *GRAPH_New()
{
	return List_New();
}

void GRAPH_Delete(GRAPH **G)
{
	List_Delete(G);
}

GRAPH_Vertex *GRAPH_Vertex_New(Generic pInfo)
{
	GRAPH_Vertex *v =(GRAPH_Vertex *)malloc(sizeof(GRAPH_Vertex));

	if(v)
	{
		v->info = pInfo;
		v->visit = NO_MARKED;
		v->lst_adj = List_New();
	}
	return v;
}

void GRAPH_Vertex_Delete(GRAPH_Vertex **V)
{
	free((*V)->info);
	List_Delete(&((*V)->lst_adj));
	free(&V);
}

Generic GRAPH_Vertex_GetContent(GRAPH_Vertex *v)
{
	Generic pInfo = NULL;
	if(v)
	{
		pInfo = v->info;
	}
	return pInfo;
}

List *GRAPH_Vertex_GetListAdy(GRAPH_Vertex *v)
{
	return(v->lst_adj);
}

Mark GRAPH_Vertex_GetVisit(GRAPH_Vertex *v){
	return(v->visit);
}

Generic GRAPH_Edge_GetContent(GRAPH_Edge *a){
	return(a->InfoExtra);
}

int GRAPH_Edge_GetWeight(GRAPH_Edge *ar) {
	return(ar->weight);
}

GRAPH_Vertex *GRAPH_Edge_GetOrigin(GRAPH_Edge *ar){
	return(ar->origin);
}

GRAPH_Vertex *GRAPH_Edge_GetDestination(GRAPH_Edge *ar){
	return(ar->destination);
}

void GRAPH_Vertex_SetVisit(GRAPH_Vertex *v, Mark visit){
	v->visit = visit;
}

void GRAPH_InsertVertex(GRAPH *G, GRAPH_Vertex *pV)
{
	NodeList *pNodo=NULL;
	
	pNodo = NodeList_New(pV);
	if(pNodo)
	{
		List_InsertAfterLast(G, pNodo);
	}
}

NodeList *GRAPH_RemoveVertex(GRAPH *G, GRAPH_Vertex *V, cmpfn fn)
{
	NodeList *pnodovertice;
	List_Delete(&(V->lst_adj));
	for(pnodovertice = List_GetHeader(G); 
			pnodovertice!=NULL; 
			pnodovertice = NodeList_GetNext(pnodovertice)){
				GRAPH_RemoveEdge(G, NodeList_GetContent(pnodovertice), V); 		
	}
	pnodovertice = List_Search(G, V, fn);
	List_RemoveXPos(G, pnodovertice);
	return pnodovertice;
}


void GRAPH_InsertEdge(GRAPH *G, GRAPH_Vertex *pOrigen, GRAPH_Vertex *pDestino, int peso, Generic IExtra)
{
	GRAPH_Edge *pA=NULL;
	NodeList *pNodo=NULL;

	pA = (GRAPH_Edge *)malloc(sizeof(GRAPH_Edge));
	if(pA)
	{
		pA->origin = pOrigen;
		pA->destination = pDestino;
		pA->weight = peso;
		pA->InfoExtra = IExtra;

		pNodo=NodeList_New(pA);
		if(pNodo)
		{
			List_InsertAfterLast(pOrigen->lst_adj, pNodo);
		}
		else
		{
			free(pA);
			pA = NULL;
		}
	}
}

void GRAPH_RemoveEdge(GRAPH *G, GRAPH_Vertex *A, GRAPH_Vertex *B)
{
	NodeList *pnodo_arco;
	if(!A->lst_adj) return;
	pnodo_arco = List_Search(A->lst_adj, B,GRAPH_Edge_CmpXVertex);
	if(pnodo_arco){
		List_RemoveXPos(A->lst_adj, pnodo_arco);
		free(pnodo_arco->G);
		NodeList_Delete(&pnodo_arco);
	}
}

int GRAPH_isEmpty(GRAPH *G)
{
	return List_isEmpty(G);
}

GRAPH_Edge *GRAPH_Vertex_areAdjacent(GRAPH_Vertex *Vo, GRAPH_Vertex *V)
{
	NodeList *p;

	if (!Vo->lst_adj || List_isEmpty(Vo->lst_adj)) return(NULL);

	p = List_Search(Vo->lst_adj,V,GRAPH_Edge_CmpXVertex);
	if (!p) return(NULL);

	return(NodeList_GetContent(p));
}

int GRAPH_Edge_CmpXVertex(GRAPH_Edge *ar, GRAPH_Vertex *V)
{
	if(ar->destination == V)
		return(0);
	return(1);
}

int GRAPH_GetNoVertices(GRAPH *G){
	return (List_GetSize(G));
}

int GRAPH_GetNoEdges(GRAPH *G){
	int total=0;
	GRAPH_Vertex *cvert;
	NodeList *p;
	for(p = List_GetHeader(G); p!=NULL; p = NodeList_GetNext(p)){
		cvert = NodeList_GetContent(p);
		total += List_GetSize(cvert->lst_adj);
	}
	return total;
}

int GRAPH_Vertex_Compare(GRAPH_Vertex *V1, GRAPH_Vertex *V2)
{
	if(V1==V2)
		return(0);
	return(1);
}

GRAPH_Vertex *GRAPH_SearchVertex(GRAPH *G, Generic cont, cmpfn fn){
	GRAPH_Vertex *v;
	NodeList *p;
	for(p = List_GetHeader(G); p!=NULL; p = NodeList_GetNext(p)){
		v = NodeList_GetContent(p);
		if(fn(v->info, cont) == 0) return v;
	}
	return NULL;
}


void GRAPH_Initiate(GRAPH *G){
	GRAPH_Vertex *v;
	NodeList *p;

	for(p=List_GetHeader(G);p!=NULL;p=NodeList_GetNext(p)){
		v = NodeList_GetContent(p);
		GRAPH_Vertex_SetVisit(v,NO_MARKED);
	}
}

List *GRAPH_GetDeepPath(GRAPH *G, GRAPH_Vertex *Vo){
	List *L, *LAdj;
	Stack *S;
	NodeList *p;
	GRAPH_Vertex *v;
	GRAPH_Edge *arc;

	if (!List_Search(G,Vo,GRAPH_Vertex_Compare))
		return NULL;

	L = List_New();
	S = Stack_New();
	p = NodeList_New(Vo);
	Stack_Push(S,p);

	while(!Stack_isEmpty(S))
	{
		p = Stack_Pop(S);
		List_InsertAfterLast(L,p);
		v = NodeList_GetContent(p);
		if (GRAPH_Vertex_GetVisit(v)==NO_MARKED) {
			GRAPH_Vertex_SetVisit(v,MARKED);
			LAdj = GRAPH_Vertex_GetListAdy(v);
			for (p=List_GetHeader(LAdj);p!=NULL;p=NodeList_GetNext(p)){
				arc = NodeList_GetContent(p);
				Stack_Push(S,NodeList_New(GRAPH_Edge_GetDestination(arc)));
			}
		}
	}
	Stack_Delete(&S);
	return(L);
}

void GRAPH_ShowDeepPath(GRAPH *G, GRAPH_Vertex *Vo, GRAPH_Print f){
	List *L;

	L = GRAPH_GetDeepPath(G,Vo);
	if (L) {
		List_Print(L,f);
		List_Delete(&L);
	}
}

List *GRAPH_GetWidthPath(GRAPH *G, GRAPH_Vertex *Vo){
	List *L, *LAdj;
	Queue *Q;
	NodeList *p;
	GRAPH_Vertex *v;
	GRAPH_Edge *arc;

	if (!List_Search(G,Vo,GRAPH_Vertex_Compare))
		return NULL;

	L = List_New();
	Q = Queue_New();
	p = NodeList_New(Vo);
	Queue_Push(Q,p);

	while(!Queue_isEmpty(Q))
	{
		p = Queue_Pop(Q);
		List_InsertAfterLast(L,p);
		v = NodeList_GetContent(p);
		if (GRAPH_Vertex_GetVisit(v)==NO_MARKED) {
			GRAPH_Vertex_SetVisit(v,MARKED);
			LAdj = GRAPH_Vertex_GetListAdy(v);
			for (p=List_GetHeader(LAdj);p!=NULL;p=NodeList_GetNext(p)){
				arc = NodeList_GetContent(p);
				Queue_Push(Q,NodeList_New(GRAPH_Edge_GetDestination(arc)));
			}
		}
	}
	Queue_Delete(&Q);
	return(L);
}

void GRAPH_ShowWidthPath(GRAPH *G, GRAPH_Vertex *Vo, GRAPH_Print f){
	List *L;

	L = GRAPH_GetWidthPath(G,Vo);
	if(L) {
		List_Print(L,f);
		List_Delete(&L);
	}
}



void Iniciar_VectorDistancias(int *Dist,GRAPH_Vertex *V,int tam,GRAPH *G)
{
     int i;
	 NodeList *p,*q;
	 GRAPH_Edge *arco;

	 //inicializo con infinito todas las distancias
	 for(i=0;i<tam;i++)
		 Dist[i]= 30000;
     //INICIALIZANDO CON 0 la distancia al propio vector
	 q=List_Search(G,V,GRAPH_Vertex_Compare);
	 i =List_GetNodeIndex(G,q);
	 Dist[i]=0;
	 //marco como visitado el vertice de origen
	 GRAPH_Vertex_SetVisit(V,MARKED);
     //INICIALIZO con el factor de peso la distancia d elos adyacentes
	 for(p=List_GetHeader(V->lst_adj);p!=NULL;p=NodeList_GetNext(p))
	 {
		 arco=NodeList_GetContent(p);
		 q=List_Search(G,arco->destination,GRAPH_Vertex_Compare);
         i =List_GetNodeIndex(G,q);
		 Dist[i]=arco->weight;
	}
}

GRAPH_Vertex *EscogerVerticeMenor(int *Dist, GRAPH *G,int tam)
{
     int i, valorMenor, indexMenor;
     GRAPH_Vertex *Vk;

     indexMenor =-1;
	 valorMenor = 30001;
	 for(i=0;i<tam;i++){
	       Vk=NodeList_GetContent(List_GetNodeXIndex(G,i));
		   if(GRAPH_Vertex_GetVisit(Vk)==NO_MARKED)
		   {
			   if(Dist[i]<=valorMenor){
				   indexMenor =i;
				   valorMenor =Dist[i];}
		   }
	 }
	 Vk =NodeList_GetContent(List_GetNodeXIndex(G,indexMenor));
	 return(Vk);
}

void Modificar_Distancias(int *Dist,GRAPH_Vertex *Vk,int tam,GRAPH *G){
     NodeList *p;
	 GRAPH_Edge *arc;
	 int indexVk,index;
     
	 indexVk=List_GetNodeIndex(G,List_Search(G,Vk,GRAPH_Vertex_Compare));
	 for(p=List_GetHeader(Vk->lst_adj);p!=NULL;p=NodeList_GetNext(p))
	 {
		 arc =NodeList_GetContent(p);
		 index=List_GetNodeIndex(G,List_Search(G,arc->destination,GRAPH_Vertex_Compare));
		 if(Dist[index]>(Dist[indexVk]+arc->weight))
			 Dist[index]=Dist[indexVk]+arc->weight;
	 }
}

//int GRAPH_Vertex_GetExentricidad(GRAPH *G, GRAPH_Vertex *V);



int Vertice_CmpXNom(GRAPH_Vertex *V, char *nombre) {
	return(strcmp(GRAPH_Vertex_GetContent(V),nombre));
}

int Vertice_CmpXCodCom(GRAPH_Vertex *V, char *codcom){
	return (Ciudad_CompararXNombre(GRAPH_Vertex_GetContent(V),codcom));
}


