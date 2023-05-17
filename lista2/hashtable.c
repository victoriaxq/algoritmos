#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*
numero definido de elementos
tamanho da hastable = primo mais prox de (2 * numEltos)

num de eltos = 15 --> tamHashTable = 29 ou 31 */
#define TAM 31

//inicializa todas as posicoes como 0 (vazio)
void startTable(int t[]){
    for(int i = 0; i < TAM; i++){
        t[i] = 0;
    }
}

int funcaoHash(int chave){
    return chave%TAM;
}

void insert(int valor, int t[]){

    int id = funcaoHash(valor);
    //tratamento de colisao
    while(t[id] != 0){
        id = funcaoHash(id+1);
    }
    t[id] = valor;

}

int busca(int t[], int chave){

    int id = funcaoHash(chave);
    while(t[id] != 0){
        if(t[id] == chave){
            return t[id];
        }else{
            id = funcaoHash(id + 1);
        }
    }return 0;
    
}

void imprimir(int t[]){
    int i;
    for(int i = 0; i < TAM; i++){
        printf("posicao %d = %d\n", i, t[i]);
    }
}

int main(){

    int tabela[TAM];
    int opcao, valor, buscou;

    startTable(tabela);

    do{
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Imprimir\n");
        scanf("%d", &opcao);
        switch(opcao)
        {
        case 1:
            printf("\tdigite valor a ser inserido >> ");
            scanf("%d", &valor);
            insert(valor, tabela);
            break;

        case 2:
            printf("\tdigite valor a ser buscado >> ");
            scanf("%d", &valor);
            buscou = busca(tabela, valor);
            if(buscou != 0){
                printf("\to valor eh %d", buscou);
            }else{
                printf("\to valor eh vazio!");
            }
            break;

        case 3:
            imprimir(tabela);
            break;

        default:
            printf("\topcao invalida\n.");
            break;
        }

    }while(opcao != 0);
    

    return 0;
}