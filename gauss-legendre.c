#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>

/*Calculo de pi com o método de Gauss-Legendre usando big-numbers*/

int main(){
    /*inicializacao das variaveis*/
    mpf_t an, bn, tn, pn, an_aux, tn_aux, pi, pi_aux;
    mpf_init2 (an,512);           
    mpf_init2 (bn,512);
    mpf_init2 (tn,512);           
    mpf_init2 (pn,512);
    mpf_init2 (an_aux,512);
    mpf_init2 (tn_aux,512);           
    mpf_init2 (pi,512);
    mpf_init2 (pi_aux,512);
      
    int count = 0;
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



    //mpf_pow_ui (bn, bn, -1);
   /* mpf_out_str (stdout, 10, 512, an);
    printf("\n");
    
    mpf_out_str (stdout, 10, 512, bn);
    printf("\n");
    
    mpf_out_str (stdout, 10, 512, tn);
    printf("\n");

    mpf_out_str (stdout, 10, 512, pn);
    printf("\n");
*/
    for(count = 0; count < 10; count ++){
        /*Desenvolvimento do algoritmo*/
        
        /* an_aux = (an + bn)/2    */
        mpf_add (an_aux, an, bn);
        mpf_div_ui(an_aux, an_aux, 2);

        /*  bn = sqrt(an*bn)    */
        mpf_mul(bn, an, bn);
        mpf_sqrt (bn,bn);

        /* tn = tn - (pn*pow((an - aux), 2))    */
        mpf_sub(tn_aux, an, an_aux);
        mpf_pow_ui(tn_aux,tn_aux,2);
        mpf_mul(tn_aux, pn, tn_aux);
        mpf_sub(tn, tn, tn_aux);

        /*  pn = 2.0*pn */
        mpf_mul_ui(pn, pn, 2);

        /*  an = aux    */   
        mpf_set(an,an_aux);                       
        

        /*Calculo do valor de pi*/
        
        /*  pi = pow((an + bn), 2) / (4.0*tn)   */
        mpf_add(pi, an, bn);
        mpf_mul_ui(pi,pi, 2);
        mpf_mul_ui(pi_aux, tn, 4);
        mpf_div(pi, pi, pi_aux);  

    
       mpf_clear (an);
       mpf_clear (bn);
       mpf_clear (tn);
       mpf_clear (pn);
       mpf_clear (an_aux);
       mpf_clear (tn_aux);
       mpf_clear (pi);
       mpf_clear (pi_aux);

       mpf_out_str (stdout, 10, 512, pi);
        printf("\n");


    }
}

//g++ mycxxprog.cc -lgmpxx -lgmp