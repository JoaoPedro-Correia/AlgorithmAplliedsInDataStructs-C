/*FACO PRE-PROCESSAMENTO PARA O COMPILADOR NAO
 * CHAMAR ESSAS BIBLIOTECAS DUAS VEZES, JA QUE EU CHAMO ELAS EM MAIS QUE UM
 * ARQUIVO*/
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

/*ESTRUTURA DO NO*/
struct node {
  int val;           /*VALOR DO ELEMENTO*/
  struct node *next; /*APONTA PARA O PROXIMO ELEMENTO*/
};

/*ESTRUTURA DA LISTA*/
struct list {
  struct node *first; /*APONTO PARA O PRIMEIRO ELEMENTO*/
  struct node *last;  /*APONTO PARA O ULTIMO ELEMENTO*/
  int total;          /*QUANTIDADE DE ELEMENTOS*/
};

/*CRIO UMA LISTA E PRE-INICIALIZO SEUS VALORES*/
struct list *list_new() {
  struct list *l = (struct list *)malloc(sizeof(struct list));
  if (l == NULL) { /*VERIFICO SE A MEMORIA CONSEGUIU SER ALOCADA*/
    printf("Not memmory!\n");
    exit(1);
  }

  l->first = NULL;
  l->last = NULL;
  l->total = 0;
  return l;
}

/*CRIO UM nó DA LISTA COM UM VALOR JA DEFINIDO*/
struct node *node_creat(int num) {
  struct node *n = (struct node *)malloc(sizeof(struct node));

  if (n == NULL) { /*VERIFICO SE A MEMORIA CONSEGUIU SER ALOCADA*/
    printf("Not memmory!\n");
    exit(1);
  }

  n->val = num; /*ADICIONO O VALOR NO ELEMENTO*/

  return n;
}

/*ADICIONO UM VALOR NA LISTA DE FORMA ORDENADA*/
void list_add(struct list *l, int num) {
  struct node *n = node_creat(num); /*CRIO UM ELEMENTO*/

  struct node *aux = l->first; /*PONTEIRO QUE PERCORRE A LISTA*/
  struct node *behind = NULL;  /*PONTEIRO PARA O ELEMENTO ANTERIOR*/

  /*LOCALIZO A POSICAO PARA INSERCAO*/
  while (aux != NULL && aux->val < num) {
    behind = aux;
    aux = aux->next;
  }

  if (behind == NULL) { /*INSIRO O ELEMENTO NO INICIO DA LISTA*/
    n->next = aux;
    l->first = n;
  } else { /*INSIRO O ELEMENTO NO MEIO*/
    behind->next = n;
    n->next = aux;
  }

  l->total++; /*ADICIONO 1 NA QUANTIDADE DE ELEMENTOS*/
}

/*REMOVO UM ELEMENTO DA LISTA COM BASE NO SEU VALOR*/
/*RETORNA
 * 0 CASO NÃO TENHA O ELEMENTO
 * 1 SE TIVER*/
int list_remove(struct list *l, int num) {
  /*PONTEIROS PARA PERCORRER A LISTA*/
  struct node *aux = l->first;
  struct node *behind = NULL; /*ELEMENTO ANTERIOR*/

  while (aux != NULL && aux->val != num) { /*BUSCO O ELEMENTO*/
    behind = aux;
    aux = aux->next;
  }

  if (aux == NULL) { /*NAO TEM ELEMENTO COM O VALOR*/
    return 0;
  } else if (behind == NULL) { /*REMOVO O PRIMEIRO*/
    l->first = aux->next;
  } else { /*REMOVO DO MEIO OU O ULTIMO*/
    behind->next = aux->next;
  }

  free(aux);  /*DESALOCO A MEMORIA*/
  l->total--; /*SUBTRAIO 1 NA QUANTIDADE DE ELEMENTOS*/
  return 1;
}

/*DESALOCO DA MEMORIA TODA A LISTA*/
void list_clear(struct list *l) {
  struct node *n = l->first; /*PONTEIRO PARA PERCORRER*/

  while (l->first != NULL) { /*PERCORRO A LISTA*/
    l->first = n->next;
    free(n); /**DESALOCO OS ELEMENTOS*/
    n = l->first;
  }
  free(l); /*DESALOCO A LISTA*/
}

/*BUSCO O VALOR DO ELEMENTO COM NA SUA POSICAO NA LISTA*/
int list_search(struct list *l, int ind) {
  if (ind > l->total) { /*A FILA NAO TEM ELEMENTO NESSA POSICAO*/
    printf("Overflow!\n");
    return -1;
  }

  int i;
  struct node *n = l->first; /*PONTEIRO QUE PERCORRE A LISTA*/
  for (i = 0; i < ind; i++) {
    n = n->next;
  }

  return n->val; /*VALOR DO ELEMENTO*/
}

/*BUSCA O ELEMENTO NA LISTA*/
/*RETORNA
 * 1 SE ENCONTRAR
 * 0 SE NAO ENCONTRAR*/
int list_search_element(struct list *l, int value) {
  struct node *n = l->first; /*PONTEIRO QUE PERCORRE A LISTA*/

  while (n != NULL && n->val != value) { /*BUSCA NA LISTA*/
    n = n->next;
  }

  if (n == NULL) { /*NAO ACHOU O ELEMENTO*/
    return 0;
  } else { /*ACHOU O ELEMENTO*/
    return 1;
  }
}

/*RETORNO A QUANTIDADE DE ELEMENTOS NA LISTA*/
int get_total(struct list *l) { return l->total; }
