#include "aux.h"

/* Funçao que retorna o maior de dois inteiros */
int max(int a, int b)
{
    return (a > b)? a : b;
}

void imprimeLista(ListaLigada ll){
	int i, h = 0, total = 0, nelem = comprimentoListaLigada(ll), nrpag = nelem/40;
	char key = 'n';
	ListaLigada l = ll;

	if((nelem%40)) nrpag++;
	
	while(key != 'q'){
		if(key == 'n'){
			system("clear");
			for(i = 0; i < 40 && l; i++){
				printf("|  %s  |\n", l->codigo);
				l = l->prox;
				total++;
			}
			h++;
			printf("Página: %d de %d | Lidos: %d de %d |\n",h, nrpag, total, nelem);
			printf("\'n\' para próximo, \'p\' para anterior, \'q\' para sair\n");
		}
		else if(key == 'p'){
			if(total > 40){ 
				system("clear");
				if(total >= 80){
					for(i = 0; i < 80 && l; i++){
					l = l->ant;
				}
				}
				for(i = 0; i < 40 && l; i++){
					printf("|  %s  |\n", l->codigo);
					if(total >1) total--;
					l = l->prox;
				}
				if(h > 1){
					h--;
				}
			else {
				if(total == 40) l = ll;
				for(i = 0; i < 40 && l; i++){
					printf("|  %s  |\n", l->codigo);
					l = l->prox;
					total++;
				}
			}
			}
			printf("Página: %d de %d | Lidos: %d de %d |\n",h, nrpag, total, nelem);
			printf("\'n\' para próximo, \'p\' para anterior, \'q\' para sair\n");
		}
		key = getchar();
	}

}
