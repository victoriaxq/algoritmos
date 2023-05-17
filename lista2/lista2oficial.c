#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
    unsigned int tmscmp;
    unsigned int cliente; 
}Conexao;

typedef struct node{
    Conexao conexao;
    struct node *next;
}Node;

int main(){

    return 0;
}