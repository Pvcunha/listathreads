#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int N = 4; //Quantidade máxima de valores de threads.

typedef struct data
{
    int a;
    int b; 
}Data;

typedef struct node{
    void** func;
    Data k;
    struct node* next;
}Node;

typedef struct buffer{
    Node *head;
    Node *tail;
    int size;
}Buffer;

//buffer para as respostas
typedef struct bufferR{
    int ans;
    Node *head;
    Node *tail;
}BufferR;

//Buffer de espera
Buffer* InputBuffer =NULL;



//Funcao que será requisitada
void* multiplier( Data* data)
{   
    int a = data->a;
    int b = data->b; 
    int result = a*b;
    pthread_exit((void*) &result);
}

int agendarExecucao( void**routine, Data data )
{
    Node* new = (Node*)malloc(sizeof(Node));
    new->next = NULL;
    new->func = routine; //Passando a função para o nó 
    new->k = data;
    InputBuffer->tail->next = new;
    InputBuffer->tail = new;
}
/*
void* user_routine()
{
    //Coisas que o usuario faz
    Data input;
    Node 

    while(1)
    {
        Node->
        input->a = rand()%99;
        input->b = rand()%99;

    }

    pthreads_exit(NULL);
}
*/
/*void* dispatcher_routine()
{
    
    
}*/

int main()
{
    //inicializando o buffer 
    InputBuffer->head = (Node*)(malloc(sizeof(Node)));
    InputBuffer->tail = InputBuffer->head; 
    //Thread de usuario
/*
    pthread_t user;
    pthread_create(user,NULL,user_routine,NULL);
    
    //Thread despachante
    pthread_t dispatcher;
    pthread_create(dispatcher, NULL,dispatcher_routine,NULL);

    //Espera a thread usuário terminar
    pthread_join(user,NULL);
*/
    pthread_exit(NULL);
}