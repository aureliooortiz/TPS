#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

/*
struct conjunto {
    int max;    // tamanho maximo do vetor atualmente alocado     
    int card;   // cardinalidade, isto eh, tamanho usado ate max  
    int ptr;    // ponteiro para algum indice do vetor (iterador) 
    int *v;     // vetor de inteiros com no maximo max elementos  
};
*/

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
 */
struct conjunto *cria_cjt (int max){
	struct conjunto *c;
	
	c = malloc(sizeof(struct conjunto));
	if(!c) return NULL;
	c->v = malloc(max * sizeof(int));
	
	//numero maximo de elementos
	c->max = max;
	//numero atual de elementos no vetor	
	c->card = 0; 
	
	return c;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
 */
struct conjunto *destroi_cjt (struct conjunto *c){
	int i;
	
	if(!c || !c->v) return NULL;
	
	//retira todos os elementos do conjunto
	//começando do ultimo até o primeiro
	i = c->card-1;
	while(!vazio_cjt(c)){
		retira_cjt(c,c->v[i]);
		i--;
	}
	free(c->v);
	free(c);
	
	return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
 */
int vazio_cjt (struct conjunto *c){
	if(!c || !c->v) return -1;
	
	if(c->card > 0){
		return 0;
	}
	return 1;
}
/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
 */
int cardinalidade_cjt (struct conjunto *c){
	if(!c || !c->v) return 0;

	return c->card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida. Se tentar inserir elemento existente,
 * nao faz nada e retorna 1 tambem. Retorna 0 em caso de falha por falta de espaco.
 */
int insere_cjt (struct conjunto *c, int elemento){
	if(!c || !c->v) return -1;
	
	//verifica se o conjunto não está cheio
	if(c->card == c->max) return 0;
	
	//verifica se não irá repetir elementos
	for(int i = 0; i < c->card;i++){
		if(elemento == c->v[i]){
			return 1;
		}
	}
	c->v[c->card] = elemento;
	c->card++;

	return 1;
}

/*
 * Remove o elemento 'elemento' do conjunto caso ele exista.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
 */
int retira_cjt (struct conjunto *c, int elemento){
	int exist;
	int temp;
	int pos;
	int i;
	
	if(!c || !c->v) return 0;
	
	//percorre o conjunto e para se verificar todos os
	//elementos ou se provar que o elemento existe no conjunto
	i = 0;
	exist = 0;
	while(!exist && i < c->card){
		if(elemento == c->v[i]){
			//coloca em pos a posição
			//de onde está o elemento
			pos = i;
			exist = 1;
		}
		i++;
	}
	if(!exist){
		return 0;
	}
	
	//troca a ultima posição com
	//a posição do elemento que deseja retirar
	temp = c->v[c->card-1];
	c->v[c->card-1] = c->v[pos];
	c->v[pos] = temp;
	c->card--;
	
	return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
 */
int pertence_cjt (struct conjunto *c, int elemento){
	if(!c || !c->v) return 0;
	
	//percorre o conjunto, se achar o elemento retorna
	for(int i = 0;i < c->card;i++){
		if(elemento == c->v[i]){
			return 1;
		}
	}
	return 0;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
 */
int contido_cjt (struct conjunto *c1, struct conjunto *c2){
	int contem;
	
	if(!c1 || !c1->v) return 0;
	if(!c2 || !c2->v) return 0;
	
	contem = 0;
	for(int k = 0;k < c1->card;k++){
		for(int j = 0; j < c2->card;j++){
			if(c1->v[k] == c2->v[j]){
				contem++;
			}		
		}	
	}
	if(contem != c1->card){
		return 0;
	}
	return 1;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
 */
int sao_iguais_cjt (struct conjunto *c1, struct conjunto *c2){
	int iguais;
	int k;
	
	if(!c1 || !c1->v) return 0;
	if(!c2 || !c2->v) return 0;
	
	//se não tiverem a mesma quantidade
	//de elementos não são iguais
	if(c1->card != c2->card){
		return 0;
	}
	
	//percorre o vetor e para quando acha
	//um diferente ou se percorreu todo o vetor
	iguais = 1;
	k = 0;
	while(iguais && k < c1->card){
		for(k = 0;k < c1->card;k++){
			if(c1->v[k] != c2->v[k]){
				iguais = 0;
			}
		}
	}
	
	if(!iguais){
		return 0;
	}
	return 1;
}

/*
 * Cria e retorna o conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *diferenca_cjt (struct conjunto *c1, struct conjunto *c2){
	struct conjunto *d;
	int elemento;
	int presente;
	int max;
	
	if(!c1 || !c1->v) return NULL;
	if(!c2 || !c2->v) return NULL;
		
	//coloca em max a soma das capacidades de c1 e c2
	max = c1->max + c2->max;
	d = cria_cjt(max);
		
	//verifica a diferença entre c1 e c2
	for (int i = 0; i < c1->card; i++) {
		elemento = c1->v[i];
		presente = 0;
		//verifica se o elemento está presente em c2
		for (int j = 0; j < c2->card; j++){
			if (c2->v[j] == elemento){
				presente = 1;
				break;
			}
    	}
		//se o elemento não estiver em c2, insira-o em 'd'
		if(!presente){
			insere_cjt(d, elemento);
    	}
    }
	return d;
}
/*
 * Cria e retorna o conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *interseccao_cjt (struct conjunto *c1, struct conjunto *c2){
	struct conjunto *i;
	int max;
	int min;
	
	if(!c1 || !c1->v) return NULL;
	if(!c2 || !c2->v) return NULL;
	
	//coloca em max a soma das capacidades de c1 e c2
	max = c1->max + c2->max;
	i = cria_cjt(max);
	
	//coloca em min a menor capacidade de elementos
	//entre c1 e c2
	min = c1->card;
	//coloca em max a maior capacidade de elementos
	//entre c1 e c2
	max = c2->card;
	if(c1->card > c2->card){
		min = c2->card;
		max = c1->card;
	}
	//faz a intersecção percorrendo o vetor
	//até atingir a menor cardinalidade entre c1 e c2
	//comparando o primeiro elemento do menor conjunto
	//com o restante do maior conjunto
	if(min == c1->card){	
		for(int k = 0;k < min;k++){
			for(int j = 0;j < max;j++){
				if(c1->v[k] == c2->v[j]){
					insere_cjt(i,c1->v[k]);	
				}
			}
		}
	}else{
		for(int k = 0;k < min;k++){
			for(int j = 0;j < max;j++){
				if(c2->v[k] == c1->v[j]){
					insere_cjt(i,c1->v[k]);	
				}
			}
		}
	}
	return i;
}

/*
 * Cria e retorna o conjunto uniao entre os conjunto c1 e c2.
 * Retorna NULL se a operacao falhou.
 */
struct conjunto *uniao_cjt (struct conjunto *c1, struct conjunto *c2){
	struct conjunto *u;
	int max;
	int min;
	
	if(!c1 || !c1->v) return NULL;
	if(!c2 || !c2->v) return NULL;
	
	//coloca em max a soma das capacidades de c1 e c2
	max = c1->max + c2->max;
	u = cria_cjt(max);
	
	//coloca em min a menor capacidade de elementos
	//entre c1 e c2
	min = c1->card;
	//coloca em max a maior capacidade de elementos
	//entre c1 e c2
	max = c2->card;
	if(c1->card > c2->card){
		min = c2->card;
		max = c1->card;
	} 
	//insere os elementos dos conjuntos c1 e c2 
	//em ordem crescente no conjunto u	
	for(int i = 0;i < min;i++){
		if(c1->v[i] < c2->v[i]){
			insere_cjt(u, c1->v[i]);
		}else{
			insere_cjt(u, c2->v[i]);
		}	
	}
	//coloca o restante do que sobrou no maior
	//conjunto no conjunto u
	if(min == c1->card){
		for(int i = 0;i < max;i++){
			insere_cjt(u, c2->v[i]);
		}	
	}else{
		for(int i = 0;i < max;i++){
			insere_cjt(u, c1->v[i]);
		}	
	}
	return u;
}

/*
 * Cria e retorna uma copia do conjunto c e NULL em caso de falha.
 */
struct conjunto *copia_cjt (struct conjunto *c){
	struct conjunto *cp;

	if(!c || !c->v) return NULL;

	cp = cria_cjt (c->max);

	for(int i = 0;i < c->card;i++){
		cp->v[i] = c->v[i];
		cp->card++;
	}
	
	return cp;
}

/*
 * Cria e retorna um subconjunto com elementos aleatorios do conjunto c.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand () tenha sido chamada antes. 
 */
struct conjunto *cria_subcjt_cjt (struct conjunto *c, int n){
	struct conjunto *sub;
	int pos;
	int i;
	
	if(!c || !c->v) return NULL;

	sub = cria_cjt(c->max);
	//se o conjunto for vazio retorna um subconjunto vazio.
	if(c->card == 0) return sub;
	//se n >= cardinalidade (c) entao retorna o proprio conjunto c.
	if(n >= c->card) return c;
	
	//posições do vetor sub
	i = 0;
	//loop que adiciona ao subconjunto 
	//elementos aleatorios n vezes
	for(int l = 0;l < n;l++){
		//aleatoriza uma posição, coloca essa posição no conjunto
		pos = rand() % c->card;
		sub->v[i] = c->v[pos];
		i++;
		sub->card++;
		//garante que o elemento não se repita
		for(int k = 0;k < sub->card;k++){
			for(int j = k+1; j < sub->card;j++){
				if(sub->v[k] == sub->v[j]){
					retira_cjt(sub,sub->v[j]);
					i--;
					l--;
				}
			}
		}
	}
	return sub;
}

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
 * Na impressao os elementos sao separados por um unico espaco
 * em branco entre os elementos, sendo que apos o ultimo nao
 * deve haver espacos em branco. Ao final imprime um \n.
 */
void imprime_cjt (struct conjunto *c){
	int *vet;
	int menor;
	int aux;
	int k,j;
	
	if(!c || !c->v) return;
		
	if(c->card == 0){
		printf("conjunto vazio\n");
		return;
	}

	//vetor que será usado para ordenar o conjunto
	vet = malloc((c->card+1) * sizeof(int));
	
	//coloca o conjunto no vetor
	for(int i = 0;i < c->card;i++){
		vet[i] = c->v[i];
	}
	
	//ordena o vetor por Selection Sort
	for(j = 0;j < c->card-1;j++){
		menor = j;
		for(k = j+1;k < c->card;k++){
			if(vet[k] < vet[menor]){
				menor = k;
			}
		}
		aux = vet[menor];
		vet[menor] = vet[j];
		vet[j] = aux;
	}
	
	//imprime o vetor
	for(int i = 0;i < c->card;i++){
		if(i == c->card-1){
			printf("%d",vet[i]);
		}else{
			printf("%d ",vet[i]);
		}	
	}
	
	//libera area alocada para vetor temporario
	free(vet);
	
	printf("\n");
}

/*
 * As funcoes abaixo implementam um iterador que vao permitir
 * percorrer os elementos do conjunto.
 * O ponteiro ptr da struct (iterador) pode ser inicializado para apontar 
 * para o primeiro elemento e incrementado ate' o ultimo elemento 
 * do conjunto.
 */

/*
 * Inicializa ptr usado na funcao incrementa_iterador 
 */
void inicia_iterador_cjt (struct conjunto *c){
	if(!c || !c->v) return;
	
	//aponta para 0, posição inicial
	c->ptr = 0;
}

/*
 * Devolve no parametro ret_iterador o elemento apontado e incrementa o iterador.
 * A funcao retorna 0 caso o iterador ultrapasse o ultimo elemento, ou retorna
 * 1 caso o iterador aponte para um elemento valido (dentro do conjunto).
 */
int incrementa_iterador_cjt (struct conjunto *c, int *ret_iterador){
	if(!c || !c->v) return 0;

	//retorna 0 caso o iterador ultrapasse o ultimo elemento
	if(c->ptr >= c->card) return 0;
	
	*ret_iterador = c->v[c->ptr];
	c->ptr++;
	
	return 1;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido, o remove e
 * o retorna.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
 */
int retira_um_elemento_cjt (struct conjunto *c){
	int pos;
	int retorno;
	
	if(!c || !c->v) return 0;

	pos = rand() % c->card;
	retorno = c->v[pos];
	retira_cjt(c,c->v[pos]);
	
	return retorno;
	
}
