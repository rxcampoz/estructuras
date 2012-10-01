#include "nodos.h"

NodeList *NodeList_New(Generic G){
	NodeList *p;
    p = (NodeList *)malloc(sizeof(NodeList));
    if(p)
    {
        p->G = G;
        p->next = NULL;
    }
    return  p;
}

void NodeList_Delete(NodeList **p){
	if(*p)
	{
		free(*p);
		*p = NULL;
	}
}

void NodeList_SetContent(NodeList *p, Generic G){
	if(p)
		p->G = G;
}

void NodeList_SetNext(NodeList *p, NodeList *Sig){
	if(p)
		p->next = Sig;
}

Generic NodeList_GetContent(NodeList *p){
	if(p) return p->G;
	else return NULL;
}

NodeList *NodeList_GetNext(NodeList *p){
	if(p) return p->next;
	else return NULL;
}
