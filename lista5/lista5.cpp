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

typedef struct order{
    struct order *next;
    int id;
    int dest;
}Order;

typedef struct queue{
    Order *head;
    Order *tail;
}Queue;

typedef struct heap{
    int dest, len;
}Heap;

typedef struct table{
    int *d, rest;
}Table;

Order *last(Order *queue){
    Order *tail = queue;
    while(tail->next){
        tail = tail->next;
    }
    return tail;
}

void print_list(Order *list){
    Order *aux = list;
    aux = aux->next;
    printf("fila de pedidos: ");
    while(aux){
        printf(" %d |", aux->id);
         aux = aux->next;
    }
printf("\n");
}

Vertex list_insert_end(Vertex g, int value, int len){
 
    List *node = (List *)calloc(1, sizeof(List));
    node->value = value;
    node->len = len;
    node->next = NULL;

    g.tail->next = node;
    g.tail = node;

    return g;
}

Queue *enqueque(Queue *q, Order *tail){
    q->tail->next = tail;
    q->tail  = tail;

    return q;
}

Order *new_order(int id, int locale){
    Order *order = (Order *)calloc(1,sizeof(Order));
    order->id = id;
    order->dest = locale;
    order->next = NULL;

    return order;
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

void list_delete2(Order *queue, int value){
    Order *aux = queue->next;
    Order *remove = NULL;
    Order *aux2 = NULL;
    Order *new_last = NULL;
    //caso seja o primeiro da lista fora o sentinela
    if(queue->next){
        if(queue->next->id == value){
            remove = queue->next;
            queue->next = remove->next;
            //return queue->sentinel->next;
        }else{
            while(aux->next && aux->next->id != value){
                aux = aux->next;
            }
            if(aux->next){
                remove = aux->next;
                new_last = aux;
                aux->next = remove->next;
            }
        }
        
        /* if(remove == queue->tail){
            queue->tail = aux;
        }else if(aux == NULL){
            queue->tail = NULL;
        } */
    }
}

Order *list_find(Order *sentinel, int value){
    Order *cur = sentinel;
    while(cur->next && cur->id != value){
        cur = cur->next;
    }
    if(cur->id == value){
        return cur;
    }else{
        return NULL;
    }
}

Queue *create_queue(){
    Queue *queue = (Queue *)calloc(1,sizeof(Queue));
    queue->head = (Order *)calloc(1,sizeof(Order));
    queue->tail = queue->head;

    return queue;
}

Heap *create_heap(){
    Heap *heap = (Heap *)calloc(1,sizeof(Heap));
    heap->dest = -1;
    heap->len = -1;
    return heap;
}

int *alloc(int v){
 int *i = (int *)calloc(v, sizeof(int));

    if(i){
        return i;
    }
}

Heap *realloc_heap(int *size){
    Heap *h = (Heap *)realloc(h, (*size) * (sizeof(Heap)));
    return h;
}

Heap *bubble_up(Heap *h, int *size){

    Heap aux;
    int t = (*size);

    while(t > 0 && h[t].dest <= h[(t-1)/2].dest){
        aux = h[t];
        h[t] = h[(t-1)/2];
        h[(t-1)/2] = aux;
        t = (t-1)/2;
    }

    return h;
}

Heap *heap_insert(Heap *h, int *size, int *sizeMax, int dest, int len){

    if(*size == *sizeMax){
        h = realloc_heap(size);
        *(size) *= 2;
    }

    h[*size].len = len;
    h[*size].dest = dest;

    h = bubble_up(h, size);
    *size++;

    return h;
}

Heap *bubble_down(Heap *h, int size, int v){

    Heap aux; 
    int l, r, m;
    m = size;
    l = 2*size + 1;
    r = 2*size + 2;

    if(l < size && h[l].len <= h[m].len){
        m = l;
    }
    if(r < size && h[r].len <= h[m].len){
        m = r;
    }
    if(m != v){
        aux = h[m];
        h[m] = h[v];
        h[v] = aux;
        h = bubble_down(h, m, size);
        return h;
    }
}

int heap_extract(Heap *h, int *size, int *len){

    Heap aux, r = h[0];

    if(*size > 0) {
        aux = h[0];
        h[0] = h[(*size) - 1];
        h[*size - 1] = aux;
        (*size)--;
        h = bubble_down(h, 0, *size);
    }

    *len = r.len;
    return r.dest;
}

int *diskraca(Vertex *g, int qt, int y){
    Heap *h = create_heap();
    int *d = alloc(qt);
    bool flag = false;
    int size = 0, size_max = 1, e = 0, u = 0, value = 0, len = 0;
    List *g_aux;

    printf("oi 1\n");

    for(int i = 0; i < qt; i++){
        d[i] = -1;
    }
    
    printf("oi 2\n");

    d[y] = 0;
    h = heap_insert(h, &size, &size_max, y, 0);

    printf("oi 3\n");
    for(int i = 0; i < qt; i++){
        printf("oi 4\n");
        u = heap_extract(h, &size, &e);
        printf("oi 5\n");
        g_aux = g[u].head->next;
        printf("oi 6\n");
        while(g_aux){
            printf("oi 7\n");
            value = g_aux->value;
            printf("oi 8\n");
            len = g_aux->len;
            printf("oi 9\n");
            if((e + len < d[value]) || (d[value] == -1)){
                printf("oi 10\n");
                d[value] = e+len;
                printf("oi 11\n");
                flag = false;
                printf("oi 11\n");
                for(int j = 0; j < size; j++){
                    printf("oi 12\n");
                    if(h[j].dest == value){
                        printf("oi 13\n");
                        h[j].len = d[value];
                        printf("oi 14\n");
                        h = bubble_up(h, &j);
                        printf("oi 15\n");
                        flag = true;
                        printf("oi 16\n");
                    }
                }
                printf("oi 17\n");
                if(flag == false){
                    printf("oi 18\n");
                    h = heap_insert(h, &size, &size_max, value, d[value]);
                    printf("oi 19\n");
                }  
            }
            printf("oi 20\n");
            g_aux = g_aux->next;
            printf("oi 21\n");
        }
    }
    printf("oi 22\n");
    return d;
}

Table *create_table(int qt){
    Table *t = (Table *)calloc(qt, sizeof(Table));
    return t;
}

int main(){
    int v = 0, e = 0, m = 0, n = 0, a = 0, b = 0, l = 0, orders = 0, cont = 0, id = 0, origin = 0, w = 0, z = 0, flag = 0, dist = 0, rest_aux = 0, ent = 0;
    bool flag2 = false;
    char command[4];
    Order *aux = NULL;
    Order *del = (Order *)calloc(1, sizeof(Order));
    Queue *q = create_queue();
    
    int *delivered = alloc(1);

    scanf("%d %d %d %d", &v, &e, &m, &n);
    Vertex *g = (Vertex *)calloc(v, sizeof(Vertex));
    int y[n];
    Table *t = create_table(n);
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

    //localidade dos N restaurantes
    for(int i = 0; i < n; i++){
        scanf("%d", &y[i]);
        t[i].rest = y[i];
        //t[i].d = diskraca(g, v, y[i]);
        printf("dist: %d\n", t[i].d);
        if(flag2 == false){
            for(int j = 0; j < m; j++){
                delivered[j] = y[i];
            }
            flag2 = true;
        }
    }
    *t[0].d = 12321968;
    *t[1].d = 12322088;
    *t[2].d = 12325680;
    *t[3].d = 12325800;
    
    scanf(" %s", command);
    do{
        if(command[0] == 'N'){
            w++;
            scanf("%d %d", &id, &z);
            printf("to aq\n");
            //adiciona pedido na fila 
            aux = new_order(id, z);
            q = enqueque(q, aux);
            printf("to aq2\n");
            //print_list(q->head);

            printf("+%d %d\n", id, w);
            printf("to aq3\n");
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
            scanf("%d", &dist);
            dist = -1;
            w--;
            for(int i = 0; i < n; i++){
                if(dist > t[i].d[delivered[ent]] + t[i].d[q->head->next->dest] || dist == -1){
                    rest_aux = t[i].rest;
                    dist = t[i].d[delivered[ent]] + t[i].d[q->head->next->dest];
                }
            }
            aux = last(q->head);
            printf("%d %d %d %d %d\n", q->head->next->id, delivered[ent], rest_aux, q->head->next->dest, dist);
            delivered[ent] = q->head->next->dest;
            list_delete2(q->head, aux->id);
        }

        scanf(" %s", command);

    }while(command[0] != 'E');

    //printa listas de adjacencia
    /* for(int i = 0; i < v; i++){
        if(g[i].head->next){
            print_list(g[i].head, i);
        }
    } */
    
    return 0;
}

/* 10 25 4 10
0 1 930
0 3 490
0 5 756
0 8 702
1 4 453
1 7 784
1 9 227
2 4 118
2 5 744
2 6 140
2 9 476
3 5 157
3 6 594
3 7 807
3 9 10
4 5 273
4 6 831
4 8 134
4 9 349
5 6 53
5 8 25
6 8 799
6 9 975
7 8 741
7 9 733
0 1 3 9
NEW 0 7
NEW 1 6
NEW 2 7
NEW 3 7
NEW 4 5
NEW 5 6
NEW 6 7
NEW 7 4
NEW 8 4
NEW 9 6
NEW 10 6
NEW 11 5
NEW 12 6
NEW 13 8
NEW 14 2
NEW 15 4
NEW 16 6
NEW 17 5
NEW 18 2
NEW 19 7
NEW 20 8
NEW 21 7
NEW 22 8
NEW 23 7
NEW 24 2
NEW 25 7
NEW 26 4
NEW 27 4
NEW 28 5
NEW 29 5
DLV 0
DLV 9
DLV 9
DLV 9
DLV 0
DLV 2
DLV 1
DLV 1
DLV 5
DLV 7
DLV 4
DLV 2
DLV 5
DLV 9
DLV 9
DLV 4
DLV 1
DLV 0
DLV 6
DLV 6
DLV 4
DLV 1
DLV 1
DLV 2
DLV 8
DLV 3
DLV 2
DLV 1
DLV 2
DLV 7
END
 */