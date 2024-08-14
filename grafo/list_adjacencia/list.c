/*FACO PRE-PROCESSAMENTO PARA O COMPILADOR NAO
 * CHAMAR ESSAS BIBLIOTECAS DUAS VEZES, JA QUE EU CHAMO ELAS EM MAIS QUE UM
 * ARQUIVO*/
#include "node.c"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*ESTRUTURA DA LISTA*/
struct list {
  Node *first; /*APONTO PARA O PRIMEIRO ELEMENTO*/
  Node *last;  /*APONTO PARA O ULTIMO ELEMENTO*/
  int total;   /*QUANTIDADE DE ELEMENTOS*/
};

/*INICIALIZO AS TRES VARIAVEIS DA ESTRUTURA list
 * A PROPRIA LISTA É O PARAMETRO*/
void list_init(struct list *l) {
  l->first = NULL;
  l->last = NULL;
  l->total = 0;
}

/*CRIO UMA LISTA E PRE-INICIALIZO SEUS VALORES*/
struct list *list_new() {
  struct list *l = (struct list *)malloc(sizeof(struct list));

  if (l == NULL) { /*VERIFICO SE A MEMORIA CONSEGUIU SER ALOCADA*/
    printf("Not memmory!\n");
    exit(1);
  }

  list_init(l);
  return l;
}

/*CRIO UM VETOR DE LISTA E PRE-INICIALIZO SEUS VALORES EM SEUS INDICES
 * PASSO COMO PARAMETRO O TAMANHO DA LISTA*/
struct list *list_new_vector(int n) {
  struct list *l = (struct list *)malloc(n * sizeof(struct list));
  int i;

  if (l == NULL) { /*VERIFICO SE A MEMORIA CONSEGUIU SER ALOCADA*/
    printf("Not memmory!\n");
    exit(1);
  }

  for (i = 0; i < n; i++) {
    list_init(&l[i]);
  }

  return l;
}

/*ADICIONO UM VALOR NA LISTA DE FORMA ORDENADA*/
void list_add(struct list *l, int id, int distancia) {
  struct node *n = node_creat(id, distancia); /*CRIO UM ELEMENTO*/
  set_id(n, id);               // ADICIONO A MATRICULA NO ESTRUTURA
  set_distancia(n, distancia); // ADICIONO O NOME NA ESTRUTURA

  struct node *aux = l->last; /*PONTEIRO QUE PERCORRE A LISTA*/

  if (aux == NULL) { /*INSIRO O ELEMENTO NO INICIO DA LISTA*/
    l->first = n;
    l->last = n;
  } else { /*INSIRO O ELEMENTO NO MEIO*/
    aux->next = n;
    l->last = n;
  }

  l->total++; /*ADICIONO 1 NA QUANTIDADE DE ELEMENTOS*/
}

/*REMOVO UM ELEMENTO DA LISTA COM BASE NO SEU VALOR*/
/*RETORNA
 * 0 CASO NÃO TENHA O ELEMENTO
 * 1 SE TIVER*/
int list_remove(struct list *l, const int identificacao) {
  /*PONTEIROS PARA PERCORRER A LISTA*/
  struct node *aux = l->first;
  struct node *behind = NULL; /*ELEMENTO ANTERIOR*/

  while (aux != NULL && (get_id(aux) != identificacao)) { /*BUSCO O ELEMENTO*/
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

  node_free(aux); /*DESALOCO A MEMORIA*/

  l->total--; /*SUBTRAIO 1 NA QUANTIDADE DE ELEMENTOS*/
  return 1;
}

/*DESALOCO DA MEMORIA TODA A LISTA*/
void list_clear(struct list *l) {
  struct node *n = l->first; /*PONTEIRO PARA PERCORRER*/

  while (l->first != NULL) { /*PERCORRO A LISTA*/
    l->first = n->next;
    node_free(n); /**DESALOCO OS ELEMENTOS*/
    n = l->first;
  }
  free(l); /*DESALOCO A LISTA*/
}

/*DESALOCO DA MEMORIA TODA A LISTA*/
void list_clear_vector(struct list *l, int n) {
  int i;

  for (i = 0; i < n; i++) {
    struct node *n = l->first; /*PONTEIRO PARA PERCORRER*/

    while (l->first != NULL) { /*PERCORRO A LISTA*/
      l->first = n->next;
      node_free(n);
      n = l->first;
    }
  }
  free(l);
  /*DESALOCO A LISTA*/
}

/*BUSCA O ELEMENTO NA LISTA*/
/*RETORNA
 * 1 SE ENCONTRAR
 * 0 SE NAO ENCONTRAR*/

/*IDENTIFICACAO PODE SER O id OU O NUMERO DE distancia DO ALUNO*/
int list_search_element(struct list *l, int identificacao) {

  struct node *n = l->first; /*PONTEIRO QUE PERCORRE A LISTA*/

  while (n != NULL && (identificacao != get_id(n))) { /*BUSCA NA LISTA*/
    n = node_next(n);
  }

  if (n == NULL) { /*NAO ACHOU O ELEMENTO*/
    return 0;
  } else { /*ACHOU O ELEMENTO*/
    return 1;
  }
}

/*RETORNO A QUANTIDADE DE ELEMENTOS NA LISTA*/
int get_total(struct list *l) { return l->total; }

/*RETORNA O PRIMEIRO ELEMENTO*/
Node *get_first_element(struct list *l) { return l->first; }

/*RETORNA O ULTIMO ELEMENTO*/
Node *get_last_element(struct list *l) { return l->last; }

/*RETORNA O ELEMENTO NA POSIÇÃO INDICADA*/
Node *get_current_element(struct list *l, int n) {
  int i;
  Node *no = l->first;

  if (n >=
      l->total) { // VALOR PASSADO É MAIOR QUE O NUMERO DE ELEMENTOS DA LISTA
    printf("Overflow! Lista tem %d elementos\n", l->total);
    exit(1);
  }

  for (i = 0; i < l->total; i++) { // PERCORRER A LISTA
    no = node_next(no);
  }

  return no;
}
