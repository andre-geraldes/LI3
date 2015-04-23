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

ListaLigada insereNaoRepetido(ListaLigada l, char *c) {
    int encontrou = 0;
    ListaLigada aux = l;
    if(l == NULL){
        l = initLista(l,c);
    } else {
        while(aux && !encontrou){
            if(strcmp(aux->codigo,c) == 0) encontrou = 1;
            aux = aux->prox;
        }
        if(!encontrou){
            l = insereElemento(l,c);
        }
    }
    return l;
}

int comprimentoListaLigada(ListaLigada l) {
    int c = 0;
    while(l != NULL){
        c++;
        l = l->prox;
    }
    return c;
}
