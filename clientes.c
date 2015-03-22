#include "clientes.h"

// A utility function to get maximum of two integers
int maxC(int a, int b);
 
// A utility function to get altura of the tree
int alturaC(NodoC N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}
 
// A utility function to get maximum of two integers
int maxC(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a novo NodoC with the given valor and
    NULL esq and dir pointers. */
NodoC novoNodoC(char * valor)
{
    struct NodoC* NodoC = (NodoC)
                        malloc(sizeof(struct NodoC));
    strcpy(NodoC->valor, valor);
    NodoC->esq   = NULL;
    NodoC->dir   = NULL;
    NodoC->altura = 1;  // novo NodoC is initially added at leaf
    return(NodoC);
}
 
// A utility function to dir rotate subtree rooted with y
// See the diagram given above.
NodoC dirRotateC(NodoC y)
{
    NodoC x = y->esq;
    NodoC T2 = x->dir;
 
    // Perform rotation
    x->dir = y;
    y->esq = T2;
 
    // Update alturas
    y->altura = maxC(alturaC(y->esq), alturaC(y->dir))+1;
    x->altura = maxC(alturaC(x->esq), alturaC(x->dir))+1;
 
    // Return novo root
    return x;
}
 
// A utility function to esq rotate subtree rooted with x
// See the diagram given above.
NodoC esqRotateC(NodoC x)
{
    NodoC y = x->dir;
    NodoC T2 = y->esq;
 
    // Perform rotation
    y->esq = x;
    x->dir = T2;
 
    //  Update altura
    x->altura = max(alturaC(x->esq), alturaC(x->dir))+1;
    y->altura = max(alturaC(y->esq), alturaC(y->dir))+1;
 
    // Return novo root
    return y;
}
 
// Get Balance factor of NodoC N
int getBalanceC(NodoC N)
{
    if (N == NULL)
        return 0;
    return alturaC(N->esq) - alturaC(N->dir);
}
 
NodoC insertC(NodoC NodoC, char * valor)
{
    /* 1.  Perform the normal BST rotation */
    if (NodoC == NULL)
        return(novoNodoC(valor));
 
    if (strcmp(valor, NodoC->valor) < 0)
        NodoC->esq  = insertC(NodoC->esq, valor);
    else if (strcmp(valor, NodoC->valor) > 0)
        NodoC->dir = insertC(NodoC->dir, valor);
 
    /* 2. Update altura of this ancestor NodoC */
    NodoC->altura = max(alturaC(NodoC->esq), alturaC(NodoC->dir)) + 1;
 
    /* 3. Get the balance factor of this ancestor NodoC to check whether
       this NodoC became unbalanced */
    int balance = getBalanceC(NodoC);
 
    // If this NodoC becomes unbalanced, then there are 4 cases
 
    // esq esq Case
    if (balance > 1 && (strcmp(valor, NodoC->esq->valor) < 0))
        return dirRotateC(NodoC);
 
    // dir dir Case
    if (balance < -1 && (strcmp(valor, NodoC->dir->valor) > 0))
        return esqRotateC(NodoC);
 
    // esq dir Case
    if (balance > 1 && (strcmp(valor, NodoC->esq->valor) > 0))
    {
        NodoC->esq =  esqRotateC(NodoC->esq);
        return dirRotateC(NodoC);
    }
 
    // dir esq Case
    if (balance < -1 && (strcmp(valor, NodoC->dir->valor) < 0))
    {
        NodoC->dir = dirRotateC(NodoC->dir);
        return esqRotateC(NodoC);
    }
 
    /* return the (unchanged) NodoC pointer */
    return NodoC;
}


int contaNodosC(NodoC avl)
{
	if(avl == NULL) return 0;
	return 1 + contaNodosC(avl->esq) + contaNodosC(avl->dir);
}

void listarC(NodoC n, int l, int c, char lista[l][c], int *i)
{
	if (n != NULL)
	{
		listarC(n->esq, l, c, lista, i);
		strcpy(lista[(*i)], n->valor);
		(*i)++;
		listarC(n->dir, l, c, lista, i);
	}
}

int existeC(NodoC n, char * nom)
{
	int x = 0;
	if ( n == NULL) {}
	else if (strcmp(n->valor, nom) == 0) { x = 1;}
	else if (strcmp(nom, n->valor) < 0) { x = existeC(n->esq, nom);}
	else { x = existeC(n->dir, nom);}
	return x;
}
