typedef struct clientes {
	char nome[6];
	struct clientes *esq, *dir;
} Clientes;


Clientes * inserir(Clientes * c, char * n);
