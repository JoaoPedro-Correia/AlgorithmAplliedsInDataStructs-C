#ifndef LIST_C
#define LIST_C

/*CHAMO O ARQUIVO list.c*/
#include "list.c"

typedef struct list List;

/*COLOCO A ASSINATURA DAS FUNÇÕES QUE MANIPULAM A STRUCT list
 * A FUNCAO node_creat NAO DEVE SER USADA*/

/*CRIA UMA LISTA*/
List *list_new();

/*CRIA  UM VETOR DE LISTA*/
List *list_new_vector(int n);

/*ADICIONA UM ALUNO NA LISTA*/
void list_add(List *l, int id, int distancia);

/*REMOVE O NÚMERO DA LISTA*/
int list_remove(List *l, const int identificacao);

/*DESALOCA A LISTA E TODOS OS nós DELA DA MEMORIA*/
void list_clear(List *l);

/*DESALOCA O ARRAY DE LISTA E TODOS OS ELEMENTOS DE CADA UMA*/
void list_clear_vector(List *l, int n);

/*BUSCA O ELEMENTO NA LISTA*/
int list_search_element(List *l, int identificacao);

/*RETORNA O TAMANHO DA LISTA*/
int get_total(List *l);

/*RETORNA O PRIMEIRO ELEMENTO DA LISTA*/
Node *get_first_element(struct list *l);

/*RETORNA O ULTIMO ELEMENTO DA LISTA*/
Node *get_last_element(struct list *l);

/*RETORNA UM ELEMENTO CORRENTE DA LISTA DE ACORDO COM SUA POSIÇÃO NELA*/
Node *get_current_element(struct list *l, int n);

#endif
