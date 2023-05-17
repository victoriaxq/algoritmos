#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex{
    int value;
    bool visited;
    struct queue *next;
    int grade;
}Vertex;

typedef struct queue{
    struct queue *next;
    int value;
}Queue;


int main(){

    int V = 0, E = 0, V0 = 0, V1 = 0, X;
    char command[10];

    scanf("%d %d", &V, &E);

    Vertex *vertex = (Vertex *)calloc(V, sizeof(Vertex));
    Vertex *aux0 = (Vertex *)calloc(1, sizeof(Vertex));
    Vertex *aux1 = (Vertex *)calloc(1, sizeof(Vertex));
    Vertex *fila = (Vertex *)calloc(1, sizeof(Vertex));
    Vertex *fila2 = (Vertex *)calloc(1, sizeof(Vertex)); 

    //inicializando vertices do grafo
    for(int i = 0; i < V; i++){
        vertex[i].next = NULL;
        vertex[i].value = i;
        vertex[i].visited = 0;
        vertex[i].grade = 0;
    }
    /* for(int i = 0; i < V; i++){
        cout << "vertex " << i << " value = " << vertex[i].value << "\n";
        cout << "vertex " << i << " visited = " << vertex[i].visited << "\n";
        cout << "vertex " << i << " grade = " << vertex[i].grade << "\n";
        cout << "\n";
    } */

    for(int i = 0; i < E; i++){
        scanf("%d %d", &V0, &V1);

        (*aux0) = vertex[V0]; 
        (*aux1) = vertex[V1];

        aux0->next = NULL;
        aux1->next = NULL;
        //att grade
        vertex[V0].grade++;
        vertex[V1].grade++;

       printf("passou aqui 1 \n");

        if(vertex[V0].next == NULL){
            vertex[V0].next = aux1;
            printf("passou aqui 2 \n");
        }else{
            fila[V0] = vertex[V0];
            printf("passou aqui 3 \n");

            while(fila[V0].next != NULL){
                fila[V0] = *fila[V0].next;
            }
            fila[V0].next = aux1;
        }
            printf("passou aqui 4 \n");
        printf("%d\n", vertex[V0].next->value);

        if(vertex[V1].next == NULL){
            vertex[V1].next = aux0;
            printf("passou aqui 5 \n");
        }else{
            fila2[V1] = vertex[V1];
            while(fila2[V1].next != NULL){
                fila2[V1] = *fila2[V1].next;
            }
            fila2->next = aux0;
            printf("passou aqui 6 \n");
        }

        printf("%d\n", vertex[V1].next->value);
    }

    /* for(int i = 0; i < V; i++){
        if(vertex[i].next == NULL){
            cout << "não faz aresta com ninguém \n";
        }else{
            *fila = vertex[i];
            while(fila->next != NULL){
                cout << "Adjacente a " << fila->next->value << "\n";
                fila = fila->next;
            }

        }
    } */

    //cin >> X;

    return 0;
}