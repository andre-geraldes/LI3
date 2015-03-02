typedef struct produtos {
	char nome[7];
	struct produtos *esq, *dir;
} Produtos;

Produtos * inserir(Produtos * c, char * n);
