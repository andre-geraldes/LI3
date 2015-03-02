typedef struct produtos {
	char nome[7];
	struct produtos *esq, *dir;
} Produtos;

Produtos * addProduto(Produtos * c, char * n);

void printP(Produtos * p);
