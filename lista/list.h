/*CHAMO O ARQUIVO list.c*/
#include "list.c"

typedef struct list List;

/*COLOCO A ASSINATURA DAS FUNÇÕES QUE MANIPULAM A STRUCT list
 * A FUNCAO node_creat NAO DEVE SER USADA*/

/*CRIA UMA LISTA*/
List *list_new();

/*ADICIONA UM NUMERO NA LISTA NA ORDEM CRESCENTE*/
void list_add(List *l, int num);

/*REMOVE O NÚMERO DA LISTA*/
int list_remove(List *l, int num);

/*DESALOCA A LISTA E TODOS OS nós DELA DA MEMORIA*/
void list_clear(List *l);

/*BUSCO O NUMERO A PARTIR DO SUA POSICAO NA FILA*/
int list_search(List *l, int ind);

/*BUSCA O ELEMENTO NA LISTA*/
int list_search_element(struct list *l, int value);

/*RETORNA O TAMANHO DA LISTA*/
int get_total(List *l);
