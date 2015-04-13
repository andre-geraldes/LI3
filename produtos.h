#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodop
{
	char valor[8];
	struct nodop *esq;
	struct nodop *dir;
	int altura;
} * NodoP;


int alturaP(NodoP N);

NodoP novoNodoP(char * valor);

NodoP dirRotateP(NodoP y);
 
NodoP esqRotateP(NodoP x);

int getBalanceP(NodoP N);
 
NodoP insertP(NodoP nodo, char * valor);

int contaNodosP(NodoP avl);

void listarP(NodoP n, int l, int c, char lista[l][c], int *i);

int existeP(NodoP n, char * nom);
