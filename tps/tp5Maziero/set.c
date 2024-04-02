#include <stdio.h>
#include <stdlib.h>
#include "set.h"

struct set_t *set_create (int max){
	struct set_t *s;
	
	s = malloc(sizeof(struct set_t));
	if(!s) return NULL;
	s->flag = malloc(max * sizeof(bool));
	if(!s->flag) return NULL;
	
	//numero atual de elementos 
	s->num = 0;						
	for(int i = 0; i < max;i++){	
		s->flag[i] = false;	
	}
	//numero maximo de elementos
	s->size = max;					
	return s;
}

struct set_t *set_destroy (struct set_t *s){
	free(s->flag);
	free(s);
	return NULL;
}

int set_add (struct set_t *s, int item){
	if(!s) return 0;
	if(item >= s->size) return 0; 		//se a posicao que deseja adicionar for 	
										//maior ou igual a capacidade retorna
	if(!s->flag[item]){
		s->flag[item] = true;
		s->num++;
		return 1;
	}
	return 0;
}

int set_del (struct set_t *s, int item){
	if(!s) return 0;
	if(item >= s->size) return 0; 		//se a posicao que deseja remover for 	
										//maior ou igual a capacidade retorna
	if(s->flag[item]){
		s->flag[item] = false;
		s->num--;
		return 1;
	}
	return 0;
}

int set_in (struct set_t *s, int item){
	if(!s || !s->flag) return 0;
	//se o item for maior ou igual ao tamanho
	//ou menor que 0 
	//não pertence ao conjunto
	if(item >= s->size || item < 0) return 0;
	
	if(s->flag[item]){
		return 1;
	}
	return 0;
}

//retorna 1 se não estiver vazio
//e 0 se estiver vazio
int set_empty (struct set_t *s){
	if(!s) return 0;	
	
	if(s->num > 0){
		return 1;
	}
	return 0;
}

int set_card (struct set_t *s){
	if(!s) return 0;
	
	if(s->num >= 0){
		return s->num;
	}
	return -1;	
}

int set_contains (struct set_t *s1, struct set_t *s2){
	if(!s1 || !s2 ) return 0;
	if(!s1->flag || !s2->flag) return 0;

	for(int i = 0;i < s1->size;i++){
		if(s1->flag[i] && !s2->flag[i]){
			return 0;
		}
	}
	return 1;
}

int set_equal (struct set_t *s1, struct set_t *s2){
	if(!s1 || !s2 ) return 0;
	if(!s1->flag || !s2->flag) return 0;	
	
	//verifica se ambos tem a mesma quantidade de elementos
	//se não tiverem não são iguais
	if(s1->num != s2->num) return 0;				
	for(int i = 0; i < s1->size;i++){					//verifica se os elementos de cada conjunto
		if(s1->flag[i] != s2->flag[i]){					//são iguais,e para se achar um diferente,	
			return 0;								
		}										
	}											
	return 1;
}

int set_union (struct set_t *s1, struct set_t *s2, struct set_t *s3){
	if(!s1 || !s2 || !s3) return 0;
	if(!s1->flag || !s2->flag || !s3->flag) return 0;

	for(int i = 0;i < s1->size;i++){					//faz a união de s1 e s2
		if(s1->flag[i] || s2->flag[i]){					//e coloca em s3
			s3->flag[i] = true;							
			s3->num++;	
		}
	}
	return 1;	
}	

int set_intersect (struct set_t *s1, struct set_t *s2, struct set_t *s3){
	if(!s1 || !s2 || !s3) return 0;
	if(!s1->flag || !s2->flag || !s3->flag) return 0;
	
	for(int i = 0;i < s1->size;i++){					//faz a intersecção de s1 e s2					
		if(s1->flag[i] && s2->flag[i]){					//e coloca em s3
			s3->flag[i] = true;							
			s3->num++;	
		}
	}
	return 1;
}	

int set_diff (struct set_t *s1, struct set_t *s2, struct set_t *s3){
	if(!s1 || !s2 || !s3) return 0;
	if(!s1->flag || !s2->flag || !s3->flag) return 0;
		
	for(int i = 0;i < s1->size;i++){					//faz a diferença de s1 e s2					
		if(s1->flag[i] && !s2->flag[i]){				//e coloca em s3
			s3->flag[i] = true;							
			s3->num++;	
		}
	}
	return 1;	
}

int set_copy (struct set_t *s1, struct set_t *s2){
	if(!s1 || !s2) return 0;
	if(!s1->flag || !s2->flag) return 0;
	
	s2->num = 0;			//reseta a cardinalidade		
	for(int i = 0; i < s1->size;i++){
		s2->flag[i] = s1->flag[i];
		if(s2->flag[i]){
			s2->num++;
		}
	}
	return 1;
}

void set_print (struct set_t *s){
	if(!s || !s->flag) return;
	
	printf("[ ");
	for(int i = 0;i < s->size;i++){
		printf("%d ",s->flag[i]);
	}
	printf("]");
	printf("\n");
}
/*
Professor deixei o set print ir até 37
pois se fosse até o s->size, a saída
ficava confusa e muito grande,
e 35 é a ultima posição em que é adicionado
um item ao conjunto, por não pertencer ao TAD
acredito que não há problema
*/
