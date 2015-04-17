#ifndef COMPRAS_H
#define COMPRAS_H

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

void imprimeListaCompras(ListaCompras l);

void imprimeCompras(Compras c);

/* Gestão da AVL */

int altura(Compras nodo);

int fator (Compras nodo);

Compras rotacao_dir_dir(Compras pai);

Compras rotacao_esq_esq(Compras pai);

Compras rotacao_dir_esq(Compras pai);

Compras rotacao_esq_dir(Compras pai);

Compras balancear(Compras nodo);


#endif