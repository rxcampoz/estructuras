#ifndef _GRAPH_H_
#define _GRAPH_H_

/*
 * ARCHIVO:
 *      graph.h
 * 		�ltima modificaci�n: 2007/04/11  (V. Mac�as)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA GRAPH
 * DEPENDENCIAS:
 *		lse.h		Definici�n de TDA List
 *		NodoLse.h	Definici�n de TDA NodeList
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original que define al grafo como una lista
 *		2007/04/11 (V. Mac�as): Versi�n en ingl�s
 */

#include "node_list.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

#define MAX_DIST 66000

/*-----------------------------------------------------------------------------------------
							TDA GRAPH
  -----------------------------------------------------------------------------------------*/
/*

	GRAPH: Lista de v�rtices
	+-----------+---------+   +-----------+---------+   +-----------+---------+   
	|	pInfo   |  pSgte -+-->|	  pInfo   |  pSgte -+-->|	pInfo   |  pSgte -+--+
	+-----+-----+---------+   +-----------+---------+   +-----------+---------+  |
	      |																		===
 +--------+
 |	v�rtice
 |	+------------+
 +->|	pInfo    | --> Informaci�n encapsulada en el v�rtice
	+------------+
	|  visitado  | --> Bandera para algoritmos de recorridos
	+------------+
	|	pLstAdy  |
	+-----+------+
	      |		
 +--------+
 |	
 |	Lista de adyacentes
 |	+-----------+---------+   +-----------+---------+   +-----------+---------+   
 +->|	pInfo   |  pSgte -+-->|	  pInfo   |  pSgte -+-->|	pInfo   |  pSgte -+--+
	+-----+-----+---------+   +-----------+---------+   +-----------+---------+  |
		  |																		===
 +--------+
 |  arco
 |  +------------+
 +->|	pOrigen  | --> V�rtice Origen
	+------------+
	|	pFin     | --> V�rtice Fin
	+------------+
    |	peso     | --> Factor de peso
	+------------+
    | InfoExtra  | --> Informaci�n adicional por arco
	+------------+
*/

//Grafo dirigido solamente
typedef List GRAPH;
typedef void (*GRAPH_Print)(void *pInfo);

typedef enum {NO_MARKED, MARKED} Mark;
//V�rtice
struct GRAPH_Vertex
{
	Generic info;
	List	*lst_adj;
	Mark	visit;//tipo de dato enumerado que sirve para crearle una marca
};
typedef struct GRAPH_Vertex GRAPH_Vertex;

//Arco
struct GRAPH_Edge	
{
	int	weight;
	Generic InfoExtra;
	GRAPH_Vertex *origin;
	GRAPH_Vertex *destination;
};
typedef struct GRAPH_Edge GRAPH_Edge;

/*
 * Funci�n: GRAPH_New
 * --------------------------
 * Modo de uso:
 * GRAPH G;
 * G = GRAPH_New();
 *
 * Descripci�n: Crea una List vac�a
 */
GRAPH *GRAPH_New();

/*
 * Funci�n: GRAPH_Delete
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Delete(&G);
 *
 * Descripci�n: Elimina los nodos de List liberando
 *			s�lo la memoria del contenedor y no de
 *			la informacion
 */
void GRAPH_Delete(GRAPH **G);

/*
 * Funci�n: GRAPH_Vertex_New
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *vertice;
 * Generico pInfo;
 * vertice = GRAPH_Vertex_New(pInfo);
 *
 * Descripci�n: Crea un nuevo vertice que tendr� como
 *			contenido la informaci�n recibida en pInfo
 */
GRAPH_Vertex *GRAPH_Vertex_New(Generic pInfo);

/*
 * Funci�n: GRAPH_Vertex_Delete
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *V;
 * GRAPH_Vertex_Delete(&V);
 *
 * Descripci�n: Elimina un vertice que no debe 
 *			pertenecer a grafo alguno (debe haberse
 *			sacado el vertice del grafo previamente);
 *			liberando la memoria de la informaci�n
 *			guardada, de su lista de adyancencia y
 *			del vertice mismo. 
 */
void GRAPH_Vertex_Delete(GRAPH_Vertex **V);

/* -------------------------------------------
 * FUNCIONES DE CONSULTA DE ATRIBUTOS
 * -------------------------------------------*/
Generic GRAPH_Vertex_GetContent(GRAPH_Vertex *v);
List *GRAPH_Vertex_GetListAdy(GRAPH_Vertex *v);
Mark GRAPH_Vertex_GetVisit(GRAPH_Vertex *v);
Generic GRAPH_Edge_GetContent(GRAPH_Edge *a);
int GRAPH_Edge_GetWeight(GRAPH_Edge *ar);
GRAPH_Vertex *GRAPH_Edge_GetOrigin(GRAPH_Edge *ar);
GRAPH_Vertex *GRAPH_Edge_GetDestination(GRAPH_Edge *ar);

/* -------------------------------------------
 * FUNCIONES DE MODIFICACION DE ATRIBUTOS
 * -------------------------------------------*/
void GRAPH_Vertex_SetVisit(GRAPH_Vertex *v, Mark visit);

/*
 * Funci�n: GRAPH_InsertVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pV;
 * GRAPH *G;
 * pInfo = GRAPH_InsertVertex(G,pV);
 *
 * Descripci�n: Inserta el vertice apuntado por
 *			pV en el Grafo apuntado por G
 */
void GRAPH_InsertVertex(GRAPH *G, GRAPH_Vertex *pV);

/*
 * Funci�n: GRAPH_RemoveVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pV;
 * GRAPH *G;
 * NodeList *pNodo;
 * pNodo = GRAPH_RemoveVertex(G,pV,FuncionComparacion);
 *
 * Descripci�n: Elimina el vertice apuntado por
 *			V del Grafo apuntado por G; retornando
 *			el nodo que tiene por contenido el 
 *			vertice sacado
 */
NodeList *GRAPH_RemoveVertex(GRAPH *G, GRAPH_Vertex *V, cmpfn fn);

/*
 * Funci�n: GRAPH_InsertEdge
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pOrigen, *pDestino;
 * GRAPH *G;
 * Generico pInfo;
 * GRAPH_InsertEdge(G,pOrigen,pDestino,pInfo);
 *
 * Descripci�n: Crea una nueva arco entre el vertice
 *			apuntado por pOrigen y el apuntado por
 *			pDestino; insertando la nueva arco en la
 *			lista de adyancencia del vertice origen
 */
void GRAPH_InsertEdge(GRAPH *G, GRAPH_Vertex *pOrigen, GRAPH_Vertex *pDestino, int peso, Generic IExtra);

/*
 * Funci�n: GRAPH_RemoveEdge
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pOrigen, *pDestino;
 * GRAPH *G;
 * GRAPH_RemoveEdge(G,pOrigen,pDestino);
 *
 * Descripci�n: Elimina la arco existente entre el 
 *			vertice apuntado por pOrigen y el apuntado
 *			por pDestino
 */
void GRAPH_RemoveEdge(GRAPH *G, GRAPH_Vertex *pOrigen, GRAPH_Vertex *pDestino);

/*
 * Funci�n: GRAPH_isEmpty
 * --------------------------
 * Modo de uso:
 * int resp;
 * GRAPH *G;
 * resp = GRAPH_isEmpty(G);
 *
 * Descripci�n: Verifica si el Grafo tiene vertices o no.
 */
int GRAPH_isEmpty(GRAPH *G);

/*
 * Funci�n: GRAPH_Vertex_areAdjacent
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *Vo, *V;
 * GRAPH_Edge *arco;
 * arco = GRAPH_Vertex_areAdjacent(Vo, V);
 *
 * Descripci�n: Verifica que dos Vertices sean adyacentes.
 *			Si lo son retorna la arco que los une, caso
 *			contrario retorna NULL
 */
GRAPH_Edge *GRAPH_Vertex_areAdjacent(GRAPH_Vertex *Vo, GRAPH_Vertex *V);

/*
 * Funci�n: GRAPH_Edge_CmpXVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *V;
 * GRAPH_Edge *ar;
 * int resp;
 * resp = GRAPH_Edge_CmpXVertex(ar, V);
 *
 * Descripci�n: Verifica si el vertice destino del 
 *			arco ar es igual al vertice V. Si son
 *			iguales retorna 0, en caso contrario 1.
 */
int GRAPH_Edge_CmpXVertex(GRAPH_Edge *ar, GRAPH_Vertex *V);

/*
 * Funci�n: GRAPH_GetNoVertices
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * int resp;
 * resp = GRAPH_GetNoVertices(G);
 *
 * Descripci�n: Retorna el n�mero de vertices que
 *			forman parte del grafo G
 */
int GRAPH_GetNoVertices(GRAPH *G);

/*
 * Funci�n: GRAPH_GetNoEdges
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * int resp;
 * resp = GRAPH_GetNoEdges(G);
 * Descripci�n: Retorna el n�mero total de arcos
 *			que	forman parte del grafo G
 */
int GRAPH_GetNoEdges(GRAPH *G);


/*
 * Funci�n: GRAPH_Vertex_Compare
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *V1, *V2;
 * int resp;
 * resp = GRAPH_Vertex_Compare(V1,V2);
 *
 * Descripci�n: Verifica si V1 y V2 referencian al
 *			mismo vertice. Si lo hacen retorna 0,
 *			caso contrario retorna 1.
 */
int GRAPH_Vertex_Compare(GRAPH_Vertex *V1, GRAPH_Vertex *V2);

/*
 * Funci�n: GRAPH_SearchVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pBuscado;
 * Generico cont;
 * GRAPH *G;
 * pBuscado = GRAPH_SearchVertex(G,cont,Funcion_Comparacion);
 *
 * Descripci�n: Busca en el grafo G un vertice cuyo
 *			contenido sea igual (segun la Funcion_Comparacion)
 *			al contenido pasado como argumento. Retorna la
 *			referencia al vertice si este existe, y si no
 *			retorna NULL
 */
GRAPH_Vertex *GRAPH_SearchVertex(GRAPH *G, Generic cont, cmpfn fn);

/*
 * Funci�n: GRAPH_Initiate
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Initiate(G);
 *
 * Descripci�n: Marca todos los v�rtices de un grafo
 *			como no visitados.
 */
void GRAPH_Initiate(GRAPH *G);

/*
 * Funci�n: GRAPH_GetDeepPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_GetDeepPath(G,Vo)
 * Descripci�n: Recorre en profundidad los v�rtices de
 *			un grafo, partiendo del v�rtice Vo, retornando
 *			una lista en el orden del recorrido.
 */
List *GRAPH_GetDeepPath(GRAPH *G, GRAPH_Vertex *Vo);

/*
 * Funci�n: GRAPH_ShowDeepPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_ShowDeepPath(G,Vo,f)
 * Descripci�n: Recorre en profundidad los v�rtices de
 *			un grafo, partiendo del v�rtice Vo, ejecutando
 *			la funci�n de impresi�n f para cada v�rtice en
 *			el orden del recorrido.
 */
void GRAPH_ShowDeepPath(GRAPH *G, GRAPH_Vertex *Vo, GRAPH_Print f);

/*
 * Funci�n: GRAPH_GetWidthPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_GetWidthPath(G,Vo)
 * Descripci�n: Recorre en anchura los v�rtices de
 *			un grafo, partiendo del v�rtice Vo, retornando
 *			una lista en el orden del recorrido.
 */
List *GRAPH_GetWidthPath(GRAPH *G, GRAPH_Vertex *Vo);

/*
 * Funci�n: GRAPH_ShowDeepPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_ShowDeepPath(G,Vo,f)
 * Descripci�n: Recorre en anchura los v�rtices de
 *			un grafo, partiendo del v�rtice Vo, ejecutando
 *			la funci�n de impresi�n f para cada v�rtice en
 *			el orden del recorrido.
 */
void GRAPH_ShowWidthPath(GRAPH *G, GRAPH_Vertex *Vo, GRAPH_Print f);

/*
 * Funci�n: GRAPH_Diskstra
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vorig;
 *int *DistanciasMenores
 *
 * DistanciasMenores = GRAPH_Diskstra(G,Vo,f)
 * Descripci�n: Recorre en anchura los v�rtices de
 *			un grafo, partiendo del v�rtice Vo, ejecutando
 *			la funci�n de impresi�n f para cada v�rtice en
 *			el orden del recorrido.
 */


 /* --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vorig;
 *int *DistanciasMenores
 *
 * DistanciasMenores = GRAPH_Diskstra(G,Vo,f)
 * Descripci�n: RETORNA LA EXENTRICIDAD DE UNN VERTICE V.
 *              La exentricidad de un vertice
 */
int GRAPH_Vertex_GetExentricidad(GRAPH *G, GRAPH_Vertex *V);

/*
 * Funcion :GRAPH_Vertex *GRAPH_GetCenter
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vorig;
 *int *DistanciasMenores
 *
 * DistanciasMenores = GRAPH_Diskstra(G,Vo,f)
 * Descripci�n: RETORNA LA EXENTRICIDAD DE UNN VERTICE V.
 *              La exentricidad de un vertice
 */
GRAPH_Vertex *GRAPH_GetCenter(GRAPH *G);

void Iniciar_VectorDistancias(int *Dist,GRAPH_Vertex *V,int tam,GRAPH *G);

GRAPH_Vertex *EscogerVerticeMenor(int *Dist, GRAPH *G,int tam);

void Modificar_Distancias(int *Dist,GRAPH_Vertex *Vk,int tam,GRAPH *G);


int Vertice_CmpXNom(GRAPH_Vertex *V, char *nombre);

int Vertice_CmpXCodCom(GRAPH_Vertex *V, char *codcom);

#endif