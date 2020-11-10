#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TOTAL 100000
#define NUM_THREADS 5

//contador geral
int contador = 0;

//mutex para região crítica
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//flag para quando chegue a 10e6
int flag = 0;

//rotina para as threads
void *inc(void *thread_id){
    int *id = (int *)thread_id;

    // imprime quando uma thread começa a funcionar
    printf("Contando. Thread: %d\n", *id);

    // executa um somatório enquanto não chegar no total
    while(!flag) {

        // trava as outras threads para somente uma acessar a região crítica por vez

        pthread_mutex_lock(&mutex);

        //faz as verificações e em seguida incrementa o contador
        if(!flag && contador == TOTAL) {
            printf("Contador alcançou %d na thread %d", TOTAL, *id);
            flag = 1;
        }
        contador++;

        // desbloqueia para as outras threads
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int *thread_ids[NUM_THREADS]; 
    int n;
    int rc;
    int i;
    
    scanf("%d", &n);
    
    //cria threads
    for(i = 0; i < n; i++) {
        thread_ids[i] = (int *)malloc(sizeof(int));
        *thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, inc, (void *)thread_ids[i]);
        if(rc) {
            printf("Error %d\n", rc);
            exit(-1);
        }
    }

    //junta todas as threads
    for(i = 0; i < n; i++)
        pthread_join(threads[i], NULL);
    

    //pthread_exit(NULL);
    return 0;
}