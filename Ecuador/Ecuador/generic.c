#include "generic.h"
#include <stdlib.h>

void Generic_Delete(Generic *G){
	free(*G);
	*G = NULL;
}

void Generic_Interchange(Generic *G, Generic *G2){
	Generic tmp;
	tmp = *G;
	*G = *G2;
	*G2 = tmp;
}
