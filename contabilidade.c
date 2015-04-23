#include "contabilidade.h"

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
        m->ncompras = 0;
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
    } else if(strcmp(c->produto,p)>0) {
        c->esq = inserirContabilidade(c->esq,p);
    }
    /* Case já tenha o código retorna sem alterações */
    /* c = balancearCT(c); */
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
                c->normal->ncompras += 1;
                c->normal->nvendas += q;
                c->normal->facturado += q*pr;
            } else if (m=='P') {
                c->promocao->ncompras += 1;
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
 * Verifica se um produto foi comprado num determinado mês
 * NOTA: O apontador contabilidade corresponde a um mês
 *       passado como parâmetro
 * @param c
 * @param p
 */
int produtoFoiComprado(Contabilidade c, char *p) {
    int res=0;
    
    if(c==NULL) {
        res = 0;
    } else if(strcmp(c->produto,p)==0) {
        if((c->normal->nvendas > 0) || (c->promocao->nvendas > 0)) {
            res = 1;
        } else {
            res = 0;
        }
    } else if(strcmp(c->produto,p)>0) {
        res =  produtoFoiComprado(c->esq,p);
    } else {
        res = produtoFoiComprado(c->dir,p);
    }
    
    return res;
}

/**
 * Calcula o numero de vendas e o total facurado de um dado mês
 * @param c
 * @param v
 * @param f
 */
void numeroVendasETotalFacturado(Contabilidade c, int *v, double *f) {
    if(c!=NULL) {
        (*v) += c->normal->ncompras + c->promocao->ncompras;
        (*f) += c->normal->facturado + c->promocao->facturado;
        numeroVendasETotalFacturado(c->esq,v,f);
        numeroVendasETotalFacturado(c->dir,v,f);
    }
    
}

/*************
 Gestão da AVL
 *************/

/** Função que calcula a altura de um nodo **/
int alturaCT(Contabilidade nodo){
	int alt = 0;
    if (nodo != NULL){
        int altura_esq = alturaCT(nodo->esq);
        int altura_dir = alturaCT(nodo->dir);
        int max=0;
        if(altura_esq > altura_dir) max = altura_dir;
        alt = 1 + max;
    }
    return alt;
}

/** Função que calcula o fator de balanceamento de um nodo **/
int fatorCT(Contabilidade nodo){
	int altura_esq = alturaCT(nodo->esq);
	int altura_dir = alturaCT(nodo->dir);
	int dif = altura_esq - altura_dir;
	return dif;
}

/** Rotação Dir Dir **/
Contabilidade rotacao_dir_dirCT(Contabilidade pai){
	Contabilidade  nodo1;
	nodo1=pai->dir;
	pai->dir = nodo1->esq;
	nodo1->esq=pai;
	return nodo1;
}

/** Rotação Esq Esq **/
Contabilidade rotacao_esq_esqCT(Contabilidade pai){
	Contabilidade nodo1;
	nodo1 = pai->esq;
	pai->esq = nodo1->dir;
	nodo1->dir = pai;
	return nodo1;
}

/**Rotação Dir Esq */
Contabilidade rotacao_dir_esqCT(Contabilidade  pai)
{
	Contabilidade  nodo1;
	nodo1 = pai->dir;
	pai->dir = rotacao_esq_esqCT(nodo1);
	return rotacao_dir_dirCT(pai);
}

/** Rotação Esq Dir **/
Contabilidade rotacao_esq_dirCT(Contabilidade  pai){

	Contabilidade nodo1;
	nodo1 = pai->esq;
	pai->esq = rotacao_dir_dirCT(nodo1);
	return rotacao_esq_esqCT(pai);
}

/** Função para balancearCT a AVL **/
Contabilidade balancearCT(Contabilidade nodo)
{
    int bfator = fatorCT(nodo);
    if (bfator >1) {
        if (fatorCT(nodo->esq) >0)
            nodo=rotacao_esq_esqCT(nodo);
        else
            nodo=rotacao_esq_dirCT(nodo);
    }
    else if(bfator < -1) {
        if(fatorCT(nodo->dir) >0)
            nodo=rotacao_dir_esqCT(nodo);
        else
            nodo=rotacao_dir_dirCT(nodo);
    }
    return nodo;
}  
