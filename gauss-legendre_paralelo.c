/* Marilene Garcia - 10276974 */

/*Calculo de pi com o método de Gauss-Legendre usando big-numbers e threads*/

/* Forma de compilar o codigo */
//gcc nome_arquivo.c -o nome_executavel -lgmp -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <pthread.h>

#define numero_interacoes 1000

/* declaracao das variaveis globais */
mpf_t an, an_aux, bn, tn, tn_aux, pn, pi_aux, pi;

/* Funcoes usadas */
void gaussLagendre();
void* determinar_an();
void* determinar_bn();

/* Algoritmo */
int main(){

  gaussLagendre();
  
  return 0;
}

void gaussLagendre(){
    /*inicializacao das variaveis*/
    mpf_init2 (an,10000000);           
    mpf_init2 (bn,10000000);
    mpf_init2 (tn,10000000);           
    mpf_init2 (pn,10000000);
    mpf_init2 (an_aux,10000000);
    mpf_init2 (tn_aux,10000000);           
    mpf_init2 (pi,10000000);
    mpf_init2 (pi_aux,10000000);

    /*Valores iniciais do algoritmo*/
    
    /*  an = 1  */
    mpf_set_ui(an,1);

    /*  bn = 1 / sqrt(2)  */
    mpf_set_ui (bn,2);
    mpf_sqrt (bn,bn);
    mpf_ui_div(bn, 1, bn);

    /*  tn = 1 / 4  */
    mpf_set_ui(tn,1);
    mpf_div_ui(tn, tn, 4);

    /*  pn = 1  */
    mpf_set_ui(pn,1);

    /* ID das threads */
    pthread_t id_determinar_an[numero_interacoes];
    pthread_t id_determinar_bn[numero_interacoes];

    /* Iteracoes do algoritmo */
    for(int count = 0; count < numero_interacoes; count ++){
        /*Desenvolvimento do algoritmo*/

        /* Criar as threads para determinar an e bn */
        pthread_create (&id_determinar_an[count], NULL, determinar_an, &count);
        pthread_create (&id_determinar_bn[count], NULL, determinar_bn, &count);        

        /* Aguardar todas as threads serem concluidas */
        pthread_join(id_determinar_an[count], NULL);
        pthread_join(id_determinar_bn[count], NULL);
        
        /* Determinar tn */
        mpf_sub(tn_aux, an, an_aux);
        mpf_pow_ui(tn_aux,tn_aux,2.0);
        mpf_mul(tn_aux, pn, tn_aux);
        mpf_sub(tn, tn, tn_aux);

        mpf_set(an,an_aux);

        /* Determinar pn */
        mpf_mul_ui(pn, pn, 2);

         mpf_add(pi, an, bn);
        mpf_pow_ui(pi, pi, 2);
        mpf_mul_ui(pi_aux, tn, 4);
        mpf_div(pi, pi, pi_aux);


        mpf_out_str (stdout, 10, 6, pi);
        printf("\n");
    }

    /* Determinar PI */
   


    /* Desalocar a memória dos big-numbers */
    mpf_clear (an);
    mpf_clear (bn);
    mpf_clear (tn);
    mpf_clear (pn);
    mpf_clear (an_aux);
    mpf_clear (tn_aux);
    mpf_clear (pi);
    mpf_clear (pi_aux);
}

void* determinar_an(){
    mpf_add (an_aux, an, bn);
    mpf_div_ui(an_aux, an_aux, 2);

    pthread_exit(0);
}

void* determinar_bn(){
    mpf_mul(bn, an, bn);
    mpf_sqrt (bn,bn);

    pthread_exit(0);
}