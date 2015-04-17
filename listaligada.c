#include"listaligada.h"

/**
 * Inicia a lista ligada
 * @param l
 * @param c
 * @return 
 */
ListaLigada initLista(ListaLigada l, char *c) {
    if(l==NULL){
        l = (ListaLigada) malloc(sizeof(struct listaligada));
        strcpy(l->codigo,c);
        l->ant = l->prox = NULL;
    }
    return l;
}

/**
 * Insere elemento na lista ligada
 * @param l
 * @param c
 * @return 
 */
ListaLigada insereElemento(ListaLigada l, char *c) {
    if(l==NULL) {
        l = initLista(l,c);
    } else {
        ListaLigada novo;
        novo = (ListaLigada) malloc(sizeof(struct listaligada));
        strcpy(novo->codigo,c);
        novo->prox = l;
        novo->ant = NULL;
        l->ant = novo;
        l = novo;
    }
    
    return l;
}

/**
 * Passa de uma árvore para uma lista em INORDER
 * »CLIENTES
 * @param l
 * @param c
 * @return 
 */
ListaLigada clientesParaLista(ListaLigada l, NodoC c) {
    if(c!=NULL) {
        l = clientesParaLista(l,c->esq);
        l = insereElemento(l,c->nome);
        l = clientesParaLista(l,c->dir);
    }
    return l;
}

/**
 * Passa de uma árvore para uma lista em INORDER
 * »PRODUTOS
 * @param l
 * @param c
 * @return 
 */
ListaLigada produtosParaLista(ListaLigada l, NodoP c) {
    if(c!=NULL) {
        l = produtosParaLista(l,c->esq);
        l = insereElemento(l,c->nome);
        l = produtosParaLista(l,c->dir);
    }
    return l;
}

