typedef struct nodo
{
	char valor[7];
	struct nodo *esq;
	struct nodo *dir;
	int altura;
} * Nodo;

int altura(Nodo N);

int max(int a, int b);

Nodo novonodo(char * valor);

Nodo dirRotate(Nodo y);

Nodo esqRotate(Nodo x);

int getBalance(Nodo N);

Nodo insert(Nodo nodo, char * valor);

void preOrder(Nodo root);

void print(Nodo root);

int contaNodos(Nodo avl);

void listar(Nodo n, int l, int c, char lista[l][c], int *i);

int existe(Nodo n, char * nom);
