#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo
{
	char valor[7];
	struct nodo *esq;
	struct nodo *dir;
	int altura;
} * NodoC;

int alturaC(NodoC N);

int maxC(int a, int b);

NodoC novonodoC(char * valor);

NodoC dirRotateC(NodoC y);

NodoC esqRotateC(NodoC x);

int getBalanceC(NodoC N);

NodoC insertC(NodoC nodo, char * valor);

int contaNodosC(NodoC avl);

void listarC(NodoC n, int l, int c, char lista[l][c], int *i);

int existeC(NodoC n, char * nom);
