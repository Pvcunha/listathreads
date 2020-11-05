#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



typedef struct dados
{
    pthread_t thread;
    const pthread_attr_t atributo;
    void * (*rotina)(void *);
    void* threadid;

}dados;

typedef struct resultado
{
    int id; 
    void* result;
}Resultado;

typedef struct node
{
    dados val;
    struct node* next;
} Node;



int N = 4; // Número máximo de processos / threads
int tam_espera = 30;
int tam_resultado = 0;
int threads_exec = 0; // Número de threads executando 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; // Variável de condição que sinaliza se a fila ta vazia
pthread_cond_t fill = PTHREAD_COND_INITIALIZER; // Variável de condição que sinaliza se a fila ta cheia


Node *bufferEspera = NULL; //  
Resultado* bufferResultado = NULL;

void func(void* info){
    
}

int agendarExecução(){
    
}

int main(){
    
    //Vetor de threads
    pthread_t threads[N];

    //Tretas do usuário
    dados input;
    input.thread = 
    
    
    pthread_exit(NULL);
}
