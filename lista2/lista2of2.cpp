#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    unsigned tstmp;
    unsigned ip_cliente;
    unsigned posicao;
}Conexao;

typedef struct{
    Conexao *conexao;
    int qt_chaves;
    unsigned tam;
}Hashtable;

Hashtable *criaHashtable(int tam){

    Hashtable *h = (Hashtable *)calloc(tam, sizeof(Hashtable));
    if(h == NULL){
        printf("erro na função de criarHashtable");
        free(h);
        exit(1);
    }
    return h;
}

int funcaoHash(int tam, unsigned timestamp){
    return timestamp%tam;
}

int binarySearch(Conexao *vet, unsigned tsp, int tam){
    int esq = 0, dir = tam-1, meio;
        while(esq <= dir){
            meio = (dir+esq)/2;
            //printf("TS: %d -- TS2: %d\n", vet[meio].tstmp, tsp);
            if(tsp == vet[meio].tstmp){
                return meio;
            }else if(tsp > vet[meio].tstmp){
                esq = meio + 1;
            }else if(tsp < vet[meio].tstmp){
                dir = meio - 1;
            }
        }
    return -1; 
}

void printaVet(int *vet, int tam){
    for(int i = 0; i < tam; i++){
        printf("%d\n",vet[i]);
    }
}

int particiona_quick(Conexao *vetor, int inicio, int final){
    int esq, dir, pivo, aux;

    esq = inicio;
    dir = final;
    pivo = vetor[inicio].tstmp;

    while(esq<dir){
        while(vetor[esq].tstmp <= pivo){
            esq++;
        }
        while(vetor[dir].tstmp > pivo){
            dir--;
        }
        if(esq < dir){
            aux = vetor[esq].tstmp;
            vetor[esq].tstmp = vetor[dir].tstmp;
            vetor[dir].tstmp = aux;
        }
    }
    vetor[inicio].tstmp = vetor[dir].tstmp;
    vetor[dir].tstmp = pivo;

    return dir;
}

void quicks(Conexao *vetor, int inicio, int fim){
    int pivo;
    if(fim>inicio){
        pivo = particiona_quick(vetor, inicio, fim);
        quicks(vetor, inicio, pivo -1);
        quicks(vetor, pivo+1, fim);
    }
}

int main(){

    int contador_L = 0,tam, tam2, pivo = 0, aux, contador, busca, k, contador_L2 = 0;
    float LMax = 0,  fator_carga = 0;
    char comando[4];
    unsigned pos, pos2, timestamp, timestamp2, ip_cliente;

    scanf("%d %f", &tam, &LMax);
    Hashtable *hashtable = criaHashtable(tam);
    Hashtable *hash_aux = NULL;
    int *vetorAux = NULL;

    // NEW 9 2031788877
    do{
        scanf(" %s", comando);


        // NEW T C : indica uma nova conexão com timestamp T e cliente C
        if(strcmp(comando, "NEW") == 0){

            scanf("%u %u", &timestamp, &ip_cliente);
            fator_carga = (float)contador_L/tam; //pro rehash

            if((float)(fator_carga) > LMax){
                
                tam2 = (2*tam) +1;
                hash_aux = criaHashtable((tam2));
            
                for(int i = 0; i < tam; i++){
                    for(int j = 0; j < hashtable[i].qt_chaves; j++){

                    pos2 = funcaoHash((2*tam)+1, hashtable[i].conexao[j].tstmp);
                    tam2 = (2*tam)+1;
                    hash_aux[pos2].conexao = (Conexao *)realloc(hash_aux[pos].conexao, sizeof(Conexao) * (hash_aux[pos2].qt_chaves+1));
                    if(hash_aux == NULL){
                        //printf("erro realloc rehash");
                        exit(2);
                    }

                    hash_aux[pos2].conexao[hash_aux[pos2].qt_chaves].ip_cliente = hashtable[i].conexao[j].ip_cliente;
                    hash_aux[pos2].conexao[hash_aux[pos2].qt_chaves].tstmp = hashtable[i].conexao[j].tstmp;
                    hash_aux[pos2].conexao[hash_aux[pos2].qt_chaves].posicao = hash_aux[pos2].qt_chaves;
                    hash_aux[pos2].qt_chaves++;

                    quicks(hashtable[pos2].conexao, 0, (hash_aux[pos2].qt_chaves)-1);
                    //printaVet(hash_aux[pos2].conexao[hash_aux[pos2].qt_chaves].tstmp, tam2);
                    }
                    free(hashtable[i].conexao);
                }

                free(hashtable);
                hashtable = hash_aux;
                hash_aux = NULL;
                tam = tam2;
                //fator_carga = (float)contador_L/tam2;
                //printf("fator carga atualizado: %f\n", fator_carga);
            } 

            pos = funcaoHash(tam, timestamp);
            //printf("fator carga: %f\n", fator_carga);
            //printf("contador L: %d\n", contador_L);//printf("contador L: %d\n", contador_L);
            hashtable[pos].conexao = (Conexao *)realloc(hashtable[pos].conexao, sizeof(Conexao) * (hashtable[pos].qt_chaves+1));
            //printf("oioio\n");
            hashtable[pos].conexao[hashtable[pos].qt_chaves].ip_cliente = ip_cliente;
            //printf("oi\n");
            hashtable[pos].conexao[hashtable[pos].qt_chaves].tstmp = timestamp;
            hashtable[pos].conexao[hashtable[pos].qt_chaves].posicao = hashtable[pos].qt_chaves; //posicao no vetor de structs
            hashtable[pos].qt_chaves++;
            contador_L++;
            
            printf("%u %u\n", pos, hashtable[pos].qt_chaves);
        // QRY T : indica uma consulta do processo auditor a uma possível conexão no timestamp T
        }else if(strcmp(comando, "QRY") == 0){

            scanf("%u", &timestamp2);
            //printaVet(vetorAux, contador_L);
            //busca binaria
            k = funcaoHash(tam,timestamp2); //posicao

            if(hashtable[k].qt_chaves > 0){

                busca = binarySearch(hashtable[k].conexao, timestamp2, hashtable[k].qt_chaves);
                if(busca != -1){
                    //printf("busca: %d\n", busca);
                    printf("%u %u\n", hashtable[k].conexao[busca].ip_cliente, hashtable[k].conexao[busca].posicao);
                }else{
                    printf("-1 -1\n");
                } 
            }else{
                printf("-1 -1\n");
            }
        }
 
    }while(strcmp(comando,"END") != 0);

    /* for(int a = 0; a < tam; a++){
        printf("indice %d:\n", a);
        for(int b = 0; b < hashtable[a].qt_chaves; b++){
            printf("timestamp %d: %u\nIP:%u\n", b, hashtable[a].conexao[b].tstmp, hashtable[a].conexao[b].ip_cliente);
        }
        printf("\n");
    
    }  */
    
    return 0;
}