#include "arvore.c"

typedef struct ArvoreBinaria Abb;

/*INSERE UM NOH NA ARVORE BINARIA*/
struct ArvoreBinaria *inserirNo(struct ArvoreBinaria **nodo, int n);

/*REMOVE UM NOH DA ARVORE*/
struct ArvoreBinaria *removeNo(struct ArvoreBinaria **nodo, int n);

/*PROCURA UM NO DA ARVORE*/
struct ArvoreBinaria *procurarNo(struct ArvoreBinaria *nodo, int n);

/*VERIFICA SE O NODO ESTA VAZIO*/
int vazio(struct ArvoreBinaria *nodo);

/*RETORNA O VALOR NO NODO*/
int getValor(struct ArvoreBinaria *nodo);

/*RETORNA O NODO DA ESQUERDA*/
Abb *noEsq(struct ArvoreBinaria *node);

/*RETORNA O NODO DA DIREITA*/
Abb *noDir(struct ArvoreBinaria *node);

/*LIMPA TODA A ARVORE*/
void freeArvore(struct ArvoreBinaria *arvore);

/*INICIALIZA*/
struct ArvoreBinaria *inicializa();
