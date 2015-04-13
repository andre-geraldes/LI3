#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clientes.h"
#include "produtos.h"


NodoC clientes[26];
NodoP produtos[26];

int linha_valida (char ** c, double p, int n, int m, NodoC cl, NodoP pr){
	int x = 0;
	if(existeC(cl, c[4]) && existeP(pr, c[0]) && (p > 0.0) && (n > 0) && ((m >= 1) || (m <= 12))) x = 1;
	return x;
}

int leitura (char * nome_fich) {
	FILE * ficheiro;
	
	char *string = (char *) malloc(100);
	char *str = (char *) malloc(100);
	char *token = NULL;
	char limit[2] = " ";

	int linhas = 0;
	int linhas_val = 0;

	ficheiro = fopen(nome_fich, "r");
	
	if (strcmp(nome_fich, "FichClientes.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;	
			token = strtok(string, limit);
			token[5] = '\0';
			clientes[token[0]-'A'] = insertC(clientes[token[0]-'A'], token);
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\n", nome_fich, linhas);
	}
	else if (strcmp(nome_fich, "FichProdutos.txt") == 0){
		while ((string = fgets (str, 100, ficheiro)) != NULL) {
			linhas++;
			token = strtok(string, limit);
			token[6] = '\0';
			produtos[token[0]-'A'] = insertP(produtos[token[0]-'A'], token);
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
			
			if (linha_valida(compra, preco, nr, mes, clientes[compra[4][0]-'A'], produtos[compra[0][0]-'A'])){
				linhas_val++;
			}
			//printf("Produto: %s Preço: %.2f Nr comprados: %d Tipo: %s Cliente: %s Mes: %d\n", compra[0], preco, nr, compra[3], compra[4], mes);
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\nNúmero de linhas válidas: %d\n", nome_fich, linhas, linhas_val);	
	}
	else return 0;
	
	//int k = contaNodosC(clientes[0]);
	//char matriz[k][7];
	//int i=0;

	//listarC(clientes[0], k, 7, matriz, &i);
	//for (int h = 0; h < k; h++) printf("Posição: %d Cliente: %s\n",h, matriz[h]);

	free(str);
	free(string);
	fclose(ficheiro);
	return 1;
}


int main (){
	
	
	leitura("FichClientes.txt");
	leitura("FichProdutos.txt");
	leitura("Compras.txt");
	return 0;
}
