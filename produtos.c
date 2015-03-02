#include <stdio.h>
#include <stdlib.h>
#include "produtos.h"
#include <string.h>

Produtos * inserir (Produtos * p, char * n){
	if (p == NULL) {
		p = (Produtos *) malloc(sizeof(struct produtos));
		strcpy(p->nome, n);
		p->dir = NULL;
		p->esq = NULL;
	}
	else if (strcmp(p->nome, n) > 0) {
		p->esq = inserir(p->esq, n);
	}
	else p->dir = inserir(p->dir, n);
	return p;
}

void print(Produtos * p){
	if (p != NULL) {
		printf("%s\n",p->nome);
		print(p->esq);
		print(p->dir);
	}
}