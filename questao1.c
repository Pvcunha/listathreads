#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TOTAL 100000
#define NUM_THREADS 5


int contador = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int flag = 0;

void *inc(void *thread_id){
    int *id = (int *)thread_id;
    printf("Contando. Thread: %d\n", *id);
    while(!flag) {
        pthread_mutex_lock(&mutex);
        if(!flag && contador == TOTAL) {
            printf("Contador alcançou %d na thread %d", TOTAL, *id);
            flag = 1;
        }
        contador++;
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
    
    for(i = 0; i < n; i++) {
        thread_ids[i] = (int *)malloc(sizeof(int));
        *thread_ids[i] = i;
        rc = pthread_create(&threads[i], NULL, inc, (void *)thread_ids[i]);
        if(rc) {
            printf("Error %d\n", rc);
            exit(-1);
        }
    }

    for(i = 0; i < n; i++)
        pthread_join(threads[i], NULL);
    

    //pthread_exit(NULL);
    return 0;
}