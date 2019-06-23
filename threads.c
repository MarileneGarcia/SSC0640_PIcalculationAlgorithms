#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

void * soma(void *arg){
    int a = *(int *)(arg);
    printf("%d \n",a);

    pthread_exit((void *) (&a));
}

int main(){
    pthread_t thread_id;
    void *thread_res;
    int restatus;
    int a = 8;
    restatus = pthread_create (&thread_id, NULL, soma, (void*)(&a));
    restatus = pthread_join(thread_id, &thread_res);
    printf("%d \n", *(int *)thread_res);
  //  printf("%d \n",restatus);

    return 0;

}
 
// gcc main.c -o main -lpthread