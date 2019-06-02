/* Esse gerador de numeros aleatorios gera numeros que seguem uma distribuicao normal com media 0 e desvio padrao 1: N(0,1). */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

struct BoxMullerState
{
        double x1, x2, w, y1, y2;
        int useLast;
        struct drand48_data random;
};

void initBoxMullerState(struct BoxMullerState* state)
{
        state->random.__init = 0;
        state->useLast = 0;
        
        struct timeval now;
	gettimeofday(&now, NULL);
	state->random.__x[0] = now.tv_usec;
}

double boxMullerRandom(struct BoxMullerState* state)
{
        double randomNumber;

        if (state->useLast)
        {
                state->y1 = state->y2;
                state->useLast = 0;
        }
        else
        {
                do
                {
                        drand48_r(&state->random, &state->x1);
                        state->x1 = 2.0 * state->x1 - 1.0;
                        drand48_r(&state->random, &state->x2);
                        state->x2 = 2.0 * state->x2 - 1.0;
                        state->w = state->x1 * state->x1 + state->x2 * state->x2;
                }
                while (state->w >= 1.0);

                state->w = sqrt((-2.0 * log(state->w)) / state->w);
                state->y1 = state->x1 * state->w;
                state->y2 = state->x2 * state->w;
                state->useLast = 1;
        }

        return state->y1;
}

/* Exemplo de uso. */
int main()
{
	/* OBS: cada thread deve possuir uma variavel do tipo BoxMullerState. */
	struct BoxMullerState state;
	
	/* O init deve ser chamado! */
	initBoxMullerState(&state);
	
	int i;
	for (i = 0; i < 10; ++i)
		printf("%lf\n", boxMullerRandom(&state));
	
	return 0;
}

