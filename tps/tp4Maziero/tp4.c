#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

// TAD lista de números inteiros - programa de teste
// Carlos Maziero - DINF/UFPR, Set 2023

// Coloque os includes necessários a este arquivo aqui.

// Eventuais funções auxiliares (usadas somente neste arquivo) podem vir aqui.
void imprimeLista(char name[],lista_t *L,int tam){
	lista_imprime(&name[0],L);	
	printf("(%d elementos)",tam);
}

void imprimeElem(lista_t *L,int elem,int pos){
	int i;
	
	printf("VALOR NA POSICAO %d",pos);
	i = lista_consulta(L,&elem,pos);
	if(i == -1){
		printf(" NAO ENCONTRADO");
	}else{
		printf(": %d",elem);
	}
}

void imprimePos(lista_t *L,int elem){
	int i;

	i = lista_procura(L,elem);
	printf("POSICAO DO VALOR %d: ",elem);
	if(i == -1){
		printf("NAO ENCONTRADO");
	}else{
		printf("%d",i);
	}
}

//considera que o usuario da o elemento e procura posição
void retiraElem(lista_t *L,int elem,int *tam){	
	//posicao do elemento
	int i;								
	
	i = lista_procura(L,elem);			//recebe posição do elemento na lista
	printf("RETIRA VALOR %d ",elem);
	if(i == -1){
		printf("NAO ENCONTRADO");
	}else{
		printf("DA POSICAO %d",i);
		*tam = lista_retira(L,&elem,i);
	}
}

void destroiLista(lista_t *L,char name[],int elem,int tam){
	//enquanto L não estiver vazia
	while(!lista_vazia(L)){
		//retira o primeiro valor de L e o imprime
		tam = lista_retira(L,&elem,0);
		printf("RETIRADO PRIMEIRO: ");
		printf("%d\n",elem);	
		//retira o último valor de L e o imprime	
		tam = lista_retira(L,&elem,-1);
		printf("RETIRADO ULTIMO: ");
		if(lista_vazia(L)){
			printf("NAO ENCONTRADO\n");
		}else{
			printf("%d\n",elem);
		}	
		//imprime L		
		imprimeLista(name,L,tam);
		printf("\n");
	}
}

int main () {
	lista_t *L;
	int pos;
	int elem;
	int tam;
	char name[7];
	
	name[0] = 'L';
	name[1] = 'I';
	name[2] = 'S';
	name[3] = 'T';
	name[4] = 'A';
	name[5] = ':';
	name[6] = '\0';
	// cria uma lista L vazia
	L = lista_cria();
	if(!L){
		printf("Erro ao alocar\n");
		return -1;
	}
	// imprime L
	imprimeLista(name,L,0);
	printf("\n");
	// insere no final de L os valores 10, 11, 12, 13 e 14, nessa ordem
	elem = 10;
	pos = 10;
	for(int i = 0; i < 5;i++){	
		tam = lista_insere(L,elem,pos);
		pos--;
		elem++;
	}
	// imprime L
	imprimeLista(name,L,tam);
	printf("\n");
	// insere no início de L o valor 32
	lista_insere(L,32,0);
	// insere no início de L o valor 64
	tam = lista_insere(L,64,0);
	// imprime L
	imprimeLista(name,L,tam);
	printf("\n");
	// insere no meio de L o valor 103
	tam = lista_insere(L,103,tam/2);
	// insere no meio de L 0 valor 47
	tam = lista_insere(L,47,tam/2);
	// imprime L
	imprimeLista(name,L,tam);
	printf("\n");
	printf("\n");

	//imprime o conteúdo das posições início, 5, última e 100 de L
	imprimeElem(L,elem,0);
	printf("\n");
	imprimeElem(L,elem,5);
	printf("\n");
	imprimeElem(L,elem,-1);
	printf("\n");
	imprimeElem(L,elem,100);
	printf("\n");
	printf("\n");
	
	//imprime as posições dos valores 5, 10 e 14 em L
	imprimePos(L,5);
	printf("\n");
	imprimePos(L,10);
	printf("\n");
	imprimePos(L,14);	
	printf("\n");
	printf("\n");
	
	//retira de L os valores 12, 103 e 79
	retiraElem(L,12,&tam);
	printf("\n");
	retiraElem(L,103,&tam);
	printf("\n");
	retiraElem(L,79,&tam);
	printf("\n");
	//imprime L
	imprimeLista(name,L,tam);
	printf("\n");
	printf("\n");
	
	//enquanto L não estiver vazia
	//retira o primeiro valor de L e o imprime	
	//retira o último valor de L e o imprime	
	//imprime L
	destroiLista(L,name,elem,tam);
	
	//fim enquanto
	//destrói L
	lista_destroi(L);
	
	//encerra
	return 0;
} 
