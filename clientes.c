#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include <string.h>

Clientes * inserir (Clientes * c, char * n){
	if (c == NULL) {
		c = (Clientes *) malloc(sizeof(struct clientes));
		strcpy(c->nome, n);
		c->dir = NULL;
		c->esq = NULL;
	}
	else if (strcmp(c->nome, n) > 0) {
		c->esq = inserir(c->esq, n);
	}
	else c->dir = inserir(c->dir, n);
	return c;
}

void print(Clientes * c){
	if (c != NULL) {
		printf("%s\n",c->nome);
		print(c->esq);
		print(c->dir);
	}
}

int main () {
	Clientes * n[26];
	n[0] = inserir(n[0], "Arroz");
	n[0] = inserir(n[0], "Az");
	n[0] = inserir(n[0], "Ab");
	n[0] = inserir(n[0], "Arroz");
	n[0] = inserir(n[0], "Az");
	n[0] = inserir(n[0], "Ab");
	p
	print(n[0]);
	return 0;
}
