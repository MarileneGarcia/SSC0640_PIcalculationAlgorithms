/* Marilene Garcia - 10276974 */

/*Aplicação da Simulação de Monte Carlo
        Modelo de Black Scholes*/

/* Forma de compilar o codigo */
//gcc nome_arquivo.c -o nome_executavel -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "black-scholes_biblioteca.c"

int main(){
	blackScholes();
	return 0;
}

void blackScholes(){
    
    /*Definicoes das funcoes que geram numeros aleatorios */
    unsigned int x = time(NULL);

    /* OBS: cada thread deve possuir uma variavel do tipo BoxMullerState. */
	struct BoxMullerState state;
    /* O init deve ser chamado! */
	initBoxMullerState(&state);

    /* Variaveis de Entrada */
    int M;
    double S, E, r, sigma, T;
    /* Obtendo os valores do arquivo de entrada */
    scanf("%lf %lf %lf %lf %lf %d ", &S, &E, &r, &sigma, &T, &M);

    /*Variaveis auxiliares*/
    int i;
    double aux1, aux2, aux3, aux4, aux5, aux6, aux7;
    double t, trials[M], max;
    double aux_mean, mean, aux_stddev, stddev, confmin, confmax, confwidth;

    /* Algoritmo de Black Scholes com Monte Carlo */
   for(i = 0; i<M; i++){
       aux1 = (r - (0.5 * (sigma * sigma))) * T;
       aux2 = sigma*sqrt(T);
       aux3 = boxMullerRandom(&state); //numero aleatorio
       aux4= aux2*aux3;
       aux5 = aux1 + aux4;

       t = S*(exp(aux5));
       
       if(t - E < 0) max = 0;
       else max = t -E;

        trials[i] = (exp((-r)*T))*max;
    }

    /* Calculo da media do vetor (mean) */
    for(i=0; i<M; i++) aux_mean += trials[i];
    mean = aux_mean / (double)M;

    /* Calculo do desvio-padrao (stddev) */
    for(i=0; i<M; i++) aux_stddev += ((trials[i]-mean)*(trials[i]-mean));
    stddev = sqrt(aux_stddev/(double)M);

    /*Calculo do intervalo de confiança */
    confwidth = 1.96 * (stddev/sqrt(M));
    confmin = mean - confwidth;
    confmax = mean + confwidth;

    /*Imprimindo os resultados*/
    printf("S        %0.lf\n",S);
	printf("E        %0.lf\n",E);
	printf("r        %0.lf\n",r);
	printf("sigma    %0.lf\n",sigma);
	printf("T        %0.lf\n",T);
	printf("M        %d\n",M);
    printf("Intervalo de Confiança: (%lf,%lf)\n", confmin,confmax);
}



