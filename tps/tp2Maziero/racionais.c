#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){
	return min + rand() % (max-min + 1);
}

/* Maximo Divisor Comum entre a e b      */
int mdc (int a, int b){
	if(a % b == 0){
		return b;
	}
	return mdc(b, a%b);
}

/* Minimo Multiplo Comum entre a e b */
int mmc (int a, int b){
	int absA;
	int absB;
	int maxDiv;

	absA = abs(a); 		/*mdc com o modulo de a e b para nao haver erro com numeros negativos*/
	absB = abs(b);
	maxDiv = mdc(absA, absB);

	return (a*b) / maxDiv;
}

struct racional cria_r (int numerador, int denominador){
	struct racional racional_r;

	racional_r.num = numerador;
	racional_r.den = denominador;
	racional_r.valido = valido_r(racional_r);

	return racional_r;
}

/*sorteia um racional entre -max e max*/
struct racional sorteia_r (int max){
	int nume;
	int deno;
	struct racional rac;
	
	nume = aleat(-max, max);
	deno = aleat(-max,max);
	
	rac = cria_r(nume,deno);
	
	if(rac.valido == 0 || rac.num == 0){ /*verifica numero valido antes de chamar a funcao simplifica*/
		return rac;
	}
	
	simplifica_r(&rac);
	
	return rac;
}

int numerador_r (struct racional r){
	return r.num;
}

int denominador_r (struct racional r){
	return r.den;
}

int valido_r (struct racional r){
	if(denominador_r(r) == 0){
		return 0;
	}
	return 1;
}

/*imprime com verificacao de casos especificos*/
void imprime_r (struct racional r){

	if(valido_r(r) == 0){
		printf("INVALIDO");
		return;
	}	
	if(numerador_r(r) == 0){     
		printf("0");		    	            
		return;
	}
	
	simplifica_r(&r);
	
	if(denominador_r(r) == 1){											
		printf("%d", r.num);
		return;
	}
	
	printf("%d/%d",r.num, r.den);
}

/* faz a comparacao de racionais */
int compara_r (struct racional r1, struct racional r2){
	float rac1;
	float rac2;
	
	rac1 = r1.num;
	  
	rac2 = r2.num; 
	
	rac1 = rac1 / r1.den ;
	rac2 = rac2 / r2.den ;
	
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
	
	if(valido_r(*r) == 0){ 		/*verifica se o numero pode ser simplificado*/
	        return 0;
	}
	if(numerador_r(*r) == 0){
		return 1;
	}
	
	absNum = abs(r->num); 		/*os numeros estao em modulo para que nao ocorra erro ao simplificar numeros negativos*/
	absDen = abs(r->den);
	maxDiv = mdc(absNum, absDen);

        r->num /= maxDiv;
        r->den /= maxDiv;
       
        if(((r->num < 0) && (r->den < 0)) || ((r->num > 0) && (r->den < 0))){ /*regra de sinal e deixar no formato padrao de negativo*/
		r->num *= -1;
		r->den *= -1;
	}
        
        return 1;
}

int soma_r (struct racional r1, struct racional r2, struct racional *r3){
	
	r3->den = r1.den * r2.den;
	r3->num = ((r3->den / r1.den)*(r1.num))+((r3->den / r2.den)*(r2.num));
	r3->valido = valido_r(*r3);

	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(*r3) == 0)){
		return 0;
	}

	return 1;
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
	
	r3->den = r1.den * r2.den;
        r3->num = ((r3->den / r1.den)*(r1.num))-((r3->den / r2.den)*(r2.num));
	r3->valido = valido_r(*r3);

	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(*r3) == 0)){
		return 0;
	}

	return 1;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){

	r3->num = r1.num * r2.num;	
	r3->den = r1.den * r2.den;
	r3->valido = valido_r(*r3);
	
	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(*r3) == 0)){
		return 0;
	}
	
	return 1;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3){

	if((numerador_r(r2) == 0)){			/*caso de divisao invalida*/
		r2.den = r2.num * r2.den;
		r3->valido = valido_r(*r3);
		return 0;         
	}
	r3->num = r1.num * r2.den;
	r3->den = r1.den * r2.num;
	r3->valido = valido_r(*r3);
	
	if((valido_r(r1) == 0) || (valido_r(r2) == 0) || (valido_r(*r3) == 0)){
		return 0;
	}
	return 1;

}
