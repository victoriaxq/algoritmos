#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct connection{
    unsigned int tscmp; //timescamp
    unsigned int client; //IP
}Connection;

typedef struct node{
    Connection connection;
    struct node *next;
}Node;

typedef struct hash_table{
    Node *head;
    int size;
}HashTable;

void insert_Hash(Connection c, HashTable *h){

    Node *node = (Node *)malloc(sizeof(Node));
    if(node == NULL){
        printf("se m4t4 2");
        exit(0);
    }

    node->connection = c;
    h->head = node;
    h->size = 

}

void printHash(Node *inicio){
    Node *aux = inicio;
    while(aux != NULL){
        printf("%d %d\n", &aux->connection.tscmp,&aux->connection.client);
        aux = aux->next;
    }
}


Node *search_Node(int ip, Node *inicio){
    
    Node *aux = inicio;
    while(aux != NULL){

        if(aux->connection.tscmp == ip){
            return aux;
        }else{
            aux = aux->next;
        }
    }
}

int main(){

    int table_size = 0;
    float l, numTscmp, lMax;
    l = numTscmp/(float)table_size; //fator de carga

    scanf("%d %f", &table_size, &lMax);

    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
        if(h == NULL){
            printf("se m4t4");
            exit(-1);
        }
        h->head = NULL;
        h->size = table_size;

    //inicializando struct de chaves
    for(int i = 0; i < table_size; i++){

    }

    return 0;
}