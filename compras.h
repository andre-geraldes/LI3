#ifndef COMPRAS_H
#define COMPRAS_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct listaCompras {
    char produto[7];
    char modo;
    double preco;
    int quantidade;
    struct listaCompras *prox;
} *ListaCompras;

typedef struct compras {
    char cliente[6];
    ListaCompras lista;
    struct compras *esq,*dir;
} *Compras;

ListaCompras initListaCompras(ListaCompras l, char *p, char m, double pr, int q);

Compras initCompras(Compras c, char *cl, char *p, char m, double pr, int q);

ListaCompras insereElemListaCompras(ListaCompras l, char *p, char m, double pr, int q);

Compras insereCompra(Compras c, char *cl, char *p, char m, double pr, int q);

int comprimentoListaCompras(ListaCompras l);

int clienteComprouProduto(ListaCompras l, char *p);

/* Gestão da AVL */

int alturaCP(Compras nodo);

int fatorCP(Compras nodo);

Compras rotacao_dir_dirCP(Compras pai);

Compras rotacao_esq_esqCP(Compras pai);

Compras rotacao_dir_esqCP(Compras pai);

Compras rotacao_esq_dirCP(Compras pai);

Compras balancearCP(Compras nodo);


#endif
