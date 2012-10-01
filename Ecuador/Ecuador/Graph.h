#ifndef _GRAPH_H_
#define _GRAPH_H_

/*
 * ARCHIVO:
 *      graph.h
 * 		Última modificación: 2007/04/11  (V. Macías)
 * --------------------------------------------------------------------------------------
 * DESCRIPCION:
 * 		Este archivo contiene la interfaz del TDA GRAPH
 * DEPENDENCIAS:
 *		lse.h		Definición de TDA List
 *		NodoLse.h	Definición de TDA NodeList
 * MODIFICACIONES:
 *		2004/06/08 (Marisol Villacres):	Version original que define al grafo como una lista
 *		2007/04/11 (V. Macías): Versión en inglés
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

	GRAPH: Lista de vértices
	+-----------+---------+   +-----------+---------+   +-----------+---------+   
	|	pInfo   |  pSgte -+-->|	  pInfo   |  pSgte -+-->|	pInfo   |  pSgte -+--+
	+-----+-----+---------+   +-----------+---------+   +-----------+---------+  |
	      |																		===
 +--------+
 |	vértice
 |	+------------+
 +->|	pInfo    | --> Información encapsulada en el vértice
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
 +->|	pOrigen  | --> Vértice Origen
	+------------+
	|	pFin     | --> Vértice Fin
	+------------+
    |	peso     | --> Factor de peso
	+------------+
    | InfoExtra  | --> Información adicional por arco
	+------------+
*/

//Grafo dirigido solamente
typedef List GRAPH;
typedef void (*GRAPH_Print)(void *pInfo);

typedef enum {NO_MARKED, MARKED} Mark;
//Vértice
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
 * Función: GRAPH_New
 * --------------------------
 * Modo de uso:
 * GRAPH G;
 * G = GRAPH_New();
 *
 * Descripción: Crea una List vacía
 */
GRAPH *GRAPH_New();

/*
 * Función: GRAPH_Delete
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Delete(&G);
 *
 * Descripción: Elimina los nodos de List liberando
 *			sólo la memoria del contenedor y no de
 *			la informacion
 */
void GRAPH_Delete(GRAPH **G);

/*
 * Función: GRAPH_Vertex_New
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *vertice;
 * Generico pInfo;
 * vertice = GRAPH_Vertex_New(pInfo);
 *
 * Descripción: Crea un nuevo vertice que tendrá como
 *			contenido la información recibida en pInfo
 */
GRAPH_Vertex *GRAPH_Vertex_New(Generic pInfo);

/*
 * Función: GRAPH_Vertex_Delete
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *V;
 * GRAPH_Vertex_Delete(&V);
 *
 * Descripción: Elimina un vertice que no debe 
 *			pertenecer a grafo alguno (debe haberse
 *			sacado el vertice del grafo previamente);
 *			liberando la memoria de la información
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
 * Función: GRAPH_InsertVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pV;
 * GRAPH *G;
 * pInfo = GRAPH_InsertVertex(G,pV);
 *
 * Descripción: Inserta el vertice apuntado por
 *			pV en el Grafo apuntado por G
 */
void GRAPH_InsertVertex(GRAPH *G, GRAPH_Vertex *pV);

/*
 * Función: GRAPH_RemoveVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pV;
 * GRAPH *G;
 * NodeList *pNodo;
 * pNodo = GRAPH_RemoveVertex(G,pV,FuncionComparacion);
 *
 * Descripción: Elimina el vertice apuntado por
 *			V del Grafo apuntado por G; retornando
 *			el nodo que tiene por contenido el 
 *			vertice sacado
 */
NodeList *GRAPH_RemoveVertex(GRAPH *G, GRAPH_Vertex *V, cmpfn fn);

/*
 * Función: GRAPH_InsertEdge
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pOrigen, *pDestino;
 * GRAPH *G;
 * Generico pInfo;
 * GRAPH_InsertEdge(G,pOrigen,pDestino,pInfo);
 *
 * Descripción: Crea una nueva arco entre el vertice
 *			apuntado por pOrigen y el apuntado por
 *			pDestino; insertando la nueva arco en la
 *			lista de adyancencia del vertice origen
 */
void GRAPH_InsertEdge(GRAPH *G, GRAPH_Vertex *pOrigen, GRAPH_Vertex *pDestino, int peso, Generic IExtra);

/*
 * Función: GRAPH_RemoveEdge
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pOrigen, *pDestino;
 * GRAPH *G;
 * GRAPH_RemoveEdge(G,pOrigen,pDestino);
 *
 * Descripción: Elimina la arco existente entre el 
 *			vertice apuntado por pOrigen y el apuntado
 *			por pDestino
 */
void GRAPH_RemoveEdge(GRAPH *G, GRAPH_Vertex *pOrigen, GRAPH_Vertex *pDestino);

/*
 * Función: GRAPH_isEmpty
 * --------------------------
 * Modo de uso:
 * int resp;
 * GRAPH *G;
 * resp = GRAPH_isEmpty(G);
 *
 * Descripción: Verifica si el Grafo tiene vertices o no.
 */
int GRAPH_isEmpty(GRAPH *G);

/*
 * Función: GRAPH_Vertex_areAdjacent
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *Vo, *V;
 * GRAPH_Edge *arco;
 * arco = GRAPH_Vertex_areAdjacent(Vo, V);
 *
 * Descripción: Verifica que dos Vertices sean adyacentes.
 *			Si lo son retorna la arco que los une, caso
 *			contrario retorna NULL
 */
GRAPH_Edge *GRAPH_Vertex_areAdjacent(GRAPH_Vertex *Vo, GRAPH_Vertex *V);

/*
 * Función: GRAPH_Edge_CmpXVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *V;
 * GRAPH_Edge *ar;
 * int resp;
 * resp = GRAPH_Edge_CmpXVertex(ar, V);
 *
 * Descripción: Verifica si el vertice destino del 
 *			arco ar es igual al vertice V. Si son
 *			iguales retorna 0, en caso contrario 1.
 */
int GRAPH_Edge_CmpXVertex(GRAPH_Edge *ar, GRAPH_Vertex *V);

/*
 * Función: GRAPH_GetNoVertices
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * int resp;
 * resp = GRAPH_GetNoVertices(G);
 *
 * Descripción: Retorna el número de vertices que
 *			forman parte del grafo G
 */
int GRAPH_GetNoVertices(GRAPH *G);

/*
 * Función: GRAPH_GetNoEdges
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * int resp;
 * resp = GRAPH_GetNoEdges(G);
 * Descripción: Retorna el número total de arcos
 *			que	forman parte del grafo G
 */
int GRAPH_GetNoEdges(GRAPH *G);


/*
 * Función: GRAPH_Vertex_Compare
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *V1, *V2;
 * int resp;
 * resp = GRAPH_Vertex_Compare(V1,V2);
 *
 * Descripción: Verifica si V1 y V2 referencian al
 *			mismo vertice. Si lo hacen retorna 0,
 *			caso contrario retorna 1.
 */
int GRAPH_Vertex_Compare(GRAPH_Vertex *V1, GRAPH_Vertex *V2);

/*
 * Función: GRAPH_SearchVertex
 * --------------------------
 * Modo de uso:
 * GRAPH_Vertex *pBuscado;
 * Generico cont;
 * GRAPH *G;
 * pBuscado = GRAPH_SearchVertex(G,cont,Funcion_Comparacion);
 *
 * Descripción: Busca en el grafo G un vertice cuyo
 *			contenido sea igual (segun la Funcion_Comparacion)
 *			al contenido pasado como argumento. Retorna la
 *			referencia al vertice si este existe, y si no
 *			retorna NULL
 */
GRAPH_Vertex *GRAPH_SearchVertex(GRAPH *G, Generic cont, cmpfn fn);

/*
 * Función: GRAPH_Initiate
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Initiate(G);
 *
 * Descripción: Marca todos los vértices de un grafo
 *			como no visitados.
 */
void GRAPH_Initiate(GRAPH *G);

/*
 * Función: GRAPH_GetDeepPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_GetDeepPath(G,Vo)
 * Descripción: Recorre en profundidad los vértices de
 *			un grafo, partiendo del vértice Vo, retornando
 *			una lista en el orden del recorrido.
 */
List *GRAPH_GetDeepPath(GRAPH *G, GRAPH_Vertex *Vo);

/*
 * Función: GRAPH_ShowDeepPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_ShowDeepPath(G,Vo,f)
 * Descripción: Recorre en profundidad los vértices de
 *			un grafo, partiendo del vértice Vo, ejecutando
 *			la función de impresión f para cada vértice en
 *			el orden del recorrido.
 */
void GRAPH_ShowDeepPath(GRAPH *G, GRAPH_Vertex *Vo, GRAPH_Print f);

/*
 * Función: GRAPH_GetWidthPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_GetWidthPath(G,Vo)
 * Descripción: Recorre en anchura los vértices de
 *			un grafo, partiendo del vértice Vo, retornando
 *			una lista en el orden del recorrido.
 */
List *GRAPH_GetWidthPath(GRAPH *G, GRAPH_Vertex *Vo);

/*
 * Función: GRAPH_ShowDeepPath
 * --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vo;
 * List *L;
 *
 * L = GRAPH_ShowDeepPath(G,Vo,f)
 * Descripción: Recorre en anchura los vértices de
 *			un grafo, partiendo del vértice Vo, ejecutando
 *			la función de impresión f para cada vértice en
 *			el orden del recorrido.
 */
void GRAPH_ShowWidthPath(GRAPH *G, GRAPH_Vertex *Vo, GRAPH_Print f);

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


 /* --------------------------
 * Modo de uso:
 * GRAPH *G;
 * GRAPH_Vertex *Vorig;
 *int *DistanciasMenores
 *
 * DistanciasMenores = GRAPH_Diskstra(G,Vo,f)
 * Descripción: RETORNA LA EXENTRICIDAD DE UNN VERTICE V.
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
 * Descripción: RETORNA LA EXENTRICIDAD DE UNN VERTICE V.
 *              La exentricidad de un vertice
 */
GRAPH_Vertex *GRAPH_GetCenter(GRAPH *G);

void Iniciar_VectorDistancias(int *Dist,GRAPH_Vertex *V,int tam,GRAPH *G);

GRAPH_Vertex *EscogerVerticeMenor(int *Dist, GRAPH *G,int tam);

void Modificar_Distancias(int *Dist,GRAPH_Vertex *Vk,int tam,GRAPH *G);


int Vertice_CmpXNom(GRAPH_Vertex *V, char *nombre);

int Vertice_CmpXCodCom(GRAPH_Vertex *V, char *codcom);

#endif