#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list{
    struct list *next;
    int value;
}List; 

typedef struct vertex{
    int value;
    bool visited;
    int grade;
    List *sentinel;
    List *tail;
}Vertex;

Vertex list_insert_end(Vertex g, int value){
  
    List *node = (List *)calloc(1, sizeof(List));
    node->value = value;
    node->next = NULL;

    g.tail->next = node;
    g.tail = node;

    return g;
} 

List *list_delete(Vertex g, List **tail, int *deleted){
  
  List *removed = (List *)calloc(1, sizeof(List));
  
  removed = g.sentinel->next;
  g.sentinel->next = removed->next;
  (*deleted) = removed->value;  

  if(g.sentinel->next == NULL){
    (*tail) = g.sentinel;
  }
    
  return g.sentinel;
}

int MenorDistancia (Vertex *lista, int V, int A, int B) {
    Vertex listas;
    List *grafo;
    int dist[V];
    int xau;
    int i;
    int vertices;

    for (i = 0; i < V; i++) {
        dist[i] = - 1; //inicializando a distancia 
    }

    listas.sentinel = (List*)malloc(sizeof(List));
    listas.sentinel->next = NULL;
    listas.tail = listas.sentinel;
    listas = list_insert_end(listas, A);
    listas.tail = listas.tail->next;
    //dist[lista[A].T] = 0;

    while (listas.sentinel != listas.tail) {
        listas.sentinel = list_delete(listas, &listas.tail, &xau);
        grafo = lista[xau].sentinel->next;

        while (grafo != NULL) {
            vertices = grafo->value;
            if (dist[vertices] == - 1) {
                dist[vertices] = dist[xau] + 1;
                listas = list_insert_end(listas, vertices);
                listas.tail = listas.tail->next;
            }
            if (vertices == B) {
                return dist[vertices];
            }
            grafo = grafo->next;
        }
    }
    return dist[B];
}

/* int BTS(Vertex *g, int qt, int a, int b){
  int pipipi; 
  List *edge = (List *)calloc(1, sizeof(List));
  int u;
  int d[qt] = {0};
  for(int i = 0; i < qt; i++){
    d[i]  = -1;
  }
  
  d[a] = 0;
  Vertex empty;
  empty.sentinel = (List *)calloc(1, sizeof(List));
  empty.tail = empty.sentinel;
  empty.sentinel->next = NULL;
  
  empty = list_insert_end(empty, a);

  while(empty.sentinel != empty.tail){
    empty = list_delete(empty, &empty.tail, &u);
    edge = g[u].sentinel->next;
    
    while(edge){
      pipipi = edge->value;
      if(d[pipipi] == -1){
        d[pipipi] = d[u] + 1;
        empty = list_insert_end(empty, u);
      }
      if(u == b){
        return d[u];
      }
      edge = edge->next;
    }
  }  
  return d[b];
} */

void print_list(List *list, int vertex){
    List *aux = list;
    aux = aux->next;
    printf("lista do vertice %d: ", vertex);
    while(aux){
        printf(" %d |", aux->value);
         aux = aux->next;
    }
printf("\n");
}

int main(){

    int v = 0, e = 0, a = 0, b = 0, x = 0, v1, v2, d = 0;
    char command[4];
    
    scanf("%d %d", &v, &e);
    int u[v];
    Vertex *g = (Vertex *)calloc(v, sizeof(Vertex));

    for(int i = 0; i < v; i++){
        u[i] = i;
        g[i].value = i;
        g[i].grade = 0;
        g[i].visited = 0;
        g[i].sentinel = (List *)calloc(1, sizeof(List));
        g[i].tail = g[i].sentinel;
        g[i].sentinel->next = NULL;
    }

    for(int i = 0; i < e; i++){
        scanf("%d %d", &a, &b);
        g[a] = list_insert_end(g[a], b);
        g[b] = list_insert_end(g[b], a);

        print_list(g[a].sentinel, a);
        printf("\n");
        print_list(g[b].sentinel, b); 

       /* g[b].sentinel = list_delete(g[b], &g[b].tail, &b);
        print_list(g[b].sentinel, b);  */
    }

    scanf("%d", &x);
    for(int i = 0; i < x; i++){
        scanf(" %s", command);

        if(command[0] == 'D'){
            scanf("%d %d", &v1, &v2);
            //verifica se tem o mesmo representante
            d = MenorDistancia(g, v, v1, v2);
            printf("%d\n", d); 

        }else if(command[0] == 'C'){

        }
    }

    return 0;
}