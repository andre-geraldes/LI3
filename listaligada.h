#ifndef LLIGADA_H
#define LLIGADA_H

#include"clientes.h"
#include"produtos.h"

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/**
 * Vai servir para passar as árvores de produtos
 * e clientes para listas duplamente ligadas de
 * modo a que seja mais facil imprimir
 */

typedef struct listaligada {
    char codigo[7];
    struct listaligada *ant,*prox;
} *ListaLigada;

ListaLigada initLista(ListaLigada l, char *c);

ListaLigada insereElemento(ListaLigada l, char *c);

ListaLigada clientesParaLista(ListaLigada l, NodoC c);

ListaLigada produtosParaLista(ListaLigada l, Nodop c);

#endif