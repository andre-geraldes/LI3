#include"compras.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/**
 * Inicia a estrutura lista de compras
 * @param l
 * @param p
 * @param pr
 * @param q
 * @return 
 */
ListaCompras initListaCompras(ListaCompras l, char *p, char m, double pr, int q) {
    if(l==NULL){
        l = (ListaCompras) malloc(sizeof(struct listaCompras));
        strcpy(l->produto,p);
        l->modo=m;
        l->preco = pr;
        l->quantidade = q;
        l->prox = NULL;
    }
    return l;
}

/**
 * Inicia estrutura compras
 * @param c
 * @param p
 * @param pr
 * @param q
 * @return 
 */
Compras initCompras(Compras c, char *cl, char *p, char m, double pr, int q) {
    if(c==NULL) {
        c = (Compras) malloc(sizeof(struct compras));
        strcpy(c->cliente,cl);
        c->lista = initListaCompras(c->lista,p,m,pr,q);
        c->esq=c->dir=NULL;
    }
    return c;
}

/**
 * Insere elemento na lista de compras
 * @param l
 * @param p
 * @param pr
 * @param q
 * @return 
 */
ListaCompras insereElemListaCompras(ListaCompras l, char *p, char m, double pr, int q) {
    if(l==NULL) {
        l = initListaCompras(l,p,m,pr,q);
    } else {
        ListaCompras novo;
        novo = (ListaCompras) malloc(sizeof(struct listaCompras));
        strcpy(novo->produto,p);
        novo->modo = m;
        novo->preco = pr;
        novo->quantidade = q;
        novo->prox = l;
        l = novo;
    }
    return l;
}

/**
 * Insere compra na estrutura compras
 * NOTA:    precisa de balancear?
 * @param c
 * @param c
 * @param p
 * @param pr
 * @param q
 * @return 
 */
Compras insereCompra(Compras c, char *cl, char *p, char m, double pr, int q) {
    if(c==NULL){
        c = initCompras(c,cl,p,m,pr,q);
    } else if(strcmp(c->cliente,cl)==0) {
        c->lista = insereElemListaCompras(c->lista,p,m,pr,q);
        c = balancear(c);
    } else if(strcmp(c->cliente,cl)>0) {
        c->esq = insereCompra(c->esq,cl,p,m,pr,q);
        c = balancear(c);
    } else if(strcmp(c->cliente,cl)<0) {
        c->dir = insereCompra(c->dir,cl,p,m,pr,q);
        c = balancear(c);        
    }
    
    return c;
}

/**
 * NOTA: Função de teste de impressão AUXILIARES
 *       ### APAGAR DEPOIS ### 
 * @param l
 */
void imprimeListaCompras(ListaCompras l) {
    if(l!=NULL) {
        printf("\tPRODUTO: %s MODO: %c PRECO: %f QUANTIDADE: %d\n",l->produto,l->modo,l->preco,l->quantidade);
        imprimeListaCompras(l->prox);
    }   
}

/**
 * NOTA: Função de teste de impressão AUXILIARES 
 *       ### APAGAR DEPOIS ###
 * @param c
 */
void imprimeCompras(Compras c) {
    if(c!=NULL) {
        imprimeCompras(c->esq);
          puts("---------------");
        printf("CLIENTE: %s\n",c->cliente);
        imprimeListaCompras(c->lista);
          puts("---------------");
        imprimeCompras(c->dir);
    }
}

/*************
 Gestão da AVL
 *************/

/** Função que calcula a altura de um nodo **/
int altura(Compras nodo){
	int alt = 0;
    if (nodo != NULL){
        int altura_esq = altura(nodo->esq);
        int altura_dir = altura(nodo->dir);
        int max=0;
        if(altura_esq > altura_dir) max = altura_dir;
        alt = 1 + max;
    }
    return alt;
}

/** Função que calcula o fator de balanceamento de um nodo **/
int fator (Compras nodo){
	int altura_esq = altura(nodo->esq);
	int altura_dir = altura(nodo->dir);
	int dif = altura_esq - altura_dir;
	return dif;
}

/** Rotação Dir Dir **/
Compras rotacao_dir_dir(Compras pai){
	Compras  nodo1;
	nodo1=pai->dir;
	pai->dir = nodo1->esq;
	nodo1->esq=pai;
	return nodo1;
}

/** Rotação Esq Esq **/
Compras rotacao_esq_esq(Compras pai){
	Compras nodo1;
	nodo1 = pai->esq;
	pai->esq = nodo1->dir;
	nodo1->dir = pai;
	return nodo1;
}

/**Rotação Dir Esq */
Compras rotacao_dir_esq(Compras  pai)
{
	Compras  nodo1;
	nodo1 = pai->dir;
	pai->dir = rotacao_esq_esq(nodo1);
	return rotacao_dir_dir(pai);
}

/** Rotação Esq Dir **/
Compras rotacao_esq_dir(Compras  pai){

	Compras nodo1;
	nodo1 = pai->esq;
	pai->esq = rotacao_dir_dir(nodo1);
	return rotacao_esq_esq(pai);
}

/** Função para balancear a AVL **/
Compras balancear(Compras nodo)
{
    int bfator = fator(nodo);
    if (bfator >1) {
        if (fator(nodo->esq) >0)
            nodo=rotacao_esq_esq(nodo);
        else
            nodo=rotacao_esq_dir(nodo);
    }
    else if(bfator < -1) {
        if(fator(nodo->dir) >0)
            nodo=rotacao_dir_esq(nodo);
        else
            nodo=rotacao_dir_dir(nodo);
    }
    return nodo;
}  


/**
 Main
 */

int main() {
    Compras c = NULL;
    c = insereCompra(c,"Carlos","AA0124",'N',1,5);
    c = insereCompra(c,"Carlos","BB0124",'N',1,5);
    c = insereCompra(c,"Carlos","CC0124",'N',1,5);
    
    c = insereCompra(c,"Bruno","DD0124",'P',1,5);
    c = insereCompra(c,"Bruno","EE0124",'P',1,5);
    c = insereCompra(c,"Bruno","FF0124",'P',1,5);
    
    c = insereCompra(c,"Ana","GG0124",'N',1,5);
    c = insereCompra(c,"Ana","HH0124",'P',1,5);
    c = insereCompra(c,"Ana","II0124",'N',1,5);
    
    imprimeCompras(c);
    
    return 0;
}