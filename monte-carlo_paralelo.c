/* Marilene Garcia - 10276974 */

/*Calculo de pi com o método de Monte Carlo usando big-numbers e threads*/


/* Forma de compilar o codigo */
//gcc nome_arquivo.c -o nome_executavel -lgmp -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <pthread.h>

#define numero_iteracoes 25000000
#define numero_threads 4

/* declaracao das variaveis globais */
mpf_t pontos_totais, pontos_circunferencia_total, pontos_circunferencia[numero_threads], pi;

/* Funcoes usadas */
void* monteCarlo(void* count);

/* Algoritmo */
int main(){
    /*inicializacao das variaveis*/
    mpf_init2 (pontos_totais,10000000);           
    mpf_init2 (pontos_circunferencia_total,10000000);
    mpf_init2 (pi,10000000); 

    /* pontos = numero threads * numero de iteracoes */
    int total_pontos = numero_threads * numero_iteracoes;
    mpf_set_ui(pontos_totais, total_pontos);

    mpf_set_ui(pontos_circunferencia_total, 0);
    pthread_t id_threads[numero_threads];

    /* Criar as threads */
    int count = 0;
    for(count = 0; count < numero_threads; count ++){
        pthread_create (&id_threads[count], NULL, monteCarlo, &count);        
    }

    /* Esperar a conclusao de todas as threads*/
    for(count = 0; count < numero_threads; count ++){ 
        pthread_join (id_threads[count], NULL);        
    }

    for(int count = 0; count < numero_threads; count ++){ 
        mpf_add(pontos_circunferencia_total, pontos_circunferencia_total, pontos_circunferencia[count]);
        mpf_clear (pontos_circunferencia[count]);
    }
    
    /* Calculo de Pi */
    mpf_div(pi, pontos_circunferencia_total, pontos_totais);
    mpf_mul_ui(pi, pi, 4);
    
    mpf_out_str (stdout, 10, 6, pi);
    printf("\n");
    /* Desalocar a memória dos big-numbers */
    mpf_clear (pontos_totais);
    mpf_clear (pontos_circunferencia_total);
    mpf_clear (pi);
  
  return 0;
}

void* monteCarlo(void* count){
    double x,y;
    int numero_thread = *((int *)count);
    mpf_init2 (pontos_circunferencia[numero_thread],10000000);
    for(int count = 0; count < numero_iteracoes; count ++){
        /*Atribuir uma coordenada aleatoria ao x e ao y
        normalizada entre 0 e 1 sendo que a circunferencia 
        esta centrada na origem e tem raio igual a RAND_MAX*/
        x = ((double)rand()/(double)RAND_MAX); 
        y = ((double)rand()/(double)RAND_MAX);

        /* Inequacao do interior da circunferencia:
        x*x + y*y <= 1 */
        if(x*x + y*y <= 1){
        mpf_add_ui(pontos_circunferencia[numero_thread], pontos_circunferencia[numero_thread], 1);
        }
    }
    pthread_exit(0);
}