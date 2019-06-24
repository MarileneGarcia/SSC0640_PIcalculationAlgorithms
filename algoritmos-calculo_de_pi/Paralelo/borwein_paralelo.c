/* Marilene Garcia - 10276974 */

/*Calculo de pi com a fómula BBP(Bailey–Borwein–Plouffe) usando big-numbers e threads*/

/* Forma de compilar o codigo */
//gcc nome_arquivo.c -o nome_executavel -lgmp -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <pthread.h>

#define numero_iteracoes 1000000000

/* declaracao das variaveis globais */
mpf_t aux1, aux2, aux3, aux4, aux5, aux_pi, pi;
int k;

/* Funcoes usadas */
void borwein();
void* determinar_aux1();
void* determinar_aux2();
void* determinar_aux3();
void* determinar_aux4();
void* determinar_aux5();

/* Algoritmo */
int main(){

  borwein();
  
  return 0;
}

void borwein(){
    /*inicializacao das variaveis*/
   mpf_init2 (aux1,10000000);           
    mpf_init2 (aux2,10000000);
    mpf_init2 (aux3,10000000);           
    mpf_init2 (aux4,10000000);
    mpf_init2 (aux5,10000000);
    mpf_init2 (aux_pi,10000000);
    
    mpf_init2 (pi,10000000);
    mpf_set_ui(pi, 0);

    /* ID das threads */
    pthread_t id_determinar_aux1[numero_iteracoes];
    pthread_t id_determinar_aux2[numero_iteracoes];
    pthread_t id_determinar_aux3[numero_iteracoes];
    pthread_t id_determinar_aux4[numero_iteracoes];
    pthread_t id_determinar_aux5[numero_iteracoes];

    /* Iteracoes do algoritmo */
    for(k = 0; k < numero_iteracoes; k ++){
        /*Desenvolvimento do algoritmo*/

        /* Criar as threads para determinar aux1, aux2, aux3, aux4 e aux5 */
        pthread_create (&id_determinar_aux1[k], NULL, determinar_aux1, &k);
        pthread_create (&id_determinar_aux2[k], NULL, determinar_aux2, &k);
        pthread_create (&id_determinar_aux3[k], NULL, determinar_aux3, &k);
        pthread_create (&id_determinar_aux4[k], NULL, determinar_aux4, &k);
        pthread_create (&id_determinar_aux5[k], NULL, determinar_aux5, &k);     

        /* Aguardar todas as threads serem concluidas */
        pthread_join(id_determinar_aux1[k], NULL);
        pthread_join(id_determinar_aux2[k], NULL);
        pthread_join(id_determinar_aux3[k], NULL);
        pthread_join(id_determinar_aux4[k], NULL);
        pthread_join(id_determinar_aux5[k], NULL);
        
        /* aux_pi = aux1 * (aux2 - aux3 - aux4 - aux5)    */
        mpf_sub(aux_pi, aux2, aux3);
		mpf_sub(aux_pi, aux_pi, aux4);
		mpf_sub(aux_pi, aux_pi ,aux5);
		mpf_mul(aux_pi, aux1, aux_pi);

        /* Calculo de pi
        pi = pi + aux_pi */
        mpf_add(pi, pi, aux_pi);
        mpf_out_str (stdout, 10, 6, pi);
        printf("\n");


        mpf_out_str (stdout, 10, 6, pi);
        printf("\n");
    }

    /* Desalocar a memória dos big-numbers */
    mpf_clear (aux1);
    mpf_clear (aux2);
    mpf_clear (aux3);
    mpf_clear (aux4);
    mpf_clear (aux5);
    mpf_clear (aux_pi);
    mpf_clear (pi);
}

void* determinar_aux1(){
   /* aux1 = 1/(16^k)    */
    mpf_set_ui(aux1, 16);
    mpf_pow_ui(aux1, aux1, k);
    mpf_ui_div(aux1, 1, aux1);

    pthread_exit(0);
}

void* determinar_aux2(){
    /*  aux2 = 4/(8k + 1)    */
    mpf_set_ui(aux2, 8);
    mpf_mul_ui(aux2, aux2, k);
    mpf_add_ui(aux2, aux2, 1);
    mpf_ui_div(aux2, 4, aux2);

    pthread_exit(0);
}

void* determinar_aux3(){
    /* aux3 = 2/(8k + 4)    */
    mpf_set_ui(aux3, 8);
    mpf_mul_ui(aux3, aux3, k);
    mpf_add_ui(aux3, aux3, 4);
    mpf_ui_div(aux3, 2, aux3);

    pthread_exit(0);
}

void* determinar_aux4(){
    /* aux4 = 1/(8k + 5)    */
    mpf_set_ui(aux4, 8);
    mpf_mul_ui(aux4, aux4, k);
    mpf_add_ui(aux4, aux4, 5);
    mpf_ui_div(aux4, 1, aux4);

    pthread_exit(0);
}

void* determinar_aux5(){
    /* aux5 = 1/(8k + 6)    */
    mpf_set_ui(aux5, 8);
    mpf_mul_ui(aux5, aux5, k);
    mpf_add_ui(aux5, aux5, 6);
    mpf_ui_div(aux5, 1, aux5);

    pthread_exit(0);
}
