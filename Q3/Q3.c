#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#define n 5
char s1[500],s2[500];
pthread_t *threads;
pthread_mutex_t gen_mutex = PTHREAD_MUTEX_INITIALIZER;
int tota_subs = 0,ind=0,ans =0;

void *compare1(void *threadid) {
    int id = *((int *)threadid);
    int tam1 = strlen(s1);
    int tam2 = strlen(s2);

    while(ind<tam1-tam2+1){
        pthread_mutex_lock(&gen_mutex);
        char aux[500];
        //pega substring de tamanho s2 em s1;
        for(int i = 0;i<tam2+1 && i<tam1;i++){
            aux[i]=s1[ind+i];
        }
        aux[tam2]='\0';
        ind++;
        //se as strings forem iguais, adiciona 1 a resposta
        if(strcmp(aux,s2)==0)ans++;
        //printf("THREAD_ID=%d, ans atual %d\n", id, ans);

        pthread_mutex_unlock(&gen_mutex);
    
    }


}


int main() {
    
    //recebe as strings s1 e s2;

    scanf("%s %s",s1,s2);
    //aloca a quantidade de threads requerida na memória
    threads = (pthread_t *)malloc(n*sizeof(pthread_t));
    //guardas os ids das threads criadas
    int *threads_id[n];
    //variável para armazenamento do retorno da thread_create
    int rc;
    //cria todas as threads e seus id's
    for(int i = 0; i < n; i++) {
        threads_id[i] = (int *)malloc(sizeof(int));
        *(threads_id[i]) = i;
        rc = pthread_create(&threads[i], NULL, compare1, (void *)threads_id[i]);

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