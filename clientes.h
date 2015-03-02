typedef struct clientes {
	char nome[6];
	struct clientes *esq, *dir;
} Clientes;

Clientes * addCliente(Clientes * c, char * n);

void printC(Clientes * c);	
