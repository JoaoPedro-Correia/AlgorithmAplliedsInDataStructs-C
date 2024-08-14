#include "node.c"

typedef struct node Node;

/*ALOCA NA MEMORIA*/
Node *node_creat(int nome, int matricula);

/*RETORNA O PRÓXIMOS ELEMENTO*/
Node *node_next(struct node *n);

/*RETORNO O CAMPO NOME*/
int get_distancia(Node *n);

/*ADICIONA UM VALOR NO CAMPO NOME*/
void set_distancia(Node *n, int name);

/*RETORNA O CAMPO DA MATRICULA*/
int get_id(Node *n);

/*ADICIONA UM VALOR NO ID/MATRICULA*/
void set_id(Node *n, int id);

/*DESOLACA NA MEMORIA*/
void node_free(struct node *n);

/*VERICICA DE O ELEMENTO ESTÁ VAZIO*/
int node_empty(struct node *n);
