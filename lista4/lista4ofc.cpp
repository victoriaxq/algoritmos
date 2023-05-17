#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct queue{
    struct queue *next;
    int value;
}Queue;

typedef struct vertex{
    int value;
    bool visited;
    int grade;
    Queue *sentinel;
    Queue *last;
}Vertex;

void sentinelinhe(Vertex *queue){
    Queue *sentinelo = (Queue *)malloc(1* sizeof(Queue));
    if(sentinelo){
        queue->sentinel = sentinelo;
    }
}

void enqueue(Vertex *queue, int value){
    Queue *new_node = (Queue *)calloc(1,sizeof(Queue));
    if(new_node != NULL){
        new_node->next = NULL;
        new_node->value = value;

        if(queue->sentinel->next == NULL){
            queue->sentinel->next = new_node;
            queue->last = new_node;
        }else{ 
            queue->last->next = new_node;
            queue->last = new_node;
        }
    }
}

void print_queue(Vertex *queue){
    Queue *aux = queue->sentinel;
    while(aux){
        printf("value: %d \n", aux->value);
        aux = aux->next;
    }
}

bool find_node(Vertex *queue, int value){
    Queue *aux = queue->sentinel->next;
    if(aux){
        while(aux != queue->last){
            if(aux->value == value){
                return true;
            }
            aux = aux->next;   
        }
        if(aux){
            if(aux->value != value){
                return false;
            }
        }else{
            return false;
        }
    }

}

bool find_node2(Vertex *queue,int value){
    Queue *aux = queue->sentinel->next;
    while(aux){
        if(aux->value == value){
            printf("achamos o valor %d!\n", aux->value);
            return true;
        }else{
            aux = aux->next;
        }

        if(aux == queue->last && aux->value != value){
            return false;
        }
    }
}

void remove(Vertex *queue, int value){
    Queue *aux = queue->sentinel->next;
    Queue *remove = NULL;
    Queue *aux2 = NULL;
    Queue *new_last = NULL;
    //caso seja o primeiro da lista fora o sentinela
    if(queue->sentinel->next){
        if(queue->sentinel->next->value == value){
            remove = queue->sentinel->next;
            queue->sentinel->next = remove->next;
            //return queue->sentinel->next;
        }else{
            while(aux->next && aux->next->value != value){
                aux = aux->next;
            }
            if(aux->next){
                remove = aux->next;
                new_last = aux;
                aux->next = remove->next;
            }
        }
        
        if(remove == queue->last){
            queue->last = aux;
        }else if(aux == NULL){
            queue->last = NULL;
        }
    }
}

void empty(Vertex *queue){
    while(queue->sentinel->next){
        remove(queue, queue->last->value);
    }
}

int main(){

    int v = 0, e = 0, a = 0, b = 0, x = 0, c = 0, vAux = 0, flag = 0, socorro = 0, counter = 0;
    char command[4] = {0};
    printf("digite V e E >>> ");
    scanf("%d %d", &v, &e);
    vAux = v;
    Vertex *vertex = (Vertex *)calloc(v, sizeof(Vertex));
    int ctr[v] = {0};
    Queue *aux0, *aux1 = NULL;

    for(int i = 0; i < v; i++){
        ctr[i] = i;
        vertex[i].value = i;
        vertex[i].grade = 0;
        vertex[i].visited = 0;
        sentinelinhe(&vertex[i]);
        vertex[i].last = NULL;
        vertex[i].sentinel->next = NULL;
    } 

    printf("agora, as arestas: \n");
    for(int i = 0; i < e; i++){
        scanf("%d %d", &a, &b);

        vertex[a].grade++;
        vertex[b].grade++;

        enqueue(&vertex[a], b);
        enqueue(&vertex[b], a);
        
    }
    
    printf("agora, o numero de operacoes a serem feitas: \n");
    scanf("%d", &x);
    
    for(int i = 0; i < x; i++){
        printf("diga o comando, chefe: \n");
        scanf("%s %d %d", command, &a, &b);

        if(command[0] == 'C'){ //ctr
            counter++;
            a = ctr[a];
            b = ctr[b];

            //apagar um dos adjacentes do outro (funciona!)
            for(int i = 0; i < vAux; i++){
                if(ctr[i] == b){
                    remove(&vertex[a], i);
                    vertex[a].grade--;
                }
                if(ctr[i] == a){
                    remove(&vertex[b], i);
                    vertex[b].grade--;
                }
            }
            
            /* printf("APOS APAGAR UM DOS ADJ DO OUTRO\n");
            for(int i = 0; i < vAux; i++){
                printf("\n");
                printf("o representante de %d eh %d!\n", i, ctr[i]);
                printf("vertice %d:\n", i);
                print_queue(&vertex[i]);
                //printf("%d\n", vertex[i].last->value);
                printf("\n");
            } */

            if(a<b || a>b){
                
                if(a>b){
                socorro = a;
                a = b;
                b = socorro;
                }
                //A é o menor


                //colocar o novovertice para apontar para todos os adjacentes dos vertices contraidos
                aux0 = (Queue *)calloc(vertex[a].grade, sizeof(Queue)); // A
                aux1 = (Queue *)calloc(vertex[b].grade, sizeof(Queue)); // B
            
                if(aux0 && aux1){
                    aux0 = vertex[a].sentinel;
                    aux1 = vertex[b].sentinel->next;
                }

                //A vai apontar pros ajdacentes de B
                while(aux1){
                    if(aux0->next == NULL){
                        enqueue(&vertex[a], aux1->value);
                        vertex[a].grade++;
                    }else{
                        if(aux0->next->value != aux1->value){
                            enqueue(&vertex[a], aux1->value);
                            vertex[a].grade++;
                        }
                        aux0 = aux0->next;
                    }
                    aux1 = aux1->next;
                }

                for(int i = 0; i < vAux; i++){
                    printf("\n");
                    printf("o representante de %d eh %d!\n", i, ctr[i]);
                    printf("vertice %d:\n", i);
                    print_queue(&vertex[i]);
                    //printf("%d\n", vertex[i].last->value);
                    printf("\n");
                }

                empty(&vertex[b]); // esvazia a lista do vertice maior porque n precisa mais dela
                //fazendo sentinela do maior apontar para o sentinela->next do menor
                for(int i = 0; i < vAux; i++){
                    if(ctr[i] == b){
                        vertex[i].sentinel = vertex[a].sentinel;
                    }
                }

                printf("APOS FAZER A APONTAR PROS ADJ DE B\n");
                for(int i = 0; i < vAux; i++){
                    printf("\n");
                    printf("o representante de %d eh %d!\n", i, ctr[i]);
                    printf("vertice %d:\n", i);
                    print_queue(&vertex[i]);
                    printf("\n");
                }

                ctr[a] = a;
                for(int i = 0; i < vAux; i++){
                    if(ctr[i] == b){
                        ctr[i] = a;
                    }
                }
                
                //colocar os adjacentes apontando para o segundo valor o qual eles ainda não apontavam
                for(int i = 0; i < vAux; i++){
                    if(ctr[i] != a){
                        for(int k = 0; k < vAux; k++){
                            if(k != a && ctr[k] == a){
                                if(find_node2(&vertex[i], a) == true && find_node2(&vertex[i], k) == false){
                                    enqueue(&vertex[i],k);
                                    vertex[i].grade++;

                                    printf("ADJACENTES APONTANDO PRO SEGUNDO VALOR Q ELES N APONTAVAM AINDA\n");
                                    for(int j = 0; j < vAux; j++){
                                        printf("\n");
                                        printf("o representante de %d eh %d!\n", j, ctr[j]);
                                        printf("vertice %d:\n", j);
                                        print_queue(&vertex[j]);
                                        //printf("%d\n", vertex[i].last->value);
                                        printf("\n");
                                    }
                                }

                                if(find_node2(&vertex[i], a) == false && find_node2(&vertex[i], k) == true){
                                    enqueue(&vertex[i], a);
                                    vertex[i].grade++;
                                    //flag++;

                                    printf("ADJACENTES APONTANDO PRO SEGUNDO VALOR Q ELES N APONTAVAM AINDA\n");
                                    for(int j = 0; j < vAux; j++){
                                        printf("\n");
                                        printf("o representante de %d eh %d!\n", j, ctr[j]);
                                        printf("vertice %d:\n", j);
                                        print_queue(&vertex[j]);
                                        //printf("%d\n", vertex[i].last->value);
                                        printf("\n");
                                    }
                                }
                            }
                        }
                    }
                }

            }else if(a==b){
                remove(&vertex[a], a);
                vertex[a].grade--;
            }
            
            if(a!=b){
                v--;
            }    
            e--;

            if(a >= b){
                b = c;
            }else{
                a = c;
            }
            printf("%d %d\n", v, (vertex[c].grade - counter));
            
            flag = 0;
        
        }else if(command[0] == 'D'){ //dis
            printf("cu");
        }
        
    //checando se as arestas estão corretas (estão! :D)
    printf("RESULTADO\n");
    for(int i = 0; i < vAux; i++){
            printf("\n");
            printf("o representante de %d eh %d!\n", i, ctr[i]);
            printf("vertice %d:\n", i);
            print_queue(&vertex[i]);
            //printf("%d\n", vertex[i].last->value);
            printf("\n");
        }
    }
    
    return 0;
}