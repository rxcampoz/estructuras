#include "generic_string.h"
#include <string.h>
#include <stdlib.h>

char * String_Crear(char *valor){
	char *nuevo;
	nuevo = malloc(sizeof(char)*strlen(valor)+1);
	strcpy(nuevo,valor);
	return nuevo;
}
char *String_Get(char *s){
	return s;
}
void String_Set(char *s, char *valor){
	strcpy(s, valor);
}
void String_Print(char *s){
	printf("%s\n", s);
}
char *String_Leer(){
	char s[1000], *nuevo;
	scanf("%s", s);
	nuevo = String_Crear(s);
	return nuevo;
}
