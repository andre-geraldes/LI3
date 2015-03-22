#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "testeavl.h"

// A utility function to get maximum of two integers
int max(int a, int b);
 
// A utility function to get altura of the tree
int altura(Nodo N)
{
    if (N == NULL)
        return 0;
    return N->altura;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a novo nodo with the given valor and
    NULL esq and dir pointers. */
Nodo novonodo(char * valor)
{
    struct nodo* nodo = (Nodo)
                        malloc(sizeof(struct nodo));
    strcpy(nodo->valor, valor);
    nodo->esq   = NULL;
    nodo->dir   = NULL;
    nodo->altura = 1;  // novo nodo is initially added at leaf
    return(nodo);
}
 
// A utility function to dir rotate subtree rooted with y
// See the diagram given above.
Nodo dirRotate(Nodo y)
{
    Nodo x = y->esq;
    Nodo T2 = x->dir;
 
    // Perform rotation
    x->dir = y;
    y->esq = T2;
 
    // Update alturas
    y->altura = max(altura(y->esq), altura(y->dir))+1;
    x->altura = max(altura(x->esq), altura(x->dir))+1;
 
    // Return novo root
    return x;
}
 
// A utility function to esq rotate subtree rooted with x
// See the diagram given above.
Nodo esqRotate(Nodo x)
{
    Nodo y = x->dir;
    Nodo T2 = y->esq;
 
    // Perform rotation
    y->esq = x;
    x->dir = T2;
 
    //  Update alturas
    x->altura = max(altura(x->esq), altura(x->dir))+1;
    y->altura = max(altura(y->esq), altura(y->dir))+1;
 
    // Return novo root
    return y;
}
 
// Get Balance factor of nodo N
int getBalance(Nodo N)
{
    if (N == NULL)
        return 0;
    return altura(N->esq) - altura(N->dir);
}
 
Nodo insert(Nodo nodo, char * valor)
{
    /* 1.  Perform the normal BST rotation */
    if (nodo == NULL)
        return(novonodo(valor));
 
    if (strcmp(valor, nodo->valor) < 0)
        nodo->esq  = insert(nodo->esq, valor);
    else if (strcmp(valor, nodo->valor) > 0)
        nodo->dir = insert(nodo->dir, valor);
 
    /* 2. Update altura of this ancestor nodo */
    nodo->altura = max(altura(nodo->esq), altura(nodo->dir)) + 1;
 
    /* 3. Get the balance factor of this ancestor nodo to check whether
       this nodo became unbalanced */
    int balance = getBalance(nodo);
 
    // If this nodo becomes unbalanced, then there are 4 cases
 
    // esq esq Case
    if (balance > 1 && (strcmp(valor, nodo->esq->valor) < 0))
        return dirRotate(nodo);
 
    // dir dir Case
    if (balance < -1 && (strcmp(valor, nodo->dir->valor) > 0))
        return esqRotate(nodo);
 
    // esq dir Case
    if (balance > 1 && (strcmp(valor, nodo->esq->valor) > 0))
    {
        nodo->esq =  esqRotate(nodo->esq);
        return dirRotate(nodo);
    }
 
    // dir esq Case
    if (balance < -1 && (strcmp(valor, nodo->dir->valor) < 0))
    {
        nodo->dir = dirRotate(nodo->dir);
        return esqRotate(nodo);
    }
 
    /* return the (unchanged) nodo pointer */
    return nodo;
}
 
// A utility function to print preorder traversal of the tree.
// The function also prints altura of every nodo
void preOrder(Nodo root)
{
    if(root != NULL)
    {
        printf("%s %d\n", root->valor, root->altura);
        preOrder(root->esq);
        preOrder(root->dir);
    }
}

void print(Nodo root)
{
    if(root != NULL)
    {
        print(root->esq);
        printf("%s %d\n", root->valor, root->altura);
        print(root->dir);
    }
}

int contaNodos(Nodo avl)
{
	if(avl == NULL) return 0;
	return 1 + contaNodos(avl->esq) + contaNodos(avl->dir);
}

void listar(Nodo n, int l, int c, char lista[l][c], int *i)
{
	if (n != NULL)
	{
		listar(n->esq, l, c, lista, i);
		strcpy(lista[(*i)], n->valor);
		//printf("%d->%s->%s\n",(*i),n->valor,lista[(*i)]);
		(*i)++;
		listar(n->dir, l, c, lista, i);
	}
}

int existe(Nodo n, char * nom)
{
	int x = 0;
	if ( n == NULL) {}
	else if (strcmp(n->valor, nom) == 0) { x = 1;}
	else if (strcmp(nom, n->valor) < 0) { x = existe(n->esq, nom);}
	else { x = existe(n->dir, nom);}
	return x;
}
