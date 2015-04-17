#ifndef CONTABILIDADE_H
#define CONTABILIDADE_H

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

void imprimeModo(Modo m);

void imprimeContabilidade(Contabilidade c);

/* Gestão da AVL */

int altura(Contabilidade nodo);

int fator (Contabilidade nodo);

Contabilidade rotacao_dir_dir(Contabilidade pai);

Contabilidade rotacao_esq_esq(Contabilidade pai);

Contabilidade rotacao_dir_esq(Contabilidade  pai);

Contabilidade rotacao_esq_dir(Contabilidade  pai);

Contabilidade balancear(Contabilidade nodo);

#endif