/**************************************************************
**		ESCUELA SUPERIOR POLITECNICA DEL LITORAL			 **
**						ESPOL								 **
**	FACULTAD DE INGENIERIA EN ELECTRONICA Y COMPUTACION		 **
**						FIEC								 **
**				Estructuras de Datos						 **
**		Desarrollo del proyecto del primer parcial			 **
**				 	MODULO IA(El Robot)						 **
**	Autores:	Ricardo Xavier Campozano Vascones			 **
**				Steven Caicedo M							 **
**				Freddy Lituma P					    		 **
**	Paralelo:	002											 **
**	FECHA DE ULTIMA MODIFICACION: 08/12/2009				 **
***************************************************************
**************************************************************/

//Importamos las librerias a usar
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "listas.h"
#include "generico.h"
#include "Stack.h"

//Constante que indica el tamaño del mundo: mundo es una matriz de TAM filas y TAM columnas 
#define TAM 10

//creamos la estructura mov que tendra coordenada x, coordenada y un angulo. Este angulo es un numero entero
//del 0 al 7 y representa la orientacion del robot(0:este  1:noreste  2:norte  etc.)  
//Esta estructura define al tipo de dato movimiento
typedef struct mov{
	int x;
	int y;
	int angle;
}movimiento;


/*En esta parte declaramos las funciones y procedimientos
a invocarse en el programa*/

Generic nuevoMov(movimiento m);
void imprimir(movimiento *r);
void girar(movimiento *m);
void desplazar(movimiento *m);
void imprimirMundo(movimiento m,int mundo[][TAM]);
movimiento vueltaBase(List *L);
void movimientoRealizado(Generic g,List *L);
void inicializarMundo(int m[][TAM]);
void insertarObstaculos(int m[][TAM]);

//PROGRAMA PRINCIPAL

void main(){
	int mundo[TAM][TAM];
	char op;		//op sera la variable centinela que permitira la finalizacion del programa
	Stack *S;		//Definimos una pila S
	movimiento r;	//variable r que representa nuestro robot de tipo movimiento
	Generic g;		//Generico g sera un puntero que apunte a nuestros datos en este caso la estructura mov
	
	S=Stack_New();	//Creamos la pila
	
	srand(time(NULL));		//Introducimos la semilla
	inicializarMundo(mundo);	//Inicializamos el mundo con 0
	insertarObstaculos(mundo);	//Insertamos Obstaculos que estaran representados por un 1
	r.x=0;		//Nuestro robot partira de una posicion base que considera totalmente segura
	r.y=0;
	r.angle=0;
	imprimirMundo(r,mundo);	//Mostramos nuestro robot en pantalla
	printf("MODULO IA INICIADO\n");
	getch();
	g=nuevoMov(r);
	Stack_Push(S,NodeList_New(g));	//Introducimos nuestra primera posicion base en la pila de movimientos

	do{
		r=*(movimiento*)NodeList_GetContent(Stack_Top(S)); //Obtenemos el ultimo movimiento realizado
		girar(&r);			//Giramos nuestro robot
		desplazar(&r);		//Ordena desplazar siempre y cuando sea esto posible 

		g=nuevoMov(r);		//Generico aapunta a nuestro nuevo movimiento
		movimientoRealizado(g,S);  //Insertamos el movimiento en nuestra pila de movimientos
		
		system("cls");
		imprimirMundo(r,mundo);
		if(mundo[r.x][r.y]==1){		//Si nuestro robot determina que la posicion es peligrosa pues hay un obstaculo
			r=vueltaBase(S);		//Entonces el robot regresa a ultima posicion segura
			printf("He encontrado un obstaculo, regreso a la ultima posicion base\n");
			getch();
			system("cls");
			imprimirMundo(r,mundo);
		}
		printf("Presione S para salir,cualquier tecla para continuar"); //Usuario puede terminar la exploracion pulsando la tecla s
		scanf("%c",&op);
	}while(op!='s');

	printf("MODULO IA FINALIZADO\n Mostrando pila de movimientos realizados\n"); //Muestra todos los movimientos realizados
	List_Print(S,imprimir);			//Funcion que imprime la pila de movimientos
	getch();
}

Generic nuevoMov(movimiento m){  
	movimiento *nr;		//Creamos un puntero de tipo movimiento
	nr=(movimiento *)malloc(sizeof(movimiento)); //Asignamos memoria
	nr->x=m.x;			//Asignamos valores
	nr->y=m.y;
	nr->angle=m.angle;
	
	return nr;		//retorna el puntero de tipo movimiento
}


void inicializarMundo(int m[][TAM]){ //Inicializa la matriz en cero
	int i,j;
	for(i=0;i<TAM;i++){
		for(j=0;j<TAM;j++)
			m[i][j]=0;
	}

}

void insertarObstaculos(int m[][TAM]){//Inserta los obstaculos representados por un 1
	int i,j,k;
	for(k=0;k<30;k++){
		i=rand()%TAM;
		j=rand()%TAM;
		m[i][j]=1;
	}
}

void imprimir(movimiento *r){
	printf("\ncoordenadas:   x: %d,  y: %d,    Orientacion: %d--->",r->x,r->y,r->angle);

}

void girar(movimiento *m){
	int angulo=-180+rand()%360;		//Especificamos el angulo que puede ser de -180 a 180
	int tA=angulo/45;		//Determinamos que tipo de orientacion corresponde al angulo dado 
	printf("giro %d grados\n",angulo);
	
	if(tA<0)	tA=8+tA;	//Determinamos el tipo de orientacion de los angulos negativos
	
	getch();
	switch(tA){		//el giro es en base a nuestra Orientacion actual ej: robot mira hacia el noreste,robot gira 180,luego de esto robot mirara hacia el suroeste
		case 0:printf("Orientacion actual: %d\n",m->angle);break;
		case 1:m->angle=(m->angle)+1;
			if(m->angle>7) m->angle=m->angle%8;
			printf("Orientacion actual: %d\n",m->angle);
			break;
		case 2:m->angle=(m->angle)+2;
			if(m->angle>7) m->angle=m->angle%8;
			printf("Orientacion actual: %d\n",m->angle);
			break;
		case 3:m->angle=(m->angle)+3;
			if(m->angle>7) m->angle=m->angle%8;
			printf("Orientacion actual: %d\n",m->angle);
			break;
		case 4:m->angle=(m->angle)+4;
			if(m->angle>7) m->angle=m->angle%8;
			printf("Orientacion actual: %d\n",m->angle);
			break;
		case 5:m->angle=(m->angle)+5;
			if(m->angle>7) m->angle=m->angle%8;
			printf("Orientacion actual: %d\n",m->angle);
			break;
		case 6:m->angle=(m->angle)+6;
			if(m->angle>7) m->angle=m->angle%8;
			printf("Orientacion actual: %d\n",m->angle);
			break;
		case 7:m->angle=(m->angle+7);
			if(m->angle>7) m->angle=m->angle%8;
			printf("Orientacion actual: %d\n",m->angle);
			break;
	}
}

void desplazar(movimiento *m){ //Ordena desplazar siempre y cuando sea esto posible 
	int metros=-TAM+rand()%(TAM*2);	//Especificamos distancia
	switch(m->angle){	//el robot avanza en base a su orientacion actual ej: robot mira hacia el norte, avanza -4,luego de esto robot se habra desplazado 4 posiciones hacia el sur
		case 0:if((m->x+metros)<TAM  &&(m->x+metros)>=0){	//el desplazamiento es posible si no desborda al mundo
				   m->x=m->x+metros;
					printf("Avanzo %d metros hacia el este\n",metros);
			   }break;
		case 1:if((m->x+metros)<TAM  &&(m->x+metros)>=0  &&(m->y-metros)<TAM &&(m->y-metros)>=0){
				   m->x=m->x+metros;
				   m->y=m->y-metros;
				   printf("Avanzo %d metros hacia el noreste\n",metros);
			   }break;
		case 2:if((m->y-metros)<TAM  &&(m->y-metros)>=0 ){
				   m->y=m->y-metros;
				   printf("Avanzo %d metros hacia el norte\n",metros);
			   }break;
		case 3:if((m->x-metros)<TAM  &&(m->x-metros)>=0  &&(m->y-metros)<TAM &&(m->y-metros)>=0){
				   m->x=m->x-metros;
				   m->y=m->y-metros;
				   printf("Avanzo %d metros hacia el noroeste",metros);
			   }break;
		case 4:if((m->x-metros)<TAM  &&(m->x-metros)>=0){
				   m->x=m->x-metros;
				   printf("Avanzo %d metros hacia el oeste",metros);
			   }break;
		case 5:if((m->x-metros)<TAM  &&(m->x-metros)>=0  &&(m->y+metros)<TAM &&(m->y+metros)>=0){
				   m->x=m->x-metros;
				   m->y=m->y+metros;
				   printf("Avanzo %d metros hacia el suroeste",metros);
			   }break;
		case 6:if((m->y+metros)<TAM &&(m->y+metros)>=0){
				   m->y=m->y+metros; 
				   printf("Avanzo %d metros hacia el sur",metros);
			   }break;
		case 7:if((m->x+metros)<TAM  &&(m->x+metros)>=0  &&(m->y+metros)<TAM &&(m->y+metros)>=0){
				   m->x=m->x+metros;
				   m->y=m->y+metros;
				   printf("Avanzo %d metros hacia el sureste",metros);
			   }break;
	}
	getch();
}

void imprimirMundo(movimiento m,int mundo[][TAM]){	//imprime el mundo como una matriz de TAM x TAM
	int i,j;

	for(i=0;i<TAM;i++){		//i representa filas
		for(j=0;j<TAM;j++){
			if(j==m.x && i==m.y)//j representa columnas
				printf(" %c ",1);		//en la posicion donde se encuentre el robot imprimira una carita feliz
			else
				printf(" %d ",mundo[j][i]);	//Muestra el contenido de la posicion(x,y) donde eje x son las columnas i 
		}
		printf("\n");
j
}

movimiento vueltaBase(Stack *S){	//Devuelve el ultimo movimiento considerado seguro
	movimiento m;
	Stack_Pop(S);			//Pop elimino el movimiento peligroso
	m=*(movimiento*)NodeList_GetContent(Stack_Top(S));//m sera el movimiento anterior a m peligroso (TOP)
	return m;	//retorno m de tipo movimiento 
}

void movimientoRealizado(Generic g,Stack *S){//Inserta en una pila el ultimo movimiento realizado
	Stack_Push(S, NodeList_New(g));		//Push
}