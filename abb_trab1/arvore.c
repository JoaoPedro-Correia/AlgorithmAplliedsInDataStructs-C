#include <stdio.h>
#include <stdlib.h>

// ESTRUTUTURA DA ARVORE BINARIA
struct ArvoreBinaria {
  int valor;
  struct ArvoreBinaria *esq;
  struct ArvoreBinaria *dir;
};

//======================= ARVORE BINARIA ==============================
struct ArvoreBinaria *criarNo(int n) {
  struct ArvoreBinaria *novo =
      (struct ArvoreBinaria *)malloc(sizeof(struct ArvoreBinaria));

  novo->dir = NULL;
  novo->esq = NULL;
  novo->valor = n;

  return novo;
}

//=============================================================
struct ArvoreBinaria *inicializa() { return NULL; }

//=============================================================
struct ArvoreBinaria *inserirNo(struct ArvoreBinaria **nodo, int n) {
  if ((*nodo) == NULL)
    (*nodo) = criarNo(n);
  else if (n < (*nodo)->valor)
    (*nodo)->esq = inserirNo(&(*nodo)->esq, n);
  else
    (*nodo)->dir = inserirNo(&(*nodo)->dir, n);

  return (*nodo);
}

//=============================================================
struct ArvoreBinaria *removeNo(struct ArvoreBinaria **nodo, int n) {
  if (!(*nodo)) // SE O NODO ESTIVER VAZIO
    return NULL;
  else if (n < (*nodo)->valor)
    (*nodo)->esq = removeNo(&(*nodo)->esq, n);
  else if (n > (*nodo)->valor)
    (*nodo)->dir = removeNo(&(*nodo)->dir, n);
  else {
    if (!((*nodo)->esq) && !((*nodo)->dir)) {
      free(*nodo);
      (*nodo) = NULL;
    } else if (!((*nodo)->esq)) {
      struct ArvoreBinaria *aux = (*nodo);
      *nodo = (*nodo)->dir;
      free(aux);
    } else if (!((*nodo)->dir)) {
      struct ArvoreBinaria *aux = *nodo;
      *nodo = (*nodo)->esq;
      free(aux);
    } else {
      struct ArvoreBinaria *aux = (*nodo)->esq;
      while (aux->dir)
        aux = aux->dir;

      (*nodo)->valor = aux->valor;
      aux->valor = n;

      (*nodo)->esq = removeNo(&(*nodo)->esq, n);
    }
  }
  return *nodo;
}

//=============================================================
struct ArvoreBinaria *procurarNo(struct ArvoreBinaria *nodo, int n) {
  if (nodo == NULL)
    return NULL;
  else if (n < (nodo)->valor)
    return procurarNo((nodo)->esq, n);
  else if (n > (nodo)->valor)
    return procurarNo((nodo)->dir, n);
  else
    return nodo;
}

//=============================================================
int vazio(struct ArvoreBinaria *nodo) { return nodo == NULL; }

//=============================================================
int getValor(struct ArvoreBinaria *nodo) { return nodo->valor; }

//=============================================================
struct ArvoreBinaria *noDir(struct ArvoreBinaria *nodo) { return nodo->dir; }

//=============================================================
struct ArvoreBinaria *noEsq(struct ArvoreBinaria *nodo) { return nodo->esq; }

//=============================================================
void freeArvore(struct ArvoreBinaria *arvore) {
  if (!vazio(arvore)) {
    freeArvore(noEsq(arvore));
    freeArvore(noDir(arvore));
    free(arvore);
  }
}
