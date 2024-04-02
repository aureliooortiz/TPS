#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "racionais.h"

#define SIZE 100

void ordenaVetor_r(struct racional *vet,int n){
	int comp;
	int i;
	int j;
	struct racional temp;
	
	for(i = 0;i < n-1; i++){
		for(j = i+1; j < n; j++){
			comp = compara_r(vet[i], vet[j]);
			if(comp > 0){
				temp = vet[j];
				vet[j] = vet[i];
				vet[i] = temp;
			}
		}
	}
}

int main (){
	int n;
	int i;
	int j;
	struct racional vetorValidos[SIZE];
	struct racional soma;

	srand(0);

	scanf("%d", &n);				/*le um n tal que 0 < n < 100*/
	if((n < 0) || (n > 100)){ 
		return 1;
	}
					
	struct racional vetorRac[n];			/*cria um vetor de n posicoes*/

	for(i = 0;i < n; i++){				/*cria e imprime vetor de racionais*/
		vetorRac[i] = sorteia_r(n);
		imprime_r(vetorRac[i]);
		printf(" ");
	}
	printf("\n");
	
	j = 0;
	for(i = 0; i < n; i++){				/*imprime vetor apenas de validos*/
		if(valido_r(vetorRac[i]) != 0){
			vetorValidos[j] = vetorRac[i];
			imprime_r(vetorValidos[j]);
			printf(" ");
			j++;				/*numero de posicoes do vetor*/
		}
	}
	printf("\n");

	ordenaVetor_r(vetorValidos, j);			/* ordena vetor do menor para maior */
	
	for(i = 0; i < j; i++){				/*imprime vetor ordenado*/
		imprime_r(vetorValidos[i]);
		printf(" ");
	}
	printf("\n");
	
	printf("a soma de todos os elementos eh: ");		
	if(j > 1){						/*caso com 2 ou mais elementos no vetor*/
		soma_r(vetorValidos[0],vetorValidos[1],&soma);
		for(i = 2; i < j; i++){
			simplifica_r(&soma);
			soma_r(soma,vetorValidos[i],&soma);
			//simplifica_r(&soma);			
		}
	}else if(j == 1){					/*caso haja apenas um elemento no vetor*/
		imprime_r(vetorValidos[0]);
		printf("\n");
		return 1;
	}else{					/*caso nao haja elementos no vetor*/
		printf("0\n");					
		return 1;		
	}
	
	imprime_r(soma);			/*imprime a soma de todos os elementos*/

	printf("\n");
	return 0;
}
