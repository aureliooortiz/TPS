/* TP3 - A diferenca desta implementação com relacao ao TP2
 * eh que os racionais devem alocados dinamicamente */
#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
int mdc (int a, int b){
	if(a % b == 0){
		return b;
	}
	return mdc(b, a%b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc (int a, int b){
	int absA;
	int absB;
	int maxDiv;

	absA = abs(a); 		//mdc com o modulo de a e b para nao haver erro com numeros negativos
	absB = abs(b);
	maxDiv = mdc(absA, absB);

	return (a*b) / maxDiv;
}

struct racional *cria_r (long int numerador, long int denominador){
	struct racional *rac;
	
	rac = malloc(sizeof(struct racional));
	
	if(!rac){
		return NULL;
	}
	numerador_r(rac,&numerador); 
	denominador_r(rac,&denominador);
	
	return rac;
}

void destroi_r (struct racional *r){
	if(!r){
		return;
	}
	
	free(r);
}

int numerador_r (struct racional *r, long int *num){	
	if(!r){ 
		return 0;
	}
	
	r->num = *num;
	
	return 1;
}

int denominador_r (struct racional *r, long int *den){
	r->den = *den;
	if(valido_r(r) == 0){
		return 0;
	}
	
	return 1;
}

int valido_r (struct racional *r){
	if(r->den == 0 || !r){
		return 0;
	}
	return 1;
}

void imprime_r (struct racional *r){
	if(!r){
		printf("NULO");
		return;
	}
	
	if(valido_r(r) < 1){
		printf("INVALIDO");
		return;
	}
	
	simplifica_r(r);
	
	if(r->num == 0 || r->den == 1){
		printf("%ld", r->num);
		return;
	}
	
	printf("%ld/%ld", r->num,r->den);
}

int compara_r (struct racional *r1, struct racional *r2){
	long int m;
	long int rac1;
	long int rac2;
	
	m = mmc(r1->den, r2->den);
	
	rac1 = (m / r1->den) * r1->num;
	rac2 = (m / r2->den) * r2->num;
	
	if(valido_r(r1) == 0 || valido_r(r2) == 0){
		return -2;
	}
	if (rac1 < rac2){
		return -1;
	}
	if(rac1 == rac2){
		return 0; 
	}
	if(rac1 > rac2){
		return 1;
	}
	return 0;
}

int simplifica_r (struct racional *r){
	int absNum;
	int absDen;
	int maxDiv;

	if(valido_r(r) < 1 || !r){
		return 0;
	}			//verifica se o numero pode ser simplificado 
	if(r->num == 0){
		return 1;
	}
	
	absNum = abs(r->num); 		//os numeros estao em modulo para que nao ocorra erro ao simplificar numeros negativos
	absDen = abs(r->den);
	maxDiv = mdc(absNum, absDen);

        r->num /= maxDiv;
        r->den /= maxDiv;
       
	if(((r->num < 0) && (r->den < 0)) || ((r->num > 0) && (r->den < 0))){ //regra de sinal e deixar no formato padrao de negativo
		r->num *= -1;
		r->den *= -1;
	}
        
        return 1;
}

int soma_r (struct racional *r1, struct racional *r2, struct racional *r3){	

	r3->den = r1->den * r2->den;
	r3->num = (r1->num * (r3->den / r1->den))+(r2->num * (r3->den / r2->den));

	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(r3) == 0)){
		return 0;
	}
	simplifica_r(r3);

	return 1;
}

int subtrai_r (struct racional *r1, struct racional *r2, struct racional *r3){
	
	r3->den = r1->den * r2->den;
        r3->num = ((r3->den / r1->den)*(r1->num))-((r3->den / r2->den)*(r2->num));
	
	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(r3) == 0)){
		return 0;
	}
	simplifica_r(r3);

	return 1;
}

int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3){

	r3->num = r1->num * r2->num;	
	r3->den = r1->den * r2->den;
	
	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(r3) == 0)){
		return 0;
	}
	simplifica_r(r3);
	
	return 1;
}

int divide_r (struct racional *r1, struct racional *r2, struct racional *r3){

	if((r2->num == 0)){			//caso de divisao invalida
		r2->den = r2->num * r2->den;
		valido_r(r3);
		return 0;         
	}
	r3->num = r1->num * r2->den;
	r3->den = r1->den * r2->num;

	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(r3) == 0)){
		return 0;
	}
	simplifica_r(r3);
	
	return 1;
}


