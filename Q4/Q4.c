#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#define _XOPEN_SOURCE_ 600
#define n 4
#define lin 2
#define col 2
int matrizA[lin][col]={{2,1,},
                        {5,7}};
int matiX[col]={1,1};
            

int buffer;
pthread_t *threads;
pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
int tota_subs = 0,ind=0,ans =0;

void *solvejaco(void *threadid) {
    int id = *((int *)threadid);
    



}


int main() {
    
    
    //aloca a quantidade de threads requerida na memória
    threads = (pthread_t *)malloc(n*sizeof(pthread_t));
    //guardas os ids das threads criadas
    int *threads_id[n];
    //variável para armazenamento do retorno da thread_create
    int rc;
    //cria todas as threads e seus id's
    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier,NULL,3);
    for(int i = 0; i < n; i++) {
        threads_id[i] = (int *)malloc(sizeof(int));
        *(threads_id[i]) = i;
        rc = pthread_create(&threads[i], NULL, solvejaco, (void *)threads_id[i]);

        if(rc) {
            printf("Deu problema na criacao da thread %d\n", rc);
            exit(-1);
        }

    }
    for(int i = 0; i < n; i++) 
        pthread_join(threads[i], NULL);

    printf("Resposta : %d substrings\n",ans);
    pthread_mutex_destroy(&gen_mutex);

    for(int i =0; i < n; i++) 
        free(threads_id[i]);    
    
    pthread_exit(NULL);

    free(threads);

    return 0;
}

