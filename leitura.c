#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clientes.h"
#include "produtos.h"
#include "listaligada.h"
#include "contabilidade.h"
#include "compras.h"
#include "aux.h"
#include "menus.h"

static NodoC clientes[26];
static NodoP produtos[26];
static Contabilidade contas[12];
static Compras compras[12];

int linha_valida (char ** c, double p, int n, int m, NodoC cl, NodoP pr){
	int x = 0;
	if(existeC(cl, c[4]) && existeP(pr, c[0]) && (p >= 0.0) && (n >= 0) && ((m >= 1) || (m <= 12))) x = 1;
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
				contas[mes-1] = actualizaContabilidade(contas[mes-1],compra[0],modo,preco,nr);
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

void query1(){
	char c;
	system("clear");
	imprimeNumQuery(1);

	leitura("FichClientes.txt");
	leitura("FichProdutos.txt");
	leitura("Compras.txt");
	puts("\nLeitura concluida");
	c = getchar();
	c = getchar();
}

void query2(){
	char c = '1';
	ListaLigada l = NULL;

	system("clear");
	imprimeNumQuery(2);

	puts("Qual a letra inicial do código?");

	scanf(" %c",&c);
	while( c < 'A' || c > 'Z') {
		puts("Letra inválida, insira outra vez:");
		scanf(" %c",&c);
	}
	l = produtosParaLista(l, produtos[c-'A']); 
	if(l != NULL) imprimeLista(l); 
	else {
		printf("Não existem produtos começados pela letra %c\n",c);
		c = getchar();
		c = getchar();
	}
}

void query3(){
	int mes = 0, ntotalN = 0, ntotalP = 0;
	double factu = 0.0;
	char codigo[7];
	char c;
	Contabilidade aux;

	system("clear");
	imprimeNumQuery(3);

	puts("Qual o mês?");

	scanf("%d",&mes);
	while(mes < 1 || mes > 12){
		puts("Mês inválido, insira outra vez:");
		scanf("%d",&mes);
	}

	puts("Qual o código?");
	scanf("%s",codigo);
	while(!existeP(produtos[codigo[0]-'A'], codigo)){
		puts("Código inválido, insira outra vez:");
		scanf("%s",codigo);
	}
	aux = contas[mes-1];
	while(strcmp(aux->produto,codigo) != 0){
		if(strcmp(aux->produto,codigo) > 0) aux = aux->esq;
		else aux = aux->dir;
	}
	ntotalN = aux->normal->nvendas;
	ntotalP = aux->promocao->nvendas;
	factu = aux->normal->facturado;
	factu += aux->promocao->facturado;
	printf("\nTotal de vendas no mês %d em modo Normal: %d\n",mes,ntotalN);
	printf("Total de vendas no mês %d em modo Promoçao: %d\n",mes,ntotalP);
	printf("Total facturado no mês %d: %f\n",mes,factu);
	c = getchar();
	c = getchar();
}

void query4(){
	ListaLigada l = NULL, prod = NULL;
	int i, j, flag = 0;

	system("clear");
	imprimeNumQuery(4);

	for(i = 0; i < 26; i++){
		prod = produtosParaLista(prod, produtos[i]);
	}

	while(prod){
		for(j = 0; j < 12; j++){
			if(!produtoFoiComprado(contas[j],prod->codigo)){
				flag++;
			}
		}
		if(flag == 12) l = insereElemento(l, prod->codigo);
		flag = 0;
		prod = prod->prox;
	}

	if(l != NULL) imprimeLista(l);
}

void query5(){
	char codigo[6];
	int i, total = 0;
	char c;
	Compras aux = NULL;
	ListaCompras auxcompras = NULL;

	system("clear");
	imprimeNumQuery(5);

	puts("Qual o Cliente?");
	scanf("%s",codigo);
	while(!existeC(clientes[codigo[0]-'A'], codigo)){
		puts("Cliente inválido, insira outra vez:");
		scanf("%s",codigo);
	}

	puts("---------------------");
	printf("|  Cliente: %s   |\n",codigo);
	puts("---------------------");
	printf("|  Mês | Nr compras |\n");
	puts("---------------------");
	for(i = 0; i < 12; i++){
		aux = compras[i];
		
		while(aux && strcmp(aux->cliente,codigo) != 0){
			if(strcmp(aux->cliente,codigo) > 0) aux = aux->esq;
			else aux = aux->dir;
		}

		if(aux){
			auxcompras = aux->lista;
			while(auxcompras){
				total += auxcompras->quantidade;
				auxcompras = auxcompras->prox;
			}
		}
	

		printf("|  %2d  |     %2d     |\n",i+1,total);
		total = 0;
	}
	puts("---------------------");
	c = getchar();
	c = getchar();

}

void query6(){
	char c = '1';
	ListaLigada l = NULL;

	system("clear");
	imprimeNumQuery(6);

	puts("Qual a letra inicial do Cliente?");
	scanf(" %c",&c);
	while(c < 'A' || c > 'z') {
		puts("Letra inválida, insira outra vez:");
		scanf(" %c",&c);
	}

	if(c >= 'a' && c <= 'z'){
		c = c - ('a' - 'A');
	}

	l = clientesParaLista(l, clientes[c - 'A']); 
	if(l != NULL) imprimeLista(l); 
	else {
		printf("Não existem clientes começados pela letra %c\n",c);
		c = getchar();
		c = getchar();
	}

}

void query7(){
	int mes1, mes2;

	system("clear");
	imprimeNumQuery(7);


}


int main (){
	int i, num = 1;
	
	
	for(i = 0; i < 12; i++){
		contas[i] = NULL;
		compras[i] = NULL;
	}
    
    while( num != 15 ){
    	system("clear");
   		carregaTextArt("textart-big.txt");
   		puts("\n");
   		num = menuOpcoes();
    	printf("Opção: %d\n",num);
    	switch(num){
    		case 1: query1(); break;
			case 2: query2(); break;
			case 3: query3(); break;
			case 4: query4(); break;
			case 5: query5(); break;
			case 6: query6(); break;
			case 7: query7(); break;
    	}
	
	}


	return 0;
}
