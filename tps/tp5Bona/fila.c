#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/*

struct nodo {
    int chave;
    struct nodo *prox;
};

struct fila {
    struct nodo *ini;
    struct nodo *fim;
    int tamanho;
};

*/

/* 
 * Cria e retorna uma nova fila.
 * Retorna NULL em caso de erro de alocação.
*/
struct fila *fila_cria (){
	struct fila *f;
	
	f = malloc(sizeof(struct fila));
	if(!f) return NULL;
	
	f->ini = NULL;
	f->fim = NULL;
	f->tamanho = 0;
	
	return f;
}

/* Desaloca toda memoria da fila e faz fila receber NULL. */
void fila_destroi (struct fila **fila){
	int dado;
	
	if(!fila || !(*fila)) return;
	
	while(!fila_vazia(*fila)){
		dequeue(*fila, &dado);
	}
	free(*fila);
	*fila = NULL;
}

/* 
 * Insere dado na fila (politica FIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int enqueue (struct fila *fila, int dado){
	struct nodo *nodo;
	
	if(!fila) return 0;
	nodo = malloc(sizeof(struct nodo));
	if(!nodo) return 0;
	
	nodo->chave = dado;
	if(fila->tamanho == 0){
		/* caso não haja elementos
		* o fim se torna o primeiro elemento */
		fila->fim = nodo;
	}
	/* o novo elemento vira o inicio
	* e passa a apontar para o antigo inicio */
	nodo->prox = fila->ini;
	fila->ini = nodo;
	fila->tamanho++;
	
	return 1;
}

/* 
 * Remove dado da fila (politica FIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da fila estar vazia.
*/
int dequeue (struct fila *fila, int *dado){
	struct nodo *aux;
	struct nodo *temp;
	
	if(!fila || fila->tamanho == 0) return 0;

	*dado = fila->fim->chave;
	
	aux = fila->ini;
	if(fila->tamanho > 1){
		/* temp irá apontar para o nodo
		* anterior ao final */
		temp = aux;
		while(aux != fila->fim){
			temp = aux;
			aux = aux->prox;
			
		}
		fila->fim = temp;	
		temp->prox = NULL;
	}
	free(aux);
	fila->tamanho--;
	
	return 1;
}
 
/* Retorna o numero de elementos da pilha, que pode ser 0. */
int fila_tamanho (struct fila *fila){
	if(!fila) return 0;

	return fila->tamanho;
}

/* Retorna 1 se fila vazia, 0 em caso contrario. */ 
int fila_vazia (struct fila *fila){
	if(!fila) return 0;
	
	if(fila->tamanho == 0){
		return 1;
	}
	return 0;
}
