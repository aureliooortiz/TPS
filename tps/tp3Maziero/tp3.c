#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"
// Exemplo: ordenar, eliminar invalidos...
int minimoVet(struct racional **v,int a, int b){
	int j;
	int menor;
	int comp;

	j = a;
	menor = a;
	while(j < b){
		j++;
		comp = compara_r(v[j],v[menor]);
		if(comp == -1){
			menor = j;
		}
	}
	return menor;
}

void trocar(struct racional **v,int a, int b){
	struct racional *temp;
	
	temp = v[a];
	v[a] = v[b];
	v[b] = temp;
}

void ordenaVetor_r(struct racional **vet,int a, int b){		//ordenacao por selectionSort recursivo
	if(a >= b){						//desta vez com uma implementacao aceitavel	
		return;
	}
	trocar(vet,a,minimoVet(vet,a,b));
	ordenaVetor_r(vet,a+1,b);
}

int lerRacionais(struct racional **v, int n){
	long int num;
	long int den;
	
	for(int i = 0; i < n; i++){
		scanf("%ld", &num); 			//le o numerador
		scanf("%ld", &den); 			//le o denominador
		v[i] = cria_r(num, den);		//cria um racional 
		if(!v[i]){		
			return 0;
		}
	}

	return 1;
}

void imprimeVetor(struct racional **v, int n){
	for(int i = 0; i < n; i++){
		imprime_r(v[i]);
		printf(" ");
	}
}

int retiraInvalidos(struct racional **v,struct racional **validos,int n){ 
	int j;
	int i;
	
	j = 0;
	for(i = 0; i < n; i++){
		if(valido_r(v[i]) != 0){
			validos[j] = v[i];
			j++;			//numero de posicoes do vetor
		}
	}
	
	for(i = 0; i < j; i++){
		v[i] = validos[i];
	}
	
	return j;			//retorna o numero de posicoes do vetor sem invalidos	
}

void liberaMem(struct racional **v,int tam){
	if(!v){
		return;
	}
	
	for(int i = 0; i < tam ; i++){		
		destroi_r(v[i]);
		v[i] = NULL;
	}
}

void somaVetor(struct racional **v,struct racional **soma,int n){	
	if(n == 1){			//caso haja apenas um elemento no vetor
		imprime_r(v[0]);
		return;	
	}
	if(n == 0){ 			//caso com nenhum elemento no vetor
		printf("0");
		return;
	}

	soma[0] = v[0];
	for(int i = 1; i < n; i++){	
		struct racional temp;
		soma_r(soma[0], v[i], &temp);
		*soma[0] = temp;
	}
	imprime_r(soma[0]);
}

int main (){
	int n;
	int j;
	int valido;
	struct racional **v;		//vetor de racionais
	struct racional **aux;

	do{
		scanf("%d", &n);
	}while(n > 100 || n < 0);
	
	v = malloc(n * sizeof(struct racional*)); 	//aloca memoria para um vetor de ponteiros para racional
	
	if(!v){						
		printf("Erro ao Alocar\n");
		return 1;
	}
	
	valido = lerRacionais(v, n);
	
	if(valido < 1){		
		printf("Erro ao alocar\n");
		return 1;
	}
	
	imprimeVetor(v, n);
	printf("\n");
	
	aux = malloc(n * sizeof(struct racional*));		//aloca memoria para o vetor de validos
	
	j = retiraInvalidos(v,aux,n);
	
	imprimeVetor(v, j);			//imprime vetor sem validos
	printf("\n");
	
	ordenaVetor_r(v,0,j-1);			//ordena vetor do menor para maior
	
	imprimeVetor(v, j);			//imprime vetor ordenado
	printf("\n");
	
	printf("SOMA: ");
	somaVetor(v,aux,j);
	
	liberaMem(v,j);				//libera memoria de cada posicao do vetor		
	free(v);
	v = NULL;
	free(aux);
	aux = NULL;
	
	printf("\n");
	return 0;
}
/* Professor sei que há vazamento de memoria em meu programa
 * não soube resolver o problema, acredito que seja por conta de haver ponteiros 
 * que apontem para uma mesma área na memória, porém não tenho certeza,
 * então se no pdf de correção o senhor puder colocar como eu poderia 
 * resolver isto agradeceria */
