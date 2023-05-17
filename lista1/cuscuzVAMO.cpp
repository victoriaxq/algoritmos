#include <iostream>
#include <string>

using namespace std;

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
    int winner;
    int tie;
}Player;

typedef struct{   
    Card *top;
    Card *bottom; 
    int qt;
}Cuscuz;

Card *add_to_hand(Card *sentinel, Card *tail){

    Card *aux = sentinel;
    //fila vazia
    if(sentinel->next == NULL){
        sentinel->next = tail;
    //fila não vazia
    }else{
        while(aux->next != NULL){
            aux = aux->next;
        }
        aux->next = tail;
        tail->next = NULL;
    }
    return tail;
    free(aux);
} //att qt

Card *list_delete(Card *sentinel){
    Card *removed = NULL;
    if(sentinel->next){
        removed = sentinel->next;
        sentinel->next = removed->next;
    }
    free(removed);
    return(sentinel);
}

Card *dequeue(Player p){

    Card *removed = p.sentinel->next;

    p.sentinel = list_delete(p.sentinel);
    if(p.sentinel->next == NULL){
        p.tail = p.sentinel;
        p.loser = 1;
    }

    return p.sentinel;
}