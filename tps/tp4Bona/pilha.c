#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

/* 
COMEÇO IMPLEMENTAÇÃO CHAT GPT

Função auxiliar para criar um novo nodo 
struct nodo *novo_nodo(int dado) {
    struct nodo *novo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo == NULL) {
        return NULL;   Falha na alocação de memória 
    }
    novo->chave = dado;
    novo->prox = NULL;
    return novo;
}

 Cria e retorna uma nova pilha
struct pilha *pilha_cria() {
    struct pilha *nova_pilha = (struct pilha *)malloc(sizeof(struct pilha));
    if (nova_pilha == NULL) {
        return NULL;   Falha na alocação de memória 
    }
    nova_pilha->topo = NULL;
    nova_pilha->tamanho = 0;
    return nova_pilha;
}

 Insere dado na pilha (push). Retorna 1 em caso de sucesso e 0 em caso de falha. 
int push(struct pilha *pilha, int dado) {
    struct nodo *novo = novo_nodo(dado);
    if (novo == NULL) {
        return 0;  Falha na alocação de memória 
    }
    novo->prox = pilha->topo;
    pilha->topo = novo;
    pilha->tamanho++;
    return 1;
}

 Remove o topo (pop) e retorna o elemento no parâmetro dado. Retorna 1 em caso de sucesso e 0 se a pilha estiver vazia. 
int pop(struct pilha *pilha, int *dado) {
    if (pilha == NULL || pilha->topo == NULL) {
        return 0;   Pilha está vazia 
    }
    *dado = pilha->topo->chave;
    struct nodo *aux = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(aux);
    pilha->tamanho--;
    return 1;
}

 Retorna o topo da pilha sem removê-lo. Retorna 1 em caso de sucesso e 0 se a pilha estiver vazia. 
int pilha_topo(struct pilha *pilha, int *dado) {
    if (pilha == NULL || pilha->topo == NULL) {
        return 0;  Pilha está vazia 
    }
    *dado = pilha->topo->chave;
    return 1;
}

 Retorna o número de elementos na pilha. 
int pilha_tamanho(struct pilha *pilha) {
    if (pilha == NULL) {
        return 0;
    }
    return pilha->tamanho;
}

 Verifica se a pilha está vazia (1 se vazia, 0 caso contrário). 
int pilha_vazia(struct pilha *pilha) {
    if (pilha == NULL || pilha->topo == NULL) {
        return 1;   Pilha está vazia 
    }
    return 0;   Pilha não está vazia 
}

 Desaloca toda a memória da pilha e faz pilha receber NULL. 
void pilha_destroi(struct pilha **pilha) {
    if (pilha == NULL || *pilha == NULL) {
        return;
    }
    while ((*pilha)->topo != NULL) {
        struct nodo *aux = (*pilha)->topo;
        (*pilha)->topo = (*pilha)->topo->prox;
        free(aux);
    }
    free(*pilha);
    *pilha = NULL;
}

FIM IMPLEMENTAÇÃO CHAT GPT
*/

/*
 * Cria e retorna uma nova pilha.
 * Retorna NULL em caso de erro de alocação.
*/ 
struct pilha *pilha_cria (){
	struct pilha *p;	

	p = malloc(sizeof(struct pilha));
	if(!p) return NULL;
	
	p->topo = NULL;
	p->tamanho = 0;
	
	return p;
}

/* Desaloca toda memoria da pilha e faz pilha receber NULL. */
void pilha_destroi (struct pilha **pilha){
	struct nodo *aux;
	
	if(!pilha || !(*pilha)) return;
	
	while((*pilha)->topo != NULL){
		aux = (*pilha)->topo;
		(*pilha)->topo = (*pilha)->topo->prox;
		free(aux);
	}
	free(*pilha);
	*pilha = NULL;
}
/*

 Desaloca toda a memória da pilha e faz pilha receber NULL. 
void pilha_destroi(struct pilha **pilha) {
    if (pilha == NULL || *pilha == NULL) {
        return;
    }
    while ((*pilha)->topo != NULL) {
        struct nodo *aux = (*pilha)->topo;
        (*pilha)->topo = (*pilha)->topo->prox;
        free(aux);
    }
    free(*pilha);
    *pilha = NULL;
}

*/

/*
 * Insere dado na pilha (politica LIFO). Retorna 1
 * em caso de sucesso e 0 em caso de falha.
*/
int push (struct pilha *pilha, int dado){
	struct nodo *nodo;
	
	if(!pilha) return 0;
	nodo = malloc(sizeof(struct nodo));
	if(!nodo) return 0;

	nodo->chave = dado;
	nodo->prox = pilha->topo;
	pilha->topo = nodo;
	pilha->tamanho++;

	return 1;
}	

/*
 * Remove o topo (politica LIFO) e retorna o elemento 
 * no parametro dado. A funcao retorna 1 em caso de 
 * sucesso e 0 no caso da pilha estar vazia.
*/
int pop (struct pilha *pilha, int *dado){
	struct nodo *aux;
	
	if(!pilha) return 0;

	if(pilha->tamanho == 0) return 0;
	
	*dado = pilha->topo->chave;
	aux = pilha->topo;
	pilha->topo = aux->prox;
	pilha->tamanho--;
	free(aux);	
	
	return 1;
}

/*
 * Similar ao pop, mas retorna o elemento dado sem remove-lo. 
 * A funcao retorna 1 em caso de sucesso e 0 no caso 
 * da pilha estar vazia.
*/
int pilha_topo (struct pilha *pilha, int *dado){
	if(!pilha) return 0;
	/* retorna 0 no caso da pilha estar vazia */
	if(pilha->tamanho == 0) return 0;
	
	*dado = pilha->topo->chave;
	
	return 1;
}

/* Retorna o numero de elementos da pilha, que pode ser 0. */
int pilha_tamanho (struct pilha *pilha){
	if(!pilha) return -1;

	return pilha->tamanho;
}

/* Retorna 1 se pilha vazia, 0 em caso contrario. */ 
int pilha_vazia (struct pilha *pilha){
	if(!pilha) return 0;

	if(pilha->tamanho == 0){
		return 1;
	}
	return 0;
}


