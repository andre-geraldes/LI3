#ifndef LLIGADA_H
#define LLIGADA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int comprimentoListaLigada(ListaLigada l);

#endif
