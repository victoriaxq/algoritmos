#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct carta{
    int valor;
    char naipe;
    struct carta *next; //cursor
}Carta;

typedef struct{   
    Carta *primeira;
    Carta *ultima;
    int qtd_cartas;
    int indice;
    int empatado;
    int ganhou;
}Jogador;

typedef struct{   
    Carta *topo;
    Carta *ultima; 
    int qtd_cartas;
}Cuscuz;

Carta *insere_na_Fila(Carta *sentinela, Carta *tail){
    Carta *aux = sentinela;

    //fila vazia
    if(sentinela->next == NULL){
        sentinela->next = tail;
    //fila não vazia
    }else{
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = tail;
    }
    return tail;
    free(aux);
}

/* void print_Hand(Carta *fila){
    Carta *aux = fila;
    aux = aux->next;
    printf("fila:\n");
    while(aux){
        printf("%d%c\n", aux->valor, aux->naipe);
         aux = aux->next;
    }
    printf("fim fila\n");
} */

Jogador remove_da_fila2(Jogador jogador){

    if(jogador.qtd_cartas > 1){
        jogador.primeira->next = jogador.primeira->next->next;
    }else{
        jogador.primeira->next = NULL;
        jogador.ultima = jogador.primeira;
    }

    return jogador;
}

Carta *insere_no_Cuscuz(Carta *head, Carta *topo){
    
    if(topo->next == NULL){
        topo->next = head;
    }else{
        //FIFO
        head->next = topo->next;
        topo->next = head;
    }

    //print_Hand(topo);
    return topo;
}

int main(){

    int n; // num jogadores
    // 1. fazer array de jogadores e designar cartas para cada jogador
    char c1, c2, c3; //caracteres da entrada
    char naipe; 
    int valor;
    int qtdDeal = 0;
    int rodada = 0;
    int empate = 0;
    scanf("%d", &n);
    Jogador jogador[n];
    Cuscuz cuscuz;
    Cuscuz aux;
    Carta *maiorCarta = NULL;
    Carta *checaEmpate = NULL;
    Carta *nova = NULL;
    Carta *head = NULL;
    Carta *novoTail = NULL;


    //inicializando struct jogadores
    for(int i = 0; i < n; i++){

        jogador[i].empatado = 0;
        jogador[i].ganhou = 0;
        jogador[i].indice = i;
        jogador[i].qtd_cartas = 0;
        //alocando sentinela
        jogador[i].primeira = (Carta *)malloc(sizeof(Carta));
        if(jogador[i].primeira == NULL){
            //printf("erro ao alocar");
            exit(0);
        }else{
            //criando fila e dizendo que ela ta vazia
            jogador[i].primeira->next = NULL;
        }
    }

    //inicializando struct do cuscuz
    cuscuz.qtd_cartas = 0;
    cuscuz.topo = (Carta *)malloc(sizeof(Carta));
    if(cuscuz.topo){
        cuscuz.topo->next == NULL;
    }else{
        //printf("erro ao alocar");
        exit(2);
    }
    
    while(scanf(" %c%c%c", &c1, &c2, &c3) != EOF){
    
       //deal
       //funcionando! :)
        if(c1 == 'D'){
            //printf("entrou no deal\n");
            qtdDeal++;

            for(int i = 0; i < n; i++){
            
                scanf("%d%c", &valor, &naipe);
                
                //alocando e atribuindo valores pra carta nova (tail)
                nova = (Carta *)malloc(sizeof(Carta));
                if(nova){
                    nova->naipe = naipe;
                    nova->valor = valor;
                    nova->next = NULL;
                }else{
                    //printf("se c0rt4");
                    exit(1);
                }

                jogador[i].ultima = insere_na_Fila(jogador[i].primeira, nova);
                //print_Hand(jogador[i].primeira);
                jogador[i].qtd_cartas++;

                }

        //round
        }else if(c1 == 'R'){
            //printf("entrou no round\n");
            for(int i = 0; i < n; i++){

                //pega carta head antes dela ser removida;
                head = jogador[i].primeira->next;
                
                //remover ultima carta da fila (LIFO) pra jogar ela no cuscuz
                jogador[i] = remove_da_fila2(jogador[i]);
                jogador[i].qtd_cartas--;
                //print_Hand(jogador[i].primeira);
                //printf("%d%c\n", head->valor, head->naipe);

                insere_no_Cuscuz(head, cuscuz.topo);
                //print_Hand(cuscuz.topo);
                cuscuz.qtd_cartas++;
            }

            //o cuscuz tera como ultima carta a carta do primeiro jogador
            //como penultima carta a carta do segundo e como primeira carta a carta do ultimo
            aux = cuscuz;

            //comparando cartas do cuscuz -> vence o numero maior

            if(aux.topo->next){

                maiorCarta = aux.topo->next;
                
                for(int i = cuscuz.qtd_cartas-1 ; i >= 0; i--){
                    //atribui o maiorCarta ao topo
                    
                    if(maiorCarta->valor < maiorCarta->next->valor){
                        maiorCarta = maiorCarta->next;
                        jogador[(i/qtdDeal) - 1].ganhou = 1;
                        
                    }else if(maiorCarta->next->valor < maiorCarta->valor){
                        maiorCarta = maiorCarta; 
                        jogador[(i/qtdDeal)].ganhou = 1;
                        jogador[(i/qtdDeal) + 1].ganhou = 0;

                    //se numero for igual -> C < E < O < P
                    }else if(maiorCarta->next->valor == maiorCarta->valor){

                        if(maiorCarta->naipe < maiorCarta->next->naipe){
                            maiorCarta = maiorCarta->next;
                            jogador[(i/qtdDeal)-1].ganhou = 1;
                            jogador[(i/qtdDeal)].ganhou = 0;

                        //empate
                        }else if(maiorCarta->naipe == maiorCarta->next->naipe){
                            empate = 1;
                        }
                    }
                }  
                //funciona! falta o empate
                //printf("a maior carta e %d%c\n", maiorCarta->valor, maiorCarta->naipe);

                
                if(empate == 1){

                    
                }else{

                    for(int i = cuscuz.qtd_cartas-1 ; i >= 0; i--){
                        if(jogador[i].ganhou == 1){
                        printf("%d %d %d\n",rodada,  
                        
                        
                        , cuscuz.qtd_cartas);
                    }
                }

                }         
            }
            rodada++;
        //END
        }else if(c1 == 'E'){

            free(maiorCarta);
            free(nova);
            free(head);
            free(novoTail);

            for(int i = 0; i < n; i++){
               
            }  

            break;
        } 
    }

    return 0;
}
//nao esquecer de desalocar memoria no fim!