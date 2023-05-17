#include <stdio.h>
#include <stdlib.h>
#include <string>

typedef struct list{
    struct list *next;
    int value, len;
}List;

typedef struct vertex{
    int grade;
    List *head,  *tail;
}Vertex;

Vertex list_insert_end(Vertex g, int value, int len){
 
    List *node = (List *)calloc(1, sizeof(List));
    node->value = value;
    node->len = len;
    node->next = NULL;

    g.tail->next = node;
    g.tail = node;

    return g;
}

List *list_delete(List *g, List **tail, int *deleted){
 
  List *removed = (List *)calloc(1, sizeof(List));
 
  removed = g->next;
  g->next = removed->next;
  (*deleted) = removed->value;  

  if(g->next == NULL){
    (*tail) = g;
  }
   
  return g;
}

void print_list(List *list, int vertex){
    List *aux = list;
    aux = aux->next;
    printf("lista do vertice %d: ", vertex);
    while(aux){
        printf(" %d,%d |", aux->value, aux->len);
         aux = aux->next;
    }
printf("\n");
}

int main(){
    int v = 0, e = 0, m = 0, n = 0, a = 0, b = 0, l = 0, orders = 0, cont = 0, id = 0, origin = 0, w = 0, z=0;
    char command[4];

    scanf("%d %d %d %d", &v, &e, &m, &n);
    Vertex *g = (Vertex *)calloc(v, sizeof(Vertex));
    int y[n];

    //inicializa vertices
    for(int i = 0; i < v; i++){
        g[i].grade = 0;
        g[i].head = (List *)calloc(1,sizeof(List));
        g[i].tail = g[i].head;
    }

    //define arestas e distancias
    for(int i = 0; i < e; i++){
        scanf("%d %d %d", &a, &b, &l);
        g[a] = list_insert_end(g[a], b, l);
        g[b] = list_insert_end(g[b], a, l);
    }

    for(int i = 0; i < n; i++){
        scanf("%d", &y[i]);
    }

    scanf(" %s", command);
    do{
        if(command[0] == 'N'){
            w++;
            scanf("%d %d", &id, &z);
            printf("+%d %d\n", id, w);
            id++;

        }else if(command[0] == 'C'){
            scanf("%d", &id);
            
            aux = q->head;
            del = list_find(q->head, id); 
            if(del){
                list_delete2(q->head, del->id);
                w--;
            }

            printf("-%d %d\n", del->id, w);
        }else if(command[0] == 'D'){

        }

        scanf(" %s", command);

    }while(command[0] != 'E');

    //printa listas de adjacencia
    for(int i = 0; i < v; i++){
        if(g[i].head->next){
            print_list(g[i].head, i);
        }
    }
    
    return 0;
}