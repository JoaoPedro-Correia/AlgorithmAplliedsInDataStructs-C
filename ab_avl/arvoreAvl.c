#include <stdio.h>
#include <stdlib.h>

// ESTRUTUTURA DA ARVORE BINARIA
struct ArvoreAvl {
  int valor;
  struct ArvoreAvl *esq;
  struct ArvoreAvl *dir;
  int altura;
};

//=============================================================
struct ArvoreAvl *inicializa() { return NULL; }

//=============================================================
int vazio(struct ArvoreAvl *nodo) { return nodo == NULL; }

//=============================================================
int getValor(struct ArvoreAvl *nodo) { return nodo->valor; }

//=============================================================
struct ArvoreAvl *noDir(struct ArvoreAvl **nodo) { return (*nodo)->dir; }

//=============================================================
struct ArvoreAvl *noEsq(struct ArvoreAvl **nodo) { return (*nodo)->esq; }

//======================= ARVORE BINARIA ==============================
struct ArvoreAvl *criarNo(int n) {
  struct ArvoreAvl *novo = (struct ArvoreAvl *)malloc(sizeof(struct ArvoreAvl));

  novo->dir = NULL;
  novo->esq = NULL;
  novo->valor = n;
  novo->altura = 0;

  return novo;
}

//=============================================================
int getAltura(struct ArvoreAvl *nodo) {
  if (nodo == NULL) {
    return 0;
  }
  return nodo->altura;
}

//=============================================================
int max(int x, int y) { return (x > y) ? x : y; }

//=============================================================
struct ArvoreAvl *rodar_E(struct ArvoreAvl **nodo) {
  struct ArvoreAvl *x = noDir(nodo);
  (*nodo)->dir = noEsq(&x);
  x->esq = (*nodo);

  (*nodo)->altura = max(getAltura(noEsq(nodo)), getAltura(noDir(nodo))) + 1;
  x->altura = max(getAltura(noEsq(&x)), getAltura(noDir(&x))) + 1;

  (*nodo) = x;
  return (*nodo);
}

//=============================================================
struct ArvoreAvl *rodar_D(struct ArvoreAvl **nodo) {
  struct ArvoreAvl *x = noEsq(nodo);
  (*nodo)->esq = noDir(&x);
  x->dir = (*nodo);

  (*nodo)->altura = max(getAltura(noEsq(nodo)), getAltura(noDir(nodo))) + 1;
  x->altura = max(getAltura(noEsq(&x)), getAltura(noDir(&x))) + 1;

  (*nodo) = x;
  return (*nodo);
}

//=============================================================
int fator_balanceamento(struct ArvoreAvl *nodo) {
  if (nodo == NULL) {
    return 0;
  }
  return getAltura(noDir(&nodo)) - getAltura(noEsq(&nodo));
}

//=============================================================
struct ArvoreAvl *balancear(struct ArvoreAvl **nodo) {
  /*PEGA O FATOR DE BALANCIAMENTO*/
  int balanceamento = fator_balanceamento(*nodo);
  int balanceamento_dir = fator_balanceamento(noDir(nodo));
  int balanceamento_esq = fator_balanceamento(noEsq(nodo));

  /*ROTACIONAR ARVORE*/
  /*ARVORE DESBALANCEADA - DIREITA*/
  if (balanceamento > 1 && balanceamento_dir > 0) {
    return rodar_E(nodo);
  }
  /*ARVORE DESBALANCEADA - ESQUERDA*/
  else if (balanceamento < -1 && balanceamento_esq < 0) {
    return rodar_D(nodo);
  }
  /*ARVORE DESBALANCEADA - DIREITA ESQUERDA*/
  else if (balanceamento > 1 && balanceamento_dir < 0) {
    (*nodo)->dir = rodar_D(&(*nodo)->dir);
    return rodar_E(nodo);
  }
  /*ARVORE DESBALANCEADA - ESQUERDA DIREITA*/
  else if (balanceamento < -1 && balanceamento_esq > 0) {
    (*nodo)->esq = rodar_E(&(*nodo)->esq);
    return rodar_D(nodo);
  }
  return (*nodo);
}

//=============================================================
struct ArvoreAvl *inserirNo(struct ArvoreAvl **nodo, int n) {
  if ((*nodo) == NULL)
    (*nodo) = criarNo(n);
  else if (n < (*nodo)->valor)
    (*nodo)->esq = inserirNo(&(*nodo)->esq, n);
  else
    (*nodo)->dir = inserirNo(&(*nodo)->dir, n);

  /*PEGA A ALTURA DA ARVORE*/
  (*nodo)->altura = 1 + max(getAltura(noEsq(nodo)), getAltura(noDir(nodo)));

  return balancear(nodo);
}

//=============================================================
struct ArvoreAvl *inserirNoB(struct ArvoreAvl **nodo, int n) {
  if ((*nodo) == NULL)
    (*nodo) = criarNo(n);
  else if (n < (*nodo)->valor)
    (*nodo)->esq = inserirNo(&(*nodo)->esq, n);
  else
    (*nodo)->dir = inserirNo(&(*nodo)->dir, n);

  return (*nodo);
}

//=============================================================
struct ArvoreAvl *removeNo(struct ArvoreAvl **nodo, int n) {
  if (!(*nodo)) // SE O NODO ESTIVER VAZIO
    return NULL;
  else if (n < (*nodo)->valor) {
    (*nodo)->esq = removeNo(&(*nodo)->esq, n);
    (*nodo)->altura = 1 + max(getAltura(noEsq(nodo)), getAltura(noDir(nodo)));
    return balancear(nodo);
  } else if (n > (*nodo)->valor) {
    (*nodo)->dir = removeNo(&(*nodo)->dir, n);
    (*nodo)->altura = 1 + max(getAltura(noEsq(nodo)), getAltura(noDir(nodo)));
    return balancear(nodo);
  } else {
    if (!((*nodo)->esq) && !((*nodo)->dir)) {
      free(*nodo);
      (*nodo) = NULL;
    } else if (!((*nodo)->esq)) {
      struct ArvoreAvl *aux = (*nodo);
      *nodo = (*nodo)->dir;
      free(aux);
    } else if (!((*nodo)->dir)) {
      struct ArvoreAvl *aux = *nodo;
      *nodo = (*nodo)->esq;
      free(aux);
    } else {
      struct ArvoreAvl *aux = (*nodo)->esq;
      while (aux->dir)
        aux = aux->dir;

      (*nodo)->valor = aux->valor;
      aux->valor = n;

      (*nodo)->esq = removeNo(&(*nodo)->esq, n);
      (*nodo)->altura = 1 + max(getAltura(noEsq(nodo)), getAltura(noDir(nodo)));
      return balancear(nodo);
    }
  }
  return *nodo;
}

//=============================================================
struct ArvoreAvl *removeNoB(struct ArvoreAvl **nodo, int n) {
  if (!(*nodo)) // SE O NODO ESTIVER VAZIO
    return NULL;
  else if (n < (*nodo)->valor) {
    (*nodo)->esq = removeNo(&(*nodo)->esq, n);
    (*nodo)->altura = 1 + max(getAltura(noEsq(nodo)), getAltura(noDir(nodo)));
  } else if (n > (*nodo)->valor) {
    (*nodo)->dir = removeNo(&(*nodo)->dir, n);
    (*nodo)->altura = 1 + max(getAltura(noEsq(nodo)), getAltura(noDir(nodo)));
  } else {
    if (!((*nodo)->esq) && !((*nodo)->dir)) {
      free(*nodo);
      (*nodo) = NULL;
    } else if (!((*nodo)->esq)) {
      struct ArvoreAvl *aux = (*nodo);
      *nodo = (*nodo)->dir;
      free(aux);
    } else if (!((*nodo)->dir)) {
      struct ArvoreAvl *aux = *nodo;
      *nodo = (*nodo)->esq;
      free(aux);
    } else {
      struct ArvoreAvl *aux = (*nodo)->esq;
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
struct ArvoreAvl *procurarNo(struct ArvoreAvl *nodo, int n) {
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
void freeArvore(struct ArvoreAvl *arvore) {
  if (!vazio(arvore)) {
    freeArvore(noEsq(&arvore));
    freeArvore(noDir(&arvore));
    free(arvore);
  }
}
