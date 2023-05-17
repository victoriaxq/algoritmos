#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct card{
    int value;
    char naipe;
    struct card *next;
}Card; // node 

typedef struct{
    Card carta[10000];
    Card *mao;
    int i;
    int qtdCarta;
}Player;

Card *add_node(Card **fila, int value, char naipe){

    Card *aux, *novo = (Card *)calloc(1,sizeof(Card));

    if(novo){
       novo->value = value;
       novo->naipe = naipe;
       novo->next = NULL;

       if(*fila == NULL){
        *fila = novo;
       }else{
        aux = *fila;
        while(aux->next){
            aux = aux->next;
        }
        aux->next = novo;

       }
    }else{
        printf("se m4ta");
        exit(0);
    }

}

Card *remover_da_Hand(Card **fila, int vale, char naipe){

    Card *rem = NULL;

    if(*fila){
        rem = *fila;
        *fila = rem->next;
    }else{
        printf("fila vazia");
    }
    return rem;
}

void print_Hand(Card *fila){
    printf("fila:\n");
    printf("%d%c", fila->value, fila->naipe);
    fila = fila->next;
    printf("\nfim fila\n");
}


int main(){ 

    int n, round = 0, flag = 0;
    Card *hand = NULL;
    char um, dois, tres;

    scanf("%d", &n); // num players

    Player players[n];

    //deal
    while((scanf(" %c%c%c", &um, &dois, &tres) != EOF) && (flag == 0)){
   
        if('D' == um && 
           'E' == dois &&
           'A' == tres){
        
          printf("entrou no dea\n");
          for(int i = 0; i < n; i++){

            scanf("%d%c", &players[i].carta[i].value, &players[i].carta[i].naipe);
            //printf("A carta do jogador %d eh %d%c\n", i+1, players[i].carta[i].value,players[i].carta[i].naipe);
            add_node(&players[i].mao, players[i].carta[i].value, players[i].carta[i].naipe);
            //print_Hand(players[i].mao);
            scanf(" %c%c%c", &um, &dois, &tres);
            }

        }/* else if('R' == um && 
                    'N' == dois &&
                    'D' == tres){ 

            }else if('E' == um && 
                    'N' == dois &&
                    'D' == tres){
                round++;
                flag = 1; 
            } */

    }

   
    return 0;
}