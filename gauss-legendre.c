/* Marilene Garcia - 10276974 */

/*Calculo de pi com o método de Gauss-Legendre usando big-numbers*/

/* Forma de compilar o codigo */
//gcc nome_arquivo.c -o nome_executavel -lgmp

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

#define numero_iteracoes 1000000000

/* Funcoes usadas */
void gaussLagendre();

/* Algoritmo */
int main(){

  gaussLagendre();
  
  return 0;
}

void gaussLagendre(){
      /*inicializacao das variaveis*/
    mpf_t an, bn, tn, pn, an_aux, tn_aux, pi, pi_aux;
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

    /* Iteracoes do algoritmo */
    for(int count = 0; count < numero_iteracoes; count ++){
        /*Desenvolvimento do algoritmo*/

        /* an_aux = (an + bn)/2    */
        mpf_add (an_aux, an, bn);
        mpf_div_ui(an_aux, an_aux, 2);

        /*  bn = sqrt(an*bn)    */
        mpf_mul(bn, an, bn);
        mpf_sqrt (bn,bn);

        /* tn = tn - (pn*pow((an - aux), 2))    */
        mpf_sub(tn_aux, an, an_aux);
        mpf_pow_ui(tn_aux,tn_aux,2.0);
        mpf_mul(tn_aux, pn, tn_aux);
        mpf_sub(tn, tn, tn_aux);

        /*  pn = 2.0*pn */
        mpf_mul_ui(pn, pn, 2);

        /*  an = aux    */   
        mpf_set(an,an_aux);              
    }

    /*Calculo do valor de pi*/
    /*  pi = pow((an + bn), 2) / (4.0*tn)   */
    mpf_add(pi, an, bn);
    mpf_pow_ui(pi, pi, 2);
    mpf_mul_ui(pi_aux, tn, 4);
    mpf_div(pi, pi, pi_aux);  

    mpf_out_str (stdout, 10, 6, pi);
    printf("\n");

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