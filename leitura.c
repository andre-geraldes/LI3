#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "clientes.h"
//#include "produtos.h"
#include "testeavl.h"

int linha_valida (char ** c, double p, int n, int m){
	//Validar Cliente e produto
	if ((p > 0.0) && (n > 0) && ((strcmp(c[3],"N") == 0)  || (strcmp(c[3],"P") == 0)) && ((m >= 1) || (m <= 12))) {
		return 1;
	}
	else return 0;
}

int leitura (char * nome_fich) {
	FILE * ficheiro;
	
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";

	int linhas = 0;
	int linhas_val = 0;

	Nodo clientes = NULL;
	//Clientes clientes[26];
	//Produtos * produtos[26];

	ficheiro = fopen(nome_fich, "r");
	
	if (strcmp(nome_fich, "FichClientes.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;	
			token = strtok(string, limit);
			token[5] = '\0';
			clientes = insert(clientes, token);
			//clientes[token[0]-'A'] = addCliente(clientes[token[0]-'A'], token);
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\n", nome_fich, linhas);
	}
	else if (strcmp(nome_fich, "FichProdutos.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;
			token = strtok(string, limit);
			token[6] = '\0';
			//produtos[token[0]-'A'] = addProduto(produtos[token[0]-'A'], token);
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\n", nome_fich, linhas);	
	}
	else if (strcmp(nome_fich, "Compras.txt") == 0){
		int i = 0;
		int nr;
		int mes;
		double preco;
		char * compra[6];

		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;
			
			token = strtok(string, limit);
			compra[0] = token;
			for(i=1; token != NULL && i < 6; i++) {
				token = strtok(NULL, " ");
				compra[i] = token;
			}
			
			preco = strtod(compra[1], &compra[1]);
			nr = atoi(compra[2]);
			mes = atoi(compra[5]);
			
			if (linha_valida(compra, preco, nr, mes)){
				linhas_val++;
			}
			//printf("Produto: %s Preço: %.2f Nr comprados: %d Tipo: %s Cliente: %s Mes: %d\n", compra[0], preco, nr, compra[3], compra[4], mes);
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\nNúmero de linhas válidas: %d\n", nome_fich, linhas, linhas_val);	
	}
	else return 0;
	
	int k = contaNodos(clientes);
	char matriz[k][7];
	int i=0;

	listar(clientes, k, 7, matriz, &i);
	for (int h = 0; h < k; h++) printf("Posição: %d Cliente: %s\n",h, matriz[h]);

	if ( existe(clientes, "FZ960")) printf("Existe o cliente\n");
	free(str);
	free(string);
	fclose(ficheiro);
	return 1;
}


int main (){
	
	
	return leitura("FichClientes.txt");
}
