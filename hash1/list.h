/*CHAMO O ARQUIVO list.c*/
#include "list.c"

typedef struct list List;

/*COLOCO A ASSINATURA DAS FUNÇÕES QUE MANIPULAM A STRUCT list
 * A FUNCAO node_creat NAO DEVE SER USADA*/

/*CRIA UMA LISTA*/
List *list_new();

/*CRIA  UM VETOR DE LISTA*/
List *list_new_vector(int n);

/*ADICIONA UM NUMERO NA LISTA NA ORDEM CRESCENTE*/
void list_add(List *l, int num);

/*REMOVE O NÚMERO DA LISTA*/
int list_remove(List *l, int num);

/*DESALOCA A LISTA E TODOS OS nós DELA DA MEMORIA*/
void list_clear(List *l);

/*DESALOCA O ARRAY DE LISTA E TODOS OS ELEMENTOS DE CADA UMA*/
void list_clear_vector(List *l, int n);

/*EXIBE NA TELA TODOS OS ELEMENTOS DA LISTA*/
void list_print(List *l);

/*BUSCA O ELEMENTO NA LISTA*/
int list_search_element(List *l, int value);

/*RETORNA O TAMANHO DA LISTA*/
int get_total(List *l);
