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

void printC(Clientes * c){
	if (c != NULL) {
		printf("%s\n",c->nome);
		printC(c->esq);
		printC(c->dir);
	}
}

/*int main () {
	Clientes * n[26];
	n[0] = inserir(n[0], "Arroz");
	n[0] = inserir(n[0], "Az");
	print(n[0]);
	return 0;
}
*/
