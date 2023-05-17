#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct G{
    int vertice;
    int arestas;
    int comprimento;
    struct G *next;
}Grafo;

typedef struct {
    int tamanho; //tamanho do grafo
    Grafo *cabeca;
}Lista;

typedef struct P{
    int id;
    int local;
    struct P *prox;
}Pedidos;

typedef struct{
    int tam;
    Pedidos *head;
    Pedidos *tail;
}Fila;

typedef struct {
    int restaurante;
    int *p; //ponteiro p restaurantes 
}Tabelinha;

typedef struct {
    int local;
    int peso;
}Heap;

//funções relacionadas a fila de pedidos 

Fila CriaFiila (Fila fila) {

    fila.head = (Pedidos*) malloc(sizeof(Pedidos));;
    fila.tail = fila.head;
    fila.head->prox = NULL;
    fila.tam = 0;  

    return fila;
}

Pedidos *Insere (Pedidos *pedidos, int id, int local) {
    Pedidos *novo;

    novo = (Pedidos*)malloc(sizeof(Pedidos));
    novo->id = id;
    novo->local = local;
    novo->prox = NULL;
    pedidos->prox = novo;
   
    return pedidos->prox;
}

Pedidos *Remove (Pedidos *head, Pedidos **tail) {
    Pedidos *xau;
    xau = head->prox;
    head->prox = xau->prox;
    free(xau);
    if(head->prox == NULL){
        *tail = head;
    }
    
    return head;
}

//funções relacionadas ao grafo que mapeia a cidade 

Lista *CriaLista (Lista *lista, int vertice) {
    int i;

    lista = (Lista*) malloc(vertice * sizeof(Lista));

    for(i = 0; i < vertice; i++){ //inicializa a lista 
        lista[i].tamanho = 0;
        lista[i].cabeca = (Grafo*)malloc(sizeof(Grafo));
        lista[i].cabeca->next = NULL; 
    }

    return lista;
}

Grafo* InsereNaLista (Grafo *ponteirinho, int vertice, int L) {
    Grafo *grafo;

    grafo = (Grafo*)malloc(sizeof(Grafo));

    grafo->vertice = vertice;
    grafo->comprimento = L;
    grafo->next = ponteirinho->next;
    ponteirinho->next = grafo;

    return ponteirinho;
}

//outras funçõeszinhas

void bubbleup (Heap *heap, int tamanho) {
    Heap nhe;

    while (tamanho > 0 && heap[tamanho].peso <= heap[(tamanho - 1)/ 2].peso) {
        nhe = heap[tamanho];
        heap[tamanho] = heap[(tamanho - 1)/ 2];
        heap[(tamanho - 1)/ 2] = nhe;
        tamanho = (tamanho - 1)/ 2;
    }   
}

Heap *insert (Heap *heap, int local, int peso, int *tamanho, int *tamanhomax) {
    if (*tamanho == *tamanhomax) {
        *tamanhomax = 2 * (*tamanho);
        heap = (Heap*)realloc(heap, (*tamanhomax) * sizeof(Heap)); 
    }
    heap[*tamanho].local = local;
    heap[*tamanho].peso = peso;
    bubbleup(heap, *tamanho);
    (*tamanho)++;

    return heap;
}

void bubbledown (Heap *heap, int a, int tamanho) {
    Heap aux;
    int left, right, middle;
    left = 2*a + 1;
    right = 2*a + 2;
    middle = a;

    if (left < tamanho && heap[left].peso <= heap[middle].peso) {
        middle = left;
    }
    if (right < tamanho && heap[right].peso <= heap[middle].peso) {
        middle = right;
    }

    if (middle != a) {
        aux = heap[middle];
        heap[middle] = heap[a];
        heap[a] = aux;
        bubbledown (heap, middle, tamanho);
    }
}

int extract (Heap *heap, int *peso, int *tamanho) {
    Heap r;
    Heap hihi;
    r = heap[0];

    if (*tamanho > 0) {
        hihi = heap[0];
        heap[0] = heap[(*tamanho) - 1];
        heap[*tamanho - 1] = hihi;
        (*tamanho)--;
        bubbledown(heap, 0, *tamanho);
    }

    *peso = r.peso;
    return r.local;
}

int *Dijkstra (Lista *grafo, int V, int Y) {
    Grafo *oi;
    int i, j;
    int tamanho = 0;
    int tamanhomax = 1;
    int d, u;
    int valor, peso;
    int *D;
    int flag;
    Heap *heap;

    heap = (Heap*)malloc(sizeof(Heap));
    D = (int*)malloc(V * sizeof(int));

    for (i = 0; i < V; i++) {
        D[i] = -1;
    }

    D[Y] = 0;
    heap = insert(heap, Y, 0, &tamanho, &tamanhomax);

    for (i = 0; i < V; i++) {
        //printf("oi");
        u = extract(heap, &d, &tamanho);
        oi = grafo[u].cabeca->next;
        while (oi != NULL) {
            valor = oi->vertice;
            peso = oi->comprimento;
            if (d + peso < D[valor] || D[valor] == -1) {
                D[valor] = d + peso;
                flag = 0;
                for(j = 0; j < tamanho; j++) {
                    if (heap[j].local == valor) {
                        heap[j].peso = D[valor];
                        bubbleup (heap, j);
                        flag = 1;
                    }
                }
                if (flag == 0) {
                    heap = insert(heap, valor, D[valor], &tamanho, &tamanhomax);
                }
            }
            oi = oi->next;
        }
    }

    return D;
}

int main () {
    int V = 0; //numero de localidades
    int E = 0; //numero de vias integrando essas localidades
    int N = 0; //quantidade de lojas na rede 
    int M = 0; //numero de entregadores
    int A; //ponto inicial da via
    int B; //ponto final da via
    int L; //compriento entre os pontos A e B
    int Y; //localidade dos N restaurantes da rede
    char entrada[4]; //entrada a ser digitada, pode ser NEW, CEL OU DLV
    int I; //id do pedido 
    int Z; //localidade em que o pedido deve ser entregue 
    int *entregue;
    int D; //entregador
    Fila fila;
    Lista *lista = NULL;
    Tabelinha *tabelinha;
    Pedidos *aux;
    int i;
    int flag = 0;
    int pedidos = 0;
    int distancia;
    int restaurantezinho;

    scanf ("%d", &V);
    scanf ("%d", &E);
    scanf ("%d", &N);
    scanf ("%d", &M);
    //printf ("%d, %d, %d, %d", V, E, N, M);

    entregue = (int*)malloc(M*sizeof(int));
    tabelinha = (Tabelinha*)malloc(N*sizeof(Tabelinha));

    lista = CriaLista(lista, V);    

    for(i = 0; i < E; i++) {
        scanf ("%d", &A);
        scanf ("%d", &B);
        scanf ("%d", &L);
        lista[A].cabeca = InsereNaLista(lista[A].cabeca, B, L);
        lista[B].cabeca = InsereNaLista(lista[B].cabeca, A, L);
        //printf ("A: %d B: %d L: %d", A, B, L);
    }
    //printf("Mapa:\n");
    /* for(int a = 0; a < V; a++){
        //printf("%d: ", a);
        Grafo *aux1 = lista[a].cabeca->next;
        while(aux1 != NULL){
            //printf("%d / %d, ", aux1->vertice, aux1->comprimento);
            aux1 = aux1->next;
        }
        //printf("\n");
    } */
    //printf("\n");

    for(i = 0; i < N; i++) {
        scanf ("%d", &Y);
        tabelinha[i].restaurante = Y;
        tabelinha[i].p = Dijkstra (lista, V, Y);
        if (flag == 0) {
            for (int j = 0; j < M; j++) {
                entregue[j] = Y;
            }
            flag = 1;
        }
    }

    fila = CriaFiila (fila); //função para inicializar a fila 

    do { 
        scanf (" %3[^ ]", entrada);

        if (strcmp (entrada, "NEW") == 0) { //indica um novo pedido "I" para ser entregue na localidade "Z"
            scanf ("%d %d", &I, &Z);
            fila.tail = Insere(fila.tail, I, Z);
            pedidos++;
            printf("+%d %d\n", I, pedidos);
        }
        else if (strcmp (entrada, "CEL") == 0) { //indica o cancelamento do pedido "I"
            scanf ("%d", &I); 
            aux = fila.head;
            while(aux->prox != NULL && aux->prox->id != I) {
                aux = aux->prox;
            }
            pedidos--;
            if (aux->prox != NULL && aux->prox->id == I) {
                aux = Remove (aux, &fila.tail);
            }
            printf("-%d %d\n", I, pedidos);

        }
        else if (strcmp (entrada, "DLV") == 0) { //indica que o entregador "D" aceitou o próximo pedido da fila 
            scanf ("%d", &D);
            distancia = -1;
            for (i = 0; i < N; i++) {
                if (distancia == -1 || distancia > tabelinha[i].p[entregue[D]] + tabelinha[i].p[fila.head->prox->local]) {
                    distancia = tabelinha[i].p[entregue[D]] + tabelinha[i].p[fila.head->prox->local];
                    restaurantezinho = tabelinha[i].restaurante;
                }
            }
            printf("%d %d %d %d %d\n", fila.head->prox->id, entregue[D], restaurantezinho, fila.head->prox->local, distancia);
            entregue[D] = fila.head->prox->local;
            fila.head = Remove(fila.head, &fila.tail);
            pedidos--;
        }
        
    } while (strcmp (entrada, "END") != 0); //para quando digita END
    
    return 0;
}