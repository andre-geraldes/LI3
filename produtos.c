#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include <string.h>

Produtos * addProduto (Produtos * p, char * n){
	if (p == NULL) {
		p = (Produtos *) malloc(sizeof(struct produtos));
		strcpy(p->nome, n);
		p->dir = NULL;
		p->esq = NULL;
	}
	else if (strcmp(p->nome, n) > 0) {
		p->esq = addProduto(p->esq, n);
	}
	else p->dir = addProduto(p->dir, n);
	return p;
}

void printP(Produtos * p){
	if (p != NULL) {
		printf("%s\n",p->nome);
		printP(p->esq);
		printP(p->dir);
	}
}
