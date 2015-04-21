#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clientes.h"
#include "produtos.h"
#include "listaligada.h"
#include "contabilidade.h"
#include "compras.h"
#include "aux.h"

static NodoC clientes[26];
static NodoP produtos[26];
static Contabilidade contas[12];
static Compras compras[12];

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
	char modo;

	int linhas = 0;
	int linhas_val = 0;
	int i;

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
			for(i = 0; i < 12; i++){
				contas[i] = inserirContabilidade(contas[i],token);
			}
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
			
			/* compra[4] -> cliente
			 * compra[0] -> produto
			 */ 
			preco = strtod(compra[1], &compra[1]);
			nr = atoi(compra[2]);
			mes = atoi(compra[5]);
			modo = compra[3][0];
			
			if (linha_valida(compra, preco, nr, mes, clientes[compra[4][0]-'A'], produtos[compra[0][0]-'A'])){
				linhas_val++;
				compras[mes-1] = insereCompra(compras[mes-1], compra[4], compra[0], modo, preco, nr);
			}
		}
		printf("Ficheiro lido: %s\nNúmero de linhas lidas: %d\nNúmero de linhas válidas: %d\n", nome_fich, linhas, linhas_val);	
	}
	else return 0;
	
	free(str);
	free(string);
	fclose(ficheiro);
	return 1;
}


int main (){
	int i;
	ListaLigada l = NULL;
	
	for(i = 0; i < 12; i++){
		contas[i] = NULL;
		compras[i] = NULL;
	}

	leitura("FichClientes.txt");
	leitura("FichProdutos.txt");
	leitura("Compras.txt");

	for(i = 0; i < 12; i++){
		compras[i] = balancearCP(compras[i]);
	}
	imprimeCompras(compras[0]);
	/* QUERIE 2 */
	//l = clientesParaLista(l, clientes[1]); 
	//imprimeLista(l); 
	return 0;
}
