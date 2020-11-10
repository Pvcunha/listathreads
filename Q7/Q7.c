#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

#define N 4

int rows,cols;
int maxvalue;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_t *threads;

typedef struct pixel{
    int red,blue,green;
}pixel;

typedef struct cord{
    int x;
    int y;
}cord;

// matriz que vai representar a imagem antes da conversão
pixel **image;

// matriz que representa a imagem após a conversão
pixel **image2;

//buffer de pixels sobrando
cord *buffer = NULL;

// index do buffer de pixels para threads usarem
int buffer_index = 0;

//tamanho do buffer
int buffer_size;
int indexi = 0;

void *convert(void *threadid){
    
    int id = *((int *)threadid);
    printf("Thread %d iniciou\n", id);
    while(indexi < buffer_size){
        //puts("entrou no loop\n");
        pthread_mutex_lock(&mutex);

        //Pega as coordenadas do pixel
        int cordx = buffer[indexi].x;
        int cordy = buffer[indexi].y;
        indexi++;
        
        printf("thread %d pegou coord=(%d, %d)\n", id, cordx , cordy);
        pthread_mutex_unlock(&mutex);
        
        // faz a conversão e armazena na imagem pos conversão
        int C = (int)(image[cordx][cordy].red*0.3 + image[cordx][cordy].green*0.59 + image[cordx][cordy].blue*0.11);
        image2[cordx][cordy].red = C;
        image2[cordx][cordy].green = C;
        image2[cordx][cordy].blue = C;
    }


    pthread_exit(NULL);

}

cord build_cord(int i, int j) {
    cord new;
    new.x = i;
    new.y = j;
    return new;
}

int main(){

    char format[200];
    
    FILE *file = fopen("a.ppm", "r");
    if(!file) exit(-1);
    
    fscanf(file, "%s", format);
    fscanf(file, "%d %d", &cols, &rows);
    fscanf(file, "%d", &maxvalue);
    
    // Devidas alocações

    buffer_size = rows*cols;
    buffer = (cord *)malloc(buffer_size*sizeof(cord));
    if(!buffer) {
        exit(-1);
    }

    image = (pixel **)malloc(rows*sizeof(pixel *));
    if(!image)
        exit(-1);

    for(int i = 0; i < rows; i++) {
        image[i] = (pixel *)malloc(cols*sizeof(pixel));
        if(!image[i])
            exit(-1);
    }    
    

    image2 = (pixel **)malloc(rows*sizeof(pixel *));
    if(!image2)
        exit(-1);

    for(int i = 0; i < rows; i++) {
        image2[i] = (pixel *)malloc(cols*sizeof(pixel));
        if(!image2[i])
            exit(-1);
    }

    threads = (pthread_t *)malloc(N*sizeof(pthread_t));

    printf("Tudo alocado\n");
    int k = 0;
    for(int i = 0;i<rows;i++){
        for(int j=0;j<cols;j++){
            fscanf(file, "%d %d %d",&(image[i][j].red),&(image[i][j].green),&(image[i][j].blue));
            buffer[k] = build_cord(i, j);
            k++;
        }
    }

    printf("Mat lida\n");
    int *threads_id[N];
    int rc;
    for(int i = 0; i < N; i++) {
        threads_id[i] = (int *)malloc(sizeof(int));
        *(threads_id[i]) = i;
        rc = pthread_create(&threads[i], NULL, convert, (void *)threads_id[i]);

        if(rc) {
            printf("Deu problema na criacao da thread %d\n", rc);
            exit(-1);
        }

    }

    //abre o arquivo de saída e imprime a imagem convertida em out.ppm
    FILE *file_gray = fopen("out.ppm", "w");
    
    for(int i = 0;i<rows;i++){
        for(int j=0;j<cols;j++){
            fprintf(file_gray, "%d %d %d\n", image2[i][j].red, image2[i][j].green, image2[i][j].blue);
            buffer[k] = build_cord(i, j);
        }
    }

    fclose(file_gray);
    

    for(int i = 0; i < N; i++) 
        pthread_join(threads[i], NULL);
     
    for(int i = 0; i < N; i++)
        free(threads_id[i]);
    
    pthread_exit(NULL);

    free(threads);
    fclose(file);

    return 0;
}
