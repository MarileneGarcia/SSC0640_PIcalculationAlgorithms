/* Marilene Garcia - 10276974 */

/*Calculo de pi com o método de Monte Carlo usando big-numbers*/

/* Forma de compilar o codigo */
//gcc nome_arquivo.c -o nome_executavel -lgmp

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

#define numero_iteracoes 1000000000

/* Funcoes usadas */
void monteCarlo();

/* Algoritmo */
int main(){

  monteCarlo();
  
  return 0;
}

void monteCarlo(){
     //definindo a precisao
    //mpf_set_default_prec(pow(10,5)); Precisa? 

    /*inicializacao das variaveis*/
    mpf_t pontos_totais, pontos_circunferencia, pi;
    mpf_init2 (pontos_totais,10000000);           
    mpf_init2 (pontos_circunferencia,10000000);
    mpf_init2 (pi,10000000);           
    double x,y;

    //pontos = numero de iteracoes
    mpf_init_set_ui(pontos_totais, numero_iteracoes);
    
    /* Iteracoes do algoritmo */
    for(int count = 0; count < numero_iteracoes; count ++){
        /*Desenvolvimento do algoritmo*/
        
        /*Atribuir uma coordenada aleatoria ao x e ao y
        normalizada entre 0 e 1 sendo que a circunferencia 
        esta centrada na origem e tem raio igual a RAND_MAX*/
        x = ((double)rand()/(double)RAND_MAX); 
        y = ((double)rand()/(double)RAND_MAX);

        /* Inequacao do interior da circunferencia:
        x*x + y*y <= 1 */
        if(x*x + y*y <= 1){
            mpf_add_ui(pontos_circunferencia, pontos_circunferencia, 1);
        }
    }

    /* Calculo de Pi */
    mpf_div(pi, pontos_circunferencia, pontos_totais);
    mpf_mul_ui(pi, pi, 4);
    
    mpf_out_str (stdout, 10, 6, pi);
    printf("\n");

    /* Desalocar a memória dos big-numbers */
    mpf_clear (pontos_totais);
    mpf_clear (pontos_circunferencia);
    mpf_clear (pi);

}