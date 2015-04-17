#ifndef LLIGADA_H
#define LLIGADA_H

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

ListaLigada clientesParaLista(ListaLigada l, Clientes c);

ListaLigada produtosParaLista(ListaLigada l, Clientes c);

#endif