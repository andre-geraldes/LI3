#ifndef CONTABILIDADE_H
#define CONTABILIDADE_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct modo {
    int nvendas;
    double facturado;
} *Modo;

typedef struct contabilidade {
    char produto[7];
    Modo normal;
    Modo promocao;
    struct contabilidade *esq,*dir;
} *Contabilidade;

Modo initModo(Modo m);

Contabilidade initContabilidade(Contabilidade c, char *p);

Contabilidade inserirContabilidade(Contabilidade c, char *p);

Contabilidade actualizaContabilidade(Contabilidade c, char *p, char m, double pr, int q);

int produtoFoiComprado(Contabilidade c, char *p);

void numeroVendasETotalFacturado(Contabilidade c, int *v, double *f);

void imprimeModo(Modo m);

void imprimeContabilidade(Contabilidade c);

/* Gestão da AVL */

int alturaCT(Contabilidade nodo);

int fatorCT(Contabilidade nodo);

Contabilidade rotacao_dir_dirCT(Contabilidade pai);

Contabilidade rotacao_esq_esqCT(Contabilidade pai);

Contabilidade rotacao_dir_esqCT(Contabilidade  pai);

Contabilidade rotacao_esq_dirCT(Contabilidade  pai);

Contabilidade balancearCT(Contabilidade nodo);

#endif
