typedef struct produtos {
	char nome[7];
	struct produtos *esq, *dir;
} Produtos;

Produtos * addProduto(Produtos *p, char * n);

int existeProduto (Produtos *p, char * n);

void printP(Produtos * p);
