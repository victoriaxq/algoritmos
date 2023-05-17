#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[10];
  unsigned int idade;
} Player;

typedef struct no{
  Player p;
  struct no *next;
} No;

Player ler_Pessoa(){

  Player p;
  printf("nome:");
  scanf(" %s", p.nome);

  printf("idade:");
  scanf("%d", &p.idade);

  return p;
}

No *empilhar(No *topo)
{

  No *novo = (No *)malloc(sizeof(No));
  if (novo == NULL)
  {
    printf("se m4ta");
    exit(0);
  }
  else
  {
    novo->p = ler_Pessoa();
    novo->next = topo;
    return novo;
  }
  return NULL;
}

No *desempilhar(No **topo)
{
  if (topo != NULL)
  {
    No *remover = *topo;
    *topo = remover->next;
    return remover;
  }
  else
  {
    printf("vazio");
  }
  return NULL;
}

void imprimePilha(No *topo)
{
  printf("imprimindo pilha:\n");
  while (topo != NULL)
  { // while(topo != NULL)
    printf("nome: %s\nidade: %d", topo->p.nome, topo->p.idade);
    topo = topo->next;
  }
  printf("\npilha impressa :)\n");
}

int main()
{

  int opcao;
  No *topo = NULL; //inicio da pilha
  No *remover;

  do
  {
    printf("\t--- MENU ---\n");
    printf("1... Empilha\n");
    printf("2... Desempiha\n");
    printf("3... Imprime\n");
    printf("4... sai\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      topo = empilhar(topo);
      break;

    case 2:
      remover = desempilhar(&topo);
      if (remover){
        printf("deu bom");
      }
      break;

    case 3:
      imprimePilha(topo);
      break;

    default:
      printf("invalido");
    }

  } while (opcao != 4);

      return 0;
}