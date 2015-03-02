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

int existeProduto (Produtos *p, char * n){
	int bool = 0;
	if (p == NULL){
		
	}
	else if (strcmp(p->nome, n) == 0){
		bool = 1;
	}
	else if (strcmp(p->nome, n) > 0) {
		bool = existeProduto(p->esq, n);
	}
	else bool = existeProduto(p->dir, n);
	return bool;
}

void printP(Produtos * p){
	if (p != NULL) {
		printf("%s\n",p->nome);
		printP(p->esq);
		printP(p->dir);
	}
}
