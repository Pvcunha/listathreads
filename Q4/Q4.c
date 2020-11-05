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
    void* func(void*);
    int id;
    struct node* next;
} Node;

typedef struct buffer{
    Node* head  = NULL;
    Node* tail = NULL;
}Buffer;

int N = 4; // Número máximo de processos / threads
int tam_espera = 30;
int tam_resultado = 0;
int threads_exec = 0; // Número de threads executando 
int fun_agendados = 0; // Número de processos agendados até então.

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex
pthread_cond_t empty = PTHREAD_COND_INITIALIZER; // Variável de condição que sinaliza se a fila ta vazia
pthread_cond_t fill = PTHREAD_COND_INITIALIZER; // Variável de condição que sinaliza se a fila ta cheia


Buffer *bufferEspera = (Buffer*)malloc(sizeof(Buffer)); // iniciando o buffer 
Resultado* bufferResultado = NULL;

void* func(void* info){
    printf("Hello carai");
}

int agendarExecucao(void* struct var, void* func(void*)){
    //insere chamada na buffer
    Node* new = (Node*)malloc(sizeof(Node));
    new->func = func(var);
    new->next = NULL;
    Node* temp = bufferEspera->tail;
    bufferEspera->tail->next = new;
    bufferEspera->tail = new;
    int id_ret = fun_agendados;//id global, repassada para o user
    fun_agendados++;
    return id_ret ; //retorna o threadid
}

void* rotina_despachante()
{
    
}

int main(){
    int c;
    //Vetor de threads
    pthread_t threads[N];
    pthread_t despachante;
    int* despachante_id = (int*)malloc(sizeof(int));
    
    pthread_create(&despachante,NULL,rotina_despachante,&despachante_id);

    //Tretas do usuário
    scanf("%d",c);
    
    
    
    pthread_exit(NULL);
}
