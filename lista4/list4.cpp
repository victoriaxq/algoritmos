#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct list{
    struct list *next;
    int value;
}List;

typedef struct vertex{
    int value;
    int visited;
    int eq;
    int grade;
    List *sentinel;
    List *tail;
}Vertex;

void print_list(List *list, int vertex, int rep){
    List *aux = list;
    aux = aux->next;
    printf("lista do vertice %d (REP %d): ", vertex, rep);
    while(aux){
        printf(" %d |", aux->value);
         aux = aux->next;
    }
printf("\n");
}

int count_grade(List *list){
    List *aux = list->next;
    int grade = 0;
    while(aux){
        grade++;
        aux = aux->next;
    }

    return grade;
}

void delete2(List *queue, int value){
    List *aux = queue->next;
    List *remove = NULL;
    List *aux2 = NULL;
    List *new_last = NULL;
    //caso seja o primeiro da lista fora o sentinela
    if(queue->next){
        if(queue->next->value == value){
            remove = queue->next;
            queue->next = remove->next;
            //return queue->sentinel->next;
        }else{
            while(aux->next && aux->next->value != value){
                aux = aux->next;
            }
            if(aux->next){
                remove = aux->next;
                new_last = remove->next;
                free(remove);
            }
        }
        
    }
}

List *insert2(List *tail, int value){
    List *node = (List *)calloc(1,sizeof(List));
    node->value = value;
    node->next = tail->next;
    tail->next = node;

    return tail;
}

Vertex list_insert_end(Vertex g, int value){
 
    List *node = (List *)calloc(1, sizeof(List));
    node->value = value;
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

List *list_find(List *sentinel, int value){
    List *cur = sentinel;
    while(cur->next && cur->value != value){
        cur = cur->next;
    }
    if(cur->value == value){
        return cur;
    }else{
        return NULL;
    }
}

List *last(List *queue){
    List *tail = queue;
    while(tail->next){
        tail = tail->next;
    }
    return tail;
}

int delete_dup(List *g){
    List *aux10 = g->next;
    List *aux;
    int vet[100];
    int t = 0, dup = -1;

    for(aux = aux10 ; aux!=NULL; aux=aux->next){
        vet[t] = aux->value;
        t++;
    }

    for(int i = 0 ; i < t; i++){
        for(int j = i+1; j < t; j++){
            if(vet[i] == vet[j]){
                dup = vet[i];
                return dup;
            }
        }
        
    }
    return dup;
    
}

void empty(List *sentinel){
    int del;
    List *tail = last(sentinel);
    while(sentinel->next){
        sentinel = list_delete(sentinel, &tail, &del);
        tail = last(sentinel);
    }
} 

int BTS(Vertex *list, int qt, int a, int b) {
    Vertex g;
    List *edge = (List *)calloc(1, sizeof(List));
    int d[qt], vertex, u, v;


    for (int i = 0; i < qt; i++){
        d[i] = - 1;
    }

    d[list[a].eq] = 0;
    g.sentinel = (List*)malloc(sizeof(List));
    g.sentinel->next = NULL;
    g.tail = g.sentinel;
    g = list_insert_end(g, list[a].eq);

    while(g.sentinel != g.tail){
      u = g.sentinel->next->value;
        g.sentinel = list_delete(g.sentinel, &g.tail, &u);
        edge = list[u].sentinel->next;

        while(edge){
            vertex = edge->value;
         
            if(d[vertex] == - 1){
                d[vertex] = d[u] + 1;
                g = list_insert_end(g, vertex);
            }
            if(vertex == list[b].eq){
                return d[vertex];
            }
            edge = edge->next;
        }
    }
    return d[list[b].eq];
}

Vertex *contract2(Vertex *g, int a, int b, int qt, int *qtAux){

    int deleted = -1, dup = -1;
    List *adj_a, *adj_b, *tail_a, *suicide, *aux, *aux2, *aux3, *tail_aux;

    if(g[g[a].eq].eq != g[b].eq){

        adj_a = g[g[a].eq].sentinel;
        adj_b = g[g[b].eq].sentinel;
        (*qtAux)--;
        aux = adj_a;
        aux2 = adj_b;
        
        //adcionando tudo de B em A fazendo tail->next = adj_b->next 
        tail_a = last(adj_a);
        tail_a->next = adj_b->next;

        //tirar ele mesmo
        suicide = list_find(adj_a, g[a].eq);
        if(suicide){
            delete2(adj_a, suicide->value);
        }

        //tirando repetidos
        dup = delete_dup(adj_a);
        if(dup != -1){
            delete2(adj_a, dup);
        } 

        suicide = list_find(adj_a, g[b].eq);
        if(suicide){
            delete2(adj_a,g[b].eq);
        }

        //fazendo os adjacentes de b apontarem pro representante 
        //removendo o A antes pra nao dar problema
        delete2(adj_b, g[a].eq);

        while(adj_b->next){
            suicide = list_find(g[g[adj_b->next->value].eq].sentinel, g[a].eq);
            if(suicide){

            }else{
                g[g[adj_b->next->value].eq] = list_insert_end(g[g[adj_b->next->value].eq], g[a].eq);
            }
            delete2(g[g[adj_b->next->value].eq].sentinel, g[b].eq);
            adj_b = adj_b->next;
        }

        //esvaziando adj_b
        empty(g[g[b].eq].sentinel);
        
        g[g[a].eq].sentinel = adj_a;
        g[g[a].eq].grade = count_grade(g[g[a].eq].sentinel);

        for(int i = 0; i < qt; i++){
            if(g[g[i].eq].eq == g[b].eq){
                g[i].eq = g[a].eq;
                
            }
           //print_list(g[i].sentinel, i, g[i].eq);
        }
        g[b].eq = g[a].eq;
    }

    return g;
}

int main(){

    int v = 0, e = 0, a = 0, b = 0, x = 0, v1, v2, aux = 0, d = 0, menor = 0, maior = 0, vaux = 0;
    char command[4];
    List *deleted = (List *)calloc(1, sizeof(List));

    scanf("%d %d", &v, &e);
    vaux = v;
    Vertex *g = (Vertex *)calloc(v, sizeof(Vertex));

    for(int i = 0; i < v; i++){
        g[i].eq = i;
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

        g[a].grade++;
        g[b].grade++;
    
    }

   /*  for(int i = 0; i < v; i++){
            print_list(g[i].sentinel, i, g[i].eq);
        } */

    scanf("%d", &x);
    for(int i = 0; i < x; i++){
        scanf(" %s", command);

        if(command[0] == 'D'){
            scanf("%d %d", &v1, &v2);
            //verifica se tem o mesmo representante
            d = BTS(g, v, g[v1].eq, g[v2].eq);
            printf("%d\n", d);

        }else if(command[0] == 'C'){
            scanf("%d %d", &a, &b);
           
            g = contract2(g, g[a].eq, g[b].eq, v, &vaux);
            printf("%d %d\n", vaux, g[g[a].eq].grade);
        }
    }
    return 0;
}
 /* 
6 7
2 4
4 5
1 4
0 2
1 2
0 5
3 5
17
DIS 5 3
DIS 4 5
DIS 4 3
DIS 1 5
DIS 2 0
DIS 4 3
DIS 0 2
DIS 3 1
DIS 4 3
CTR 2 4
CTR 1 4
DIS 4 3
DIS 2 3
DIS 0 4
DIS 2 3
DIS 2 3
DIS 5 0
 */
