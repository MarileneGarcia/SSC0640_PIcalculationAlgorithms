/* Funcoes usadas para o algoritmo Black Scholes*/
void blackScholes();

/* Usando os codigos de gerar numeros aleatorios fornecido pelo professor
Para gerar um numero aleatorio e possivel tanto a funcao (geradorNumerosAleatorios)
quanto a funcao (boxMullerRandom) */
const unsigned int A = 1664525, C = 1013904223;
unsigned int geradorNumerosAleatorios(unsigned int x);

struct BoxMullerState
{
        double x1, x2, w, y1, y2;
        int useLast;
        struct drand48_data random;
};

/* Funcoes para geracao de numeros aleatorios */

/* Gerador congruencial linear */
unsigned int geradorNumerosAleatorios(unsigned int x){
    return x*A+C;
}

/* Gerador de numeros aleatorios gera numeros que seguem uma distribuicao normal com media 0 e desvio padrao 1: N(0,1).*/

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