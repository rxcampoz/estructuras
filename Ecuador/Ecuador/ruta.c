/*/
 * ARCHIVO:
 *      logistica.c
		creacion:2009/08/28
 * 		modificación: 2009/08/30
		modificación: 2009/09/01
		modificación: 2009/09/03
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene el codigo fuente de la parte del proyecto del
		segundo parcial de Estructuras de Datos
 * DEPENDENCIAS:
 *		ciudad.h
		generic.h
		list.h
		graph.h
		stack.h
		queue.h
 * Autores:
	*Andres Calle
	*Freddy Tandazo
 */


/*************************************************************************
**																		**
**							DEPENDENCIAS ADICIONALES					**
**																		**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generic.h"
#include "graph.h"
#include "list.h"
#include "ciudad.h"
#include "queue.h"
#include "stack.h"
#include "ciudad.h"
#include "camino.h"



/*************************************************************************
**																		**
**							PROTOTIPOS									**
**																		**
**************************************************************************/

void Titulo();
void Menu();
void Crear_ArcosIniciales(GRAPH *G,List *R);
int *GRAPH_Dikjstra(GRAPH *G,GRAPH_Vertex *Vorig);
void llenar_Grafo_Vertices(GRAPH *G, List *P);
void Opcion1(GRAPH *G,List *C, List *Cam);

/*************************************************************************
**																		**
**							PROGRAMA PRINCIPAL							**
**																		**
**************************************************************************/

void main(){
	char *ciudad="";
	int op;
	GRAPH *G=GRAPH_New();
	List *C=List_ReadFile("Ciudad.txt",Ciudad_Leer_Archivo);
	List *Cam=List_ReadFile("Camino.txt",Camino_Leer_Archivo);
	
	do{
		Titulo();
		Menu();
		scanf("%d",&op);
		if(op==1){
			Opcion1(G,C,Cam);
		}


	}while(op!=2);
	

}

/*************************************************************************
**																		**
**							IMPLEMENTACIONES							**
**																		**
**************************************************************************/
/*
** FUNCION: void Opcion1(GRAPH *G,List *C, List *Cam);
**	DESCRIPCION: Muestra la primera opcion del menu
**	Uso: Opcion1(G,c,Cam);
***/

void Opcion1(GRAPH *G,List *C, List *Cam){
	Ciudad *city;
	NodeList *nodo;
	char *ciudad2="";
	char ciudad[50];
	int tam=List_GetSize(G);
	int i;
	int *Dist=malloc(sizeof(int)*tam);//El tamaño 
	llenar_Grafo_Vertices(G,C);
	Crear_ArcosIniciales(G,Cam);
	printf("\n\n\t\tEscoja la ciudad que desea consultar\t:)");
	scanf("%s",ciudad);
	ciudad2=ciudad;
	city=Ciudad_Crear("",ciudad2);
	nodo=List_Search(C,city,Ciudad_cmpXNombre);
	
	if(nodo){

		Dist=GRAPH_Dikjstra(G,GRAPH_SearchVertex(G,city,Ciudad_cmpXNombre));
		
	}
	else{
		printf("\n\n\t\t***********************************************");
		printf("\n\n\t\t********	La Ciudad no existe    ************");
		printf("\n\n\t\t***********************************************");
	}
	
		



}
/*
**FUNCION: void Titulo();
**DESCRIPCION:Presenta el titulo del proyecto
**USO: Titulo();
*/
void Titulo(){
	printf("\n\n\t\t***********************************************");
	printf("\n\n\t\t********     RUTAS DEL ECUADOR    *************");
	printf("\n\n\t\t***********************************************");
}
/*
**FUNCION:void Menu();
**DESCRIPCION:Presenta el menu principal del proyecto
**USO: Menu();
*/
void Menu(){
	printf("\n\n\t1.-Ver rutas");
	printf("\n\n\t2.-Salir");
	printf("\n\n\tIngrese la opcion deseada");
}

/*
*FUNCION:void llenar_Grafo_Vertices(GRAPH *G, List *P)
*DESCRIPCION: Llena los vertices del grafo
* Uso: llenar_Grafo_Vertices(G, P);
*/

void llenar_Grafo_Vertices(GRAPH *G, List *P){
	NodeList *p;
	GRAPH_Vertex *V;

	for(p=List_GetHeader(P);p!=NULL;p=p->next){
		V=GRAPH_Vertex_New(NodeList_GetContent(p));
		List_InsertAfterLast(G,NodeList_New(V));
	}
}


/*
*FUNCION:void Crear_ArcosIniciales(GRAPH *G,List *R)
*DESCRIPCION:Crea los arcos de los verrices
* Uso: Crear_ArcosIniciales(G, R);
*/

void Crear_ArcosIniciales(GRAPH *G,List *R)
{
	Camino *ru,*ca;
	Ciudad *pu,*ci,*ciu;
	NodeList *p,*q;
	GRAPH_Edge *ar;
	GRAPH_Vertex *V1,*V2;
	List *L;
	

	for(p=List_GetHeader(G);p!=NULL;p=p->next){
		V1=NodeList_GetContent(p);
		L=List_SearchAll(R,Ciudad_GetNombre(GRAPH_Vertex_GetContent(V1)),Camino_CompXV1);
		for(q=List_GetHeader(L);q!=NULL;q=q->next){
			V2=NodeList_GetContent(List_Search(G,Camino_GetDestino(NodeList_GetContent(q)),Vertice_CmpXCodCom));
			
			
				GRAPH_InsertEdge(G,V1,V2,0,NodeList_GetContent(q));
				
			
			
		}
	}
}
/*
 * Función: GRAPH_Diskstra
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vorig;
 *int *DistanciasMenores
 *
 * DistanciasMenores = GRAPH_Diskstra(G,Vo,f)
 * Descripción: Recorre en anchura los vértices de
 *			un grafo, partiendo del vértice Vo, ejecutando
 *			la función de impresión f para cada vértice en
 *			el orden del recorrido.
 */
int *GRAPH_Dikjstra(GRAPH *G,GRAPH_Vertex *Vorig)
{
	NodeList *nodo;
	Ciudad *city;
	int *Dist,tam,pos;
	List *Lvert;
	GRAPH_Vertex *Vk;
	GRAPH_Initiate(G);
	tam=List_GetSize(G);
	Dist=malloc(sizeof(int)*tam);//El tamaño 
	
    Iniciar_VectorDistancias(Dist,Vorig,tam,G);
	Lvert=List_Copy(G);
	List_RemoveXPos(Lvert,List_Search(Lvert,Vorig,GRAPH_Vertex_Compare));
	while(!List_isEmpty(Lvert))
	{
		Vk =EscogerVerticeMenor(Dist,G,tam);
		Modificar_Distancias(Dist,Vk,tam,G);
		GRAPH_Vertex_SetVisit(Vk,MARKED);
		List_RemoveXPos(Lvert,List_Search(Lvert,Vk,GRAPH_Vertex_Compare));
		city=Vk->info;
		Ciudad_Imprimir(city);
	}
	List_Delete(&Lvert);
	return(Dist);
}