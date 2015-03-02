#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include <string.h>

Clientes * addCliente (Clientes * c, char * n){
	if (c == NULL) {
		c = (Clientes *) malloc(sizeof(struct clientes));
		strcpy(c->nome, n);
		c->dir = NULL;
		c->esq = NULL;
	}
	else if (strcmp(c->nome, n) > 0) {
		c->esq = addCliente(c->esq, n);
	}
	else c->dir = addCliente(c->dir, n);
	return c;
}

int existeCliente (Clientes *c, char * n){
	int bool = 0;
	if (c == NULL){
		
	}
	else if (strcmp(c->nome, n) == 0){
		bool = 1;
	}
	else if (strcmp(c->nome, n) > 0) {
		bool = existeCliente(c->esq, n);
	}
	else bool = existeCliente(c->dir, n);
	return bool;
}

void printC(Clientes * c){
	if (c != NULL) {
		printf("%s\n",c->nome);
		printC(c->esq);
		printC(c->dir);
	}
}

/*
	Clientes * n[26];
	n[0] = inserir(n[0], "Arroz");
	print(n[0]);
*/
