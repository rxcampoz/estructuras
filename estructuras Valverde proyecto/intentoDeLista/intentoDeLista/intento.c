#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "generico.h"
#include "listas.h"

typedef struct persona{
	int x;
	int y;
	int z;
	
}tpersona;

Generic nuevaPersona(tpersona p);
void imprimir(tpersona *p);
void inicializarMundo(int A[][10],int fil,int col);
void girar(tpersona *p);

void main(){
	List *L;
	tpersona p,q;
	int mundo[10][10];
	int i,x,y,z;
	

	Generic g,j;
	L=List_New();

	inicializarMundo(mundo,10,10);

	for(i=0;i<3;i++){
		printf("Ingrese una coordenada x\n");
		scanf("%d",&x);
		p.x=x;

		printf("Ingrese una coordenada y\n");
		scanf("%d",&y);
		p.y=y;

		p.z=9;
		g=nuevaPersona(p);

		List_InsertHeader(L, NodeList_New(g));
	}
	List_Print(L,imprimir);
	
	
	q=*(tpersona*)NodeList_GetContent(List_GetHeader(L));
	girar(&q);
	g=nuevaPersona(q);
	
	
	List_InsertHeader(L,NodeList_New(g));
	printf("\n");
	
	List_Print(L,imprimir);

	getch();

}
Generic nuevaPersona(tpersona p){
	tpersona *np;
	np=(tpersona *)malloc(sizeof(tpersona));
	np->x=p.x;
	np->y=p.y;
	np->z=p.z;
	return np;
}


void imprimir(tpersona *p){
	printf("coordenadas: %d,%d,%d--->",p->x,p->y,p->z);

}

void inicializarMundo(int A[][10],int fil,int col){
	int i,j,k;

	for(i=0;i<fil;i++){
		for(j=0;j<col;j++)
			A[i][j]=0;
	}
	for(k=0;k<25;k++){
		i=rand()%10;
		j=rand()%10;
		A[i][j]=1;
	}

}

void girar(tpersona *p){
	p->z=3;
}


