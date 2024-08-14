#include "arvoreAvl.c"

typedef struct ArvoreAvl Avl;

/*INSERE UM NOH NA ARVORE BINARIA*/
struct ArvoreAvl *inserirNo(struct ArvoreAvl **nodo, int n);
struct ArvoreAvl *inserirNoB(struct ArvoreAvl **nodo, int n);

/*REMOVE UM NOH DA ARVORE*/
struct ArvoreAvl *removeNo(struct ArvoreAvl **nodo, int n);
struct ArvoreAvl *removeNoB(struct ArvoreAvl **nodo, int n);

/*PROCURA UM NO DA ARVORE*/
struct ArvoreAvl *procurarNo(struct ArvoreAvl *nodo, int n);

/*VERIFICA SE O NODO ESTA VAZIO*/
int vazio(struct ArvoreAvl *nodo);

/*RETORNA O VALOR NO NODO*/
int getValor(struct ArvoreAvl *nodo);

/*RETORNA O NODO DA ESQUERDA*/
Avl *noEsq(struct ArvoreAvl **node);

/*RETORNA O NODO DA DIREITA*/
Avl *noDir(struct ArvoreAvl **node);

/*LIMPA TODA A ARVORE*/
void freeArvore(struct ArvoreAvl *arvore);

/*INICIALIZA*/
struct ArvoreAvl *inicializa();
