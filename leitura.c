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
	if(existeC(cl, c[4]) && existeP(pr, c[0]) && (p >= 0.0) && (n > 0) && ((m >= 1) || (m <= 12))) x = 1;
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
	char c, l;
	Compras aux = NULL;
	ListaCompras auxcompras = NULL;
	FILE * file;

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
	puts("Pretende guardar esta tabela? (S ou N)");
	scanf(" %c",&l);
	while( l != 'S' && l !='N') {
		puts("Letra inválida, insira outra vez:");
		scanf(" %c",&l);
	}

	if(l == 'S'){
		file = fopen("query5.txt", "w+");
		fprintf(file,"---------------------\n");
		fprintf(file,"|  Cliente: %s   |\n",codigo);
		fprintf(file,"---------------------\n");
		fprintf(file,"|  Mês | Nr compras |\n");
		fprintf(file,"---------------------\n");
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
	
		fprintf(file,"|  %2d  |     %2d     |\n",i+1,total);
		total = 0;
		}
		fprintf(file,"---------------------\n");
		fclose(file);
	}

	c = getchar();
	c = getchar();

}

void query6(){
	char c = '1';
	ListaLigada l = NULL;

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

void query7() {
    int li,ls,i,valido=0,nvendas=0;
    double facturado=0;
    char c;
    
    imprimeNumQuery(7);
    while(!valido) {
        puts("Limite inferior:");
        scanf("%d",&li);
        puts("Limite superior:");
        scanf("%d",&ls);
        if(ls<li || li<1 || li>12 || ls<1 || ls>12) {
            puts(" *** Intervalo inválido **** ");
            valido = 0;
        } else {
            valido = 1;
        }
    }
    
    for(i=li-1;i<ls;i++) {
        numeroVendasETotalFacturado(contas[i],&nvendas,&facturado);
    }
    printf("No intervalo [%d,%d] foram registadas %d vendas e um total facturado de %f€.\n",li,ls,nvendas,facturado);
    
    c = getchar();
    c = getchar();
}

void query8() {
    int i;
    char codigo[7];
    ListaLigada clientesN = NULL, clientesP = NULL;
    Compras caux;
    
    imprimeNumQuery(8);
    
    puts("Insira o código do produto:");
    scanf("%s",codigo);
    while(!existeP(produtos[codigo[0]-'A'], codigo)){
	puts("Código inválido, insira outra vez:");
	scanf("%s",codigo);
    }
    
    for(i = 0; i < 12; i++){
        caux = compras[i];
    	clientesN = listaClientesCompraramProduto(caux,clientesN,'N',codigo);
        clientesP = listaClientesCompraramProduto(caux,clientesP,'P',codigo);
    }
    imprimeLista(clientesN);
    imprimeLista(clientesP);
}

void query9() {
    char codigo[6];
    int mes;
    ListaLigada produtos = NULL;
    ListaCompras lc=NULL,lcsr=NULL,lco=NULL;
    
    imprimeNumQuery(9);
    
    puts("Qual o Cliente?");
    scanf("%s",codigo);
    while(!existeC(clientes[codigo[0]-'A'], codigo)){
	puts("Cliente inválido, insira outra vez:");
	scanf("%s",codigo);
    }
    puts("Insira o mês:");
    scanf("%d",&mes);
    while(mes<1 || mes>12){
        puts("Mês inválido, insira outra vez:");
	scanf("%d",&mes);
    }
   
    lc = devolveListaComprasCliente(compras[mes-1],lc,codigo); 
    lcsr = juntaComprasPorProduto(lcsr,lc); 
    lco = insereComprasOrdenadas(lco,lcsr);    
    produtos = listaLigadaDeCompras(lco,produtos); 
    
    imprimeLista(produtos);
}

void query10(){
	int i;
	ListaLigada clientes = NULL, aux = NULL, h = NULL;
	imprimeNumQuery(10);

	/*
	clientes = comprasDoClientesParaLista(clientes, compras[0]);
	for(i = 1; i < 12; i++){
		aux = comprasDoClientesParaLista(aux, compras[i]);
		h = clientes;
		while(h){
			if(!existeElemento(aux,h->codigo)) {
				clientes = removeElemento(clientes,h->codigo);
			}
			h = h->prox;
		}
	}
	*/

	h = comprasDoClientesParaLista(clientes, compras[0]);
	aux = comprasDoClientesParaLista(clientes, compras[1]);
	clientes = interseccaoListas(h,aux);
	for(i=2; i<12; i++){
		aux = comprasDoClientesParaLista(clientes, compras[i]);
		clientes = interseccaoListas(clientes,aux);
	}

	imprimeLista(clientes);

}

void query11(){
	FILE * file;
	int i;
	imprimeNumQuery(11);

	file = fopen("query11.csv", "w+");
	fprintf(file,"\"Mes\",\"#Compras\",\"#Clientes\"\n");
	for(i = 0; i < 12; i++){
		fprintf(file, "\"%d\",\"%d\",\"%d\"", i+1,contaComprasMes(compras[i]), contaClientes(compras[i]));
		if(i != 11) fprintf(file, "\n");
	}
	fclose(file);
}

int main (){
	int i, num = 1, lido=0;
	
	for(i = 0; i < 12; i++){
		contas[i] = NULL;
		compras[i] = NULL;
	}
    
    while(num > 0 && num < 15){
    	system("clear");
   		carregaTextArt("textart-big.txt");
   		puts("\n");
   		num = menuOpcoes();
    	printf("Opção: %d\n",num);
    	switch(num){
    		case 1: {
                    /* Falta o caso de reler */
                    query1(); 
                    lido=1; 
                    break;
                }    
		case 2: {
                    if(lido) query2();
                } break;        
		case 3: {
                    if(lido) query3();
                } break;
		case 4: {
                    if(lido) query4();
                } break;
                /* OPção de guardar em ficheiro */
                case 5: {
                    if(lido) query5();
                } break;
                
		case 6: {
                    if(lido) query6();
                } break;
                
                case 7: {
                    if(lido) query7();
                } break;
                
                case 8: {
                    if(lido) query8();
                } break;
                
                case 9: {
                    if(lido) query9();
                }

                case 10: {
                    if(lido) query10();
                }

                case 11: {
                    if(lido) query11();
                }
    	}
	
    }


	return 0;
}
