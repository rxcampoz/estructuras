/*************************************************************
**		ESCUELA SUPERIOR POLITECNICA DEL LITORAL			**
**						ESPOL								**
**	FACULTAD DE INGENIERIA EN ELECTRONICA Y COMPUTACION		**
**						FIEC								**
**				Fundamentos de Programacion					**
**		Desarrollo del proyecto del primer parcial			**
**				 	MONOPOLIO 1.0							**
**	Autor:	Ricardo Xavier Campozano Vascones		    	**
**	Paralelo:	008											**
**	FECHA DE ULTIMA MODIFICACION: 09/12/2008				**
**************************************************************
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

/*En esta parte declaramos las funciones y procedimientos
a invocarse en el programa*/

#define MAX 40			//tamaño del tablero
void generar(int arreglo[],int tam);
int obtener_casilla(int arreglo[],int tam); 
void mostrar(int arreglo[],int tam);
int lanzar_dado();
int obtener_jugada(int pos);
void mostrar_jugada(int jug,int casilla);
int pago_o_cobro(int posicion,int tipo);
int avanza_o_retrocede(int posicion,int tipo);
int esta_en_la_carcel(int tipo);
int finaliza(int banco,int turnos,int opcion);


void main(){							//declaraciones de variables a usar dentro del main
	int tablero[MAX],p1[MAX],p2[MAX],din_p2=100;
	int i,avance1=0,avance2=0,din_p1=100,jugada,jug,ronda=1,fin=0,dado,carcel1=0,carcel2=0;

	char op;

	srand(time(NULL));

	for(i=0; i<MAX ; i++)  //inicializamos el tablero en 0
		tablero[i]=0;
		
	generar(tablero,MAX);

	printf("\t\t\t\t*************\n\t\t\t\t*Bienvenidos*\n\t\t\t\t*************\n");
	printf("\t\t\t\t *MONOPOLIO*\n\n");

	do{
		mostrar(tablero,MAX);

		printf("\n\nRONDA %d\n",ronda);    //ronda es el numero de lanzamientos que realizan los jugadores
		printf("\n\nPlayer 1\tPresione cualquier tecla para lanzar los dados\n");  //jugador 1
		op=getch();
		if(op!=27){     //si el jugador presiona la tecla esc sale del programa
			
			if(carcel1<1){
				dado=lanzar_dado();				//lanza los dados
				avance1=avance1 + dado;			//el jugador avanza segun el resultado del dado
				printf("el resultado fue %d\n",dado);			//imprime el resultado del dado
				if(avance1>39){					//si el jugador avanza mas de 39 (limite del arreglo) continua desde 0 y se incrementa el saldo en 100
					avance1=avance1%39;
					din_p1+=100;
				}

				jug=tablero[avance1];			//jug contiene el resultado de la casilla donde cayo el jugador
				jugada=obtener_jugada(jug);     //jugada determina el tipo de jugada
				mostrar_jugada(jugada,jug);		//muestra al jugador el contenido de la casilla y el tipo de jugada
				getch();
				
				carcel1=esta_en_la_carcel(jugada);   //si cae en la carcel entonces carcel=2(numero de turnos que perdera)
				if(carcel1==2)
					din_p1-=100;					//disminuye el saldo en 100

				din_p1=din_p1+pago_o_cobro(jug,jugada);			//aumenta o disminuye el saldo 
				avance1=avance1 +avanza_o_retrocede(jug,jugada);		//avanza o retrocede segun sea la jugada
				
				if(avance1>39){						//valida el avance para que si sobrepasa el limite del arreglo continue desde el inicio
					avance1=avance1%40;
					din_p1+=100;					//al pasar por inicio aumenta el saldo en 100
				}
				if(avance1<0)						//si retrocede antes del inicio, el jugador se queda en el inicio 
					avance1=0;
				}
			else{
				printf("el resultado fue 0\n");		//si esta en la carcel se lo sanciona con lanzamientos en cero
				carcel1--;
			}
			printf("player 1 en %d\n",avance1);		//muestra la posicion del jugador luego de la ultima jugada
			printf("saldo player 1= %d\n",din_p1);	//muestra el saldo
			fin=finaliza(din_p1,ronda,op);			//verifica las condiciones que finalizan el juego

			//jugador 2

			if(fin!=1){				// si el jugador 1 presiono esc en ese instante finaliza el juego
				printf("\n\nPlayer 2\tPresione cualquier tecla para lanzar los dados\n");
				op=getch();
				if(op!=27){

					if(carcel2<1){
						dado=lanzar_dado();
						avance2=avance2 + dado;
						printf("el resultado fue %d\n",dado);
						
						if(avance2>39){
							avance2=avance2%40;
							din_p2+=100;
						}

						jug=tablero[avance2];
						jugada=obtener_jugada(jug);
						mostrar_jugada(jugada,jug);
						getch();

						carcel2=esta_en_la_carcel(jugada);
							if(carcel2==2)
								din_p2-=100;

						din_p2=din_p2+pago_o_cobro(jug,jugada);
						avance2=avance2 +avanza_o_retrocede(jug,jugada);
						
						if(avance2>39){
							avance2=avance2%40;
							din_p2+=100;
						}
						if(avance2<0)
							avance2=0;
					}
					else{
						printf("el resultado fue 0\n");
						carcel2--;
					}

					printf("player 2 en %d\n",avance2);
					printf("saldo player 2= %d\n",din_p2);
					fin=finaliza(din_p2,ronda,op);
				}

			}
		}
		ronda++;   //aumenta la cantidad de lanzamientos que han realizado los jugadores
		if(op==27) //si un jugador presiona esc al momento de lanzar los dados el juego termina 
			fin=1;
		if(ronda>20) //si ambos jugadores realizan mas de 20 lanzamientos el juego termina
			fin=1;
		getch();
	}while(fin==0);   //el juego continua si ninguna de las condiciones que lo finalizan se cumplen


	printf("\n\tGAME OVER\nGRACIAS POR JUGAR MONOPOLIO");			//mensaje de despedida
	getch();
}  //FIN DEL JUEGO


/***********************************************************
 *Implementacion de funciones y procedimientos a utilizarse*
 ***********************************************************/

void generar(int arreglo[],int tam){	//llena el arreglo con numeros aleatorios
	int libre,i;

	libre = obtener_casilla(arreglo,tam);  //Obtiene una casilla que no haya sido llenada antes
	arreglo[libre]=999;	 //creamos la carcel

	for(i=1;i<=9;i++){		//casillas de avance del 1 al 39
		libre=obtener_casilla(arreglo,tam);
		arreglo[libre]=1+rand()%39;
	}

	for(i=1;i<=9;i++){		//casillas de retroceso del -1 al -39
		libre=obtener_casilla(arreglo,tam);
		arreglo[libre]=-39+rand()%39;
	}

	for(i=1;i<=10;i++){		//casillas de pago del 41 al 200
		libre=obtener_casilla(arreglo,tam);
		arreglo[libre]=41+rand()%160;
	}

	for(i=1;i<=10;i++){		//casillas de avance del -41 al -200
		libre=obtener_casilla(arreglo,tam);
		arreglo[libre]=-200+rand()%160;
	}
}
int obtener_casilla(int arreglo[],int tam){  // verifica que la casilla a llenar este vacia
	int libre=0,casilla;

	do{
		casilla=1+rand()%39; //el inicio es la unica casilla que toma el valor de cero
		if(arreglo[casilla]==0) 
			libre=1;
	}while(libre==0);

	return casilla;		//devuelve la casilla libre
}

void mostrar(int arreglo[],int tam){  //muestra el arreglo como un cuadro de 5 x 8
	int i;
		
	for(i=0; i<tam ; i++){
		if(i%5==0)
			printf("\n");
		printf("%4d\t",arreglo[i]);
	}
}



int lanzar_dado(){  //simula el lanzamiento de 2 dados
	int res_dado;  //el resultado de lanzar los dados puede ser del 2 al 12

	res_dado=2+rand()%12;
	return res_dado;		//retorna un numero del 2 al 12
}

int obtener_jugada(int pos){		//obtiene el tipo de jugada 

	if(pos>=1 && pos<=39) //jugada avance
		return 1; 

	if(pos>=-39 && pos<=-1) //jugada retroceso
		return 2;

	if(pos==999) //jugada carcel
		return 3;

	if(pos>=41 && pos<=200) //jugada cobro
		return 4;

	if(pos>=-200 && pos<=-41) //jugada pago
		return 5;

}

void mostrar_jugada(int jug,int casilla){  //muestra al jugador el contenido de la casilla donde cayo y la jugada correspondiente
	
	switch(jug){ //jug es el tipo de jugada que se obtuvo el la funcion obtener_jugada
		case 1: printf("contenido casilla: %d\t Usted avanza %d\n",casilla,casilla);break;
		case 2: printf("contenido casilla: %d\t Usted retrocede %d\n",casilla,casilla);break;
		case 3: printf("contenido casilla: %d\t Usted ha caido en la carcel: pierde dos turnos y 100 monedas\n",casilla);break;
		case 4: printf("contenido casilla: %d\t Usted cobra %d monedas\n",casilla,casilla);break;
		case 5: printf("contenido casilla: %d\t Usted paga %d monedas\n",casilla,casilla*-1);break;
	}
}

//TIPOS DE JUGADA

int pago_o_cobro(int posicion,int tipo){  //si el jugador cae en pago o cobro se le suma el valor de la casilla a su saldo
	if(tipo==4 || tipo==5 )
		return posicion;
	
	else
		return 0;
}

int avanza_o_retrocede(int posicion,int tipo){ //si cae en estos tipos de jugadas, a la posicion del jugador se le suma el resultado de la casilla
	if(tipo==1 || tipo==2)						
		return posicion;
	else
		return 0;
}

int esta_en_la_carcel(int tipo){  //verifica si el jugador esta o no en la carcel
	if(tipo==3)			//carcel es el 3 tipo de jugada
		return 2;		//numero de lanzamientos en cero
	else 
		return 0;
}
int finaliza(int banco,int turnos,int opcion){		//estas son las condiciones que hacen que el programa finalize
	if(banco>0 && turnos<21 && opcion!=27) 
		return 0;
	else			//si el jugador se queda sin dinero, si se pasan de 20 turnos o si presionan esc al lanzar los dados entonces:
		return 1;	//el programa finaliza
}


