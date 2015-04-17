#include "contabilidade.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * Inicia a estrutura modo
 * @param m
 * @return 
 */
Modo initModo(Modo m) {
    if(m==NULL) {
        m = (Modo) malloc(sizeof(struct modo));
        m->nvendas = 0;
        m->facturado = 0;
    }
    return m;
}

/**
 * Inicia contabilidade tudo a zero, excepto o código do produto
 * @param c
 * @param p
 * @return 
 */
Contabilidade initContabilidade(Contabilidade c, char *p) {
    if(c==NULL) {
        c = (Contabilidade) malloc(sizeof(struct contabilidade));
        c->normal = NULL;
        c->promocao = NULL;
        strcpy(c->produto,p);
        c->normal = initModo(c->normal);
        c->promocao = initModo(c->promocao);
        c->esq=c->dir=NULL;
    }
    return c;
}

/**
 * Insere a contabilidade
 * NOTA: tem de conter os códigos mesmo dos produtos sem vendas
 *       usar na leitura dos codigos dos produtos
 * @param c
 * @param p
 * @return 
 */
Contabilidade inserirContabilidade(Contabilidade c, char *p) {
    if(c == NULL) {
        c = initContabilidade(c,p);
    } else if(strcmp(c->produto,p)<0) {
        c->dir = inserirContabilidade(c->dir,p);
        c = balancear(c);
    } else if(strcmp(c->produto,p)>0) {
        c->esq = inserirContabilidade(c->esq,p);
        c = balancear(c);
    }
    /* Case já tenha o código retorna sem alterações */
    return c;
}

/**
 * Actualiza a contabilidade, contabilizando as compras
 * NOTA: usar na leitura das compras
 *       apenas actualiza os campos dos cógidos correspondentes
 *       logo, não precisa de balanceamento
 * @param c
 * @param p
 * @param m
 * @param u
 * @param p
 * @return 
 */
Contabilidade actualizaContabilidade(Contabilidade c, char *p, char m, double pr, int q) {
    if(c!=NULL) {
        if (strcmp(c->produto,p)==0) {
            if(m=='N') {
                c->normal->nvendas += q;
                c->normal->facturado += q*pr;
            } else if (m=='P') {
                c->promocao->nvendas += q;
                c->promocao->facturado += q*pr;  
            }        
        } else if (strcmp(c->produto,p)>0) {
            c->esq = actualizaContabilidade(c->esq,p,m,pr,q);
        } else if (strcmp(c->produto,p)<0) {
            c->dir = actualizaContabilidade(c->dir,p,m,pr,q);
        }
    }
    return c;
}

/**
 * Função auxiliar de impressão do modo
 *      ### APAGAR DEPOIS
 * @param m
 */
void imprimeModo(Modo m) {
    if(m!=NULL) {
        printf("\t\tVENDAS: %d FACTURADO: %f\n",m->nvendas,m->facturado);
    }
}

/**
 * Função de impressão AUXILIAR
 *      ### APAGAR DEPOIS
 * @param c
 */
void imprimeContabilidade(Contabilidade c) {
    if(c != NULL) {
        imprimeContabilidade(c->esq);
        
          puts("----------------------------------------------------");
        printf("PRODUTO: %s\n",c->produto);
        printf("\tNORMAL:\n");
        imprimeModo(c->normal);
        printf("\tPROMOCAO:\n");
        imprimeModo(c->promocao);
          puts("----------------------------------------------------");
          
        imprimeContabilidade(c->dir);
    }
}

/*************
 Gestão da AVL
 *************/

/** Função que calcula a altura de um nodo **/
int altura(Contabilidade nodo){
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
int fator (Contabilidade nodo){
	int altura_esq = altura(nodo->esq);
	int altura_dir = altura(nodo->dir);
	int dif = altura_esq - altura_dir;
	return dif;
}

/** Rotação Dir Dir **/
Contabilidade rotacao_dir_dir(Contabilidade pai){
	Contabilidade  nodo1;
	nodo1=pai->dir;
	pai->dir = nodo1->esq;
	nodo1->esq=pai;
	return nodo1;
}

/** Rotação Esq Esq **/
Contabilidade rotacao_esq_esq(Contabilidade pai){
	Contabilidade nodo1;
	nodo1 = pai->esq;
	pai->esq = nodo1->dir;
	nodo1->dir = pai;
	return nodo1;
}

/**Rotação Dir Esq */
Contabilidade rotacao_dir_esq(Contabilidade  pai)
{
	Contabilidade  nodo1;
	nodo1 = pai->dir;
	pai->dir = rotacao_esq_esq(nodo1);
	return rotacao_dir_dir(pai);
}

/** Rotação Esq Dir **/
Contabilidade rotacao_esq_dir(Contabilidade  pai){

	Contabilidade nodo1;
	nodo1 = pai->esq;
	pai->esq = rotacao_dir_dir(nodo1);
	return rotacao_esq_esq(pai);
}

/** Função para balancear a AVL **/
Contabilidade balancear(Contabilidade nodo)
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


int main() {
    Contabilidade c = NULL;
    
    /* Leitura dos códigos */
    c = inserirContabilidade(c,"DD0124");
    c = inserirContabilidade(c,"CC0124");
    c = inserirContabilidade(c,"BB0124");
    c = inserirContabilidade(c,"AA0124");
    
    /* Leitura das compras */
    c = actualizaContabilidade(c,"AA0124",'N',1,5);
    c = actualizaContabilidade(c,"AA0124",'N',1.7,5);
    c = actualizaContabilidade(c,"AA0124",'P',1,5);
    c = actualizaContabilidade(c,"AA0124",'P',1.7,5);
    
    c = actualizaContabilidade(c,"DD0124",'N',2,3);
    c = actualizaContabilidade(c,"DD0124",'P',0.5,10);
    
    c = actualizaContabilidade(c,"EE0124",'N',1.7,5);
    
    imprimeContabilidade(c);
    
    return 0;
}