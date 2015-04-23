#include"compras.h"

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
 * NOTA:    precisa de balancearCP?
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
    } else if(strcmp(c->cliente,cl)>0) {
        c->esq = insereCompra(c->esq,cl,p,m,pr,q);
    } else if(strcmp(c->cliente,cl)<0) {
        c->dir = insereCompra(c->dir,cl,p,m,pr,q);    
    }
    
    return c;
}

/**
 * Calcula o comprimento da lista de compras
 * @param l
 */
int comprimentoListaCompras(ListaCompras l) {
    int res=0;
    ListaCompras aux = l;
    
    while(aux!=NULL) {
        res++;
        aux = aux->prox;
    }
    return res;
}



/**
 * Retorna 0 se nao comprou
 * Retorna N se comprou N vezes
 * @param l
 * @param p
 * @return 
 */
int clienteComprouProduto(ListaCompras l, char *p) {
    int res=0;
    ListaCompras laux;
    
    if(l==NULL) {
        res=0;
    } else {
        laux = l;
        while(laux) {
            if(strcmp(laux->produto,p)==0) {
                res++;
            }
            laux = laux->prox;
        }
    }
    
    return res;
}

/*************
 Gestão da AVL
 *************/

/** Função que calcula a alturaCP de um nodo **/
int alturaCP(Compras nodo)
{
	int alt = 0;
    if (nodo != NULL){
        int alturaCP_esq = alturaCP(nodo->esq);
        int alturaCP_dir = alturaCP(nodo->dir);
        int max=0;
        if(alturaCP_esq > alturaCP_dir) max = alturaCP_dir;
        alt = 1 + max;
    }
    return alt;
}

/** Função que calcula o fatorCPCP de balanceamento de um nodo **/
int fatorCP (Compras nodo)
{
	int alturaCP_esq = alturaCP(nodo->esq);
	int alturaCP_dir = alturaCP(nodo->dir);
	int dif = alturaCP_esq - alturaCP_dir;
	return dif;
}

/** Rotação Dir Dir **/
Compras rotacao_dir_dirCP(Compras pai)
{
	Compras  nodo1;
	nodo1=pai->dir;
	pai->dir = nodo1->esq;
	nodo1->esq=pai;
	return nodo1;
}

/** Rotação Esq Esq **/
Compras rotacao_esq_esqCP(Compras pai){
	Compras nodo1;
	nodo1 = pai->esq;
	pai->esq = nodo1->dir;
	nodo1->dir = pai;
	return nodo1;
}

/**Rotação Dir Esq */
Compras rotacao_dir_esqCP(Compras  pai)
{
	Compras  nodo1;
	nodo1 = pai->dir;
	pai->dir = rotacao_esq_esqCP(nodo1);
	return rotacao_dir_dirCP(pai);
}

/** Rotação Esq Dir **/
Compras rotacao_esq_dirCP(Compras  pai) {

	Compras nodo1;
	nodo1 = pai->esq;
	pai->esq = rotacao_dir_dirCP(nodo1);
	return rotacao_esq_esqCP(pai);
}

/** Função para balancearCP a AVL **/
Compras balancearCP(Compras nodo)
{
    int bfatorCP = fatorCP(nodo);
    if (bfatorCP >1) {
        if (fatorCP(nodo->esq) >0)
            nodo=rotacao_esq_esqCP(nodo);
        else
            nodo=rotacao_esq_dirCP(nodo);
    }
    else if(bfatorCP < -1) {
        if(fatorCP(nodo->dir) >0)
            nodo=rotacao_dir_esqCP(nodo);
        else
            nodo=rotacao_dir_dirCP(nodo);
    }
    return nodo;
}  
