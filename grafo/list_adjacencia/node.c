/*FACO PRE-PROCESSAMENTO PARA O COMPILADOR NAO
 * CHAMAR ESSAS BIBLIOTECAS DUAS VEZES, JA QUE EU CHAMO ELAS EM MAIS QUE UM
 * ARQUIVO*/
#ifndef NODE_C
#define NODE_C

#include <stdio.h>
#include <stdlib.h>

/*ESTRUTURA DO NO*/
struct node {
  int id;            /*NOME DO ALUNO*/
  int distancia;     /*CHAMO A MATRICULA DO ALUNO DE ID*/
  struct node *next; /*APONTA PARA O PROXIMO ELEMENTO*/
};

/*CRIO UM nó DA LISTA COM UM VALOR JA DEFINIDO*/
struct node *node_creat(int id, int distancia) {
  struct node *n = (struct node *)malloc(sizeof(struct node));

  if (n == NULL) { /*VERIFICO SE A MEMORIA CONSEGUIU SER ALOCADA*/
    printf("Not memmory!\n");
    exit(1);
  }

  return n;
}

/*RETORNO O PROXIMO NÓ*/
struct node *node_next(struct node *n) { return n->next; }

/*RETORNO O NOME DA ESTRUTURA*/
int get_distancia(struct node *n) { return n->distancia; }

/*ADIONO UM NOME*/
void set_distancia(struct node *n, int distancia) { n->distancia = distancia; }

/*RETORNO O ID/MATRICULA*/
int get_id(struct node *n) { return n->id; }

/*ADICIONO UM ID/MATRICULA*/
void set_id(struct node *n, int id) { n->id = id; }

/*DESALOCO DA MEMORIA*/
void node_free(struct node *n) { free(n); }

/*VERIFICA SE ESTÁ VAZIO*/
int node_empty(struct node *n) { return n == NULL; }

#endif
