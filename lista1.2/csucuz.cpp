#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct card{
    int value;
    int suit;
    struct card *next;
}Card;

typedef struct{
    Card *sentinel;
    Card *tail;
    int qt;
    int loser;
}Player;

typedef struct{   
    Card *top;
    int qt;
}Cuscuz;

Player add_to_hand (Player p, int value, char suit) {

    Card *aux = (Card*) malloc (sizeof(Card));
    aux->value = value;
    aux->suit = suit;
    aux->next = NULL;

    if(p.sentinel->next == NULL){
        p.tail = aux;
        p.sentinel->next = aux;
    }else{
        p.tail->next = aux;
        p.tail = aux;
    }
    
    return p;
}

void print_Hand(Card *fila, int i){
    Card *aux = fila;
    printf("fila do jogador %d: ", i);
    while(aux){
        printf(" %d%c |", aux->value, aux->suit);
        aux = aux->next;
    }
printf("\n");
}

void print_Cuscuz(Card *fila){
    Card *aux = fila;
    printf("pilha do cuscuz:");
    while(aux){
        printf(" %d%c |", aux->value, aux->suit);
         aux = aux->next;
    }
printf("\n");
}

bool endgame_(int qt, Player *p){ 
    int alive = qt;
    for(int i = 0; i < qt; i++){
        if(p[i].loser == 1){
            alive--;
        }
    }
    if(alive == 0){
        return true;
    }else{
        return false;
    }
}

int rwinner(int qt, Player *p){
    Card *aux = (Card *)calloc(1, sizeof(Card));
    
        aux->suit = 'C';
        aux->value = 0;
    
    Card *biggest = aux;
    //printf("w1\n");

    int winner = -1;
    for(int i = 0; i < qt; i++){
        //printf("%d\n", i);

        if(p[i].sentinel->next != NULL && p[i].loser == 0 ){
            if(biggest->value < p[i].sentinel->next->value){
                biggest = p[i].sentinel->next;
                winner = i;
                //printf("w3\n");
            }else if(biggest->value == p[i].sentinel->next->value){
                //printf("w4\n");
                if(biggest->suit < p[i].sentinel->next->suit){
                    biggest = p[i].sentinel->next;     
                    winner = i;
                    //printf("w5\n");
                }else if(biggest->suit == p[i].sentinel->next->suit){ 
                    winner = -1;
                    //printf("w6\n");
                }
            }
        }
    }
    //printf("w7\n");
    free(aux);
    return winner;
}

Cuscuz *player_to_cuscuz( Cuscuz *c, Player *p){
    Card *aux = (Card*)calloc(1,sizeof(Card));
    if(p->sentinel->next){

        aux = p->sentinel->next;
        p->sentinel->next = aux->next;
        aux->next = c->top;
        //aux = c->top;
        c->top = aux;
    }else if(p->sentinel->next == NULL){
        p->loser = 1;
    }

    return c;
}

Player eat_cuscuz(Cuscuz *c, Player *p){

    Card *aux = (Card *)calloc(1,sizeof(Card));
    if (p->qt == 0 || p->sentinel->next == NULL){
        p->sentinel->next = c->top;
        p->tail = c->top;
        p->loser = 0;
    }else{
        p->tail->next = c->top;
    }

    aux = c->top;

    while(aux->next){
        aux = aux->next;
    }
    p->qt += c->qt;
    p->tail = aux;

    return *p;
}

int main(){

    char command[4], suit;
    int n = 0, value = 0, round = 0, winner = -13, alive = 0, w = 0; 
    bool endgame = false;
    scanf("%d", &n);

    Card *aux = NULL;

    Player *p = (Player *)calloc(n, sizeof(Player));
    for(int i = 0; i < n; i++){
        p[i].sentinel = (Card *)calloc(1,sizeof(Card));
        p[i].sentinel->next = NULL;
        p[i].tail = p[i].sentinel;
        p[i].qt = 0;
        p[i].loser = 0;
    }

    scanf(" %s", command);

    do{
        if(command[0] == 'D'){
            for (int i = 0; i < n; i++){
                if (p[i].loser == 0){
                    scanf("%d%c", &value, &suit);
                    p[i] = add_to_hand(p[i], value, suit);
                    p[i].qt++; //print_Hand(p[i].sentinel->next, i);
                }
            }

        }else if(command[0] == 'R'){
            //printf("veio aqui\n");
            w = -1;
            Cuscuz *cuscuz = (Cuscuz *)calloc(1, sizeof(Cuscuz));
            cuscuz->top = NULL;
            cuscuz->qt = 0;

            while(w == -1){
                //printf("veio aqui2\n");
                //checando quantos se ainda tem jogadores
                alive = n;
                for(int i = 0; i < n; i++){
                    if(p[i].loser == 1){
                        alive--;
                    }
                    if(alive == 0){ 
                        endgame = true;
                    }else{
                        endgame = false;
                    }
                    //printf("oi\n");
                }
                if(endgame == true){
                    printf("-1 -1 -1\n"); 
                }
                
                winner = rwinner(n, p);
                w = winner;
                //printf("tchaun\n");

                for(int i = 0; i < n; i++) {
                    if(p[i].loser == 0){
                        cuscuz = player_to_cuscuz(cuscuz, &p[i]);
                        p[i].qt--;
                        cuscuz->qt++; 
                        /* printf("tchau2");
                        print_Hand(p[i].sentinel->next, i);
                        print_Cuscuz(cuscuz->top); */
                    }
                }

                if(winner != -1){
                    // p[winner] vai comer o cuscuz
                    p[w] = eat_cuscuz(cuscuz, &p[w]);
                     Card *cuaux = cuscuz->top;
                    int qt = 0;
                    while(cuaux){
                        qt++;
                        cuaux = cuaux->next;
                    }
                    printf("%d %d %d\n", round, winner, qt);
                    round++;
                }
            }
            free(cuscuz);   
        }
        scanf(" %s", command);
    }while(command[0] !=  'E');

    Card *count;
    int c;
    int c_max = 0;
    for(int i = 0; i < n; i++){
        if(p[i].sentinel->next){
            count = p[i].sentinel->next;
            c = 0;
            while(count){
                c++;
                count = count->next;
            }

            if(c > c_max){
                c_max = c;
                w = i;
            }

        }
    }   
    printf("%d\n", w);

    return 0;
}