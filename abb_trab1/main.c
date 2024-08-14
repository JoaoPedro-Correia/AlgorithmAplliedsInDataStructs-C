#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

/*EXIBE O MENU NA TELA*/
int menu(void);
/*LIMPA A TELA*/
void clearWindow(void);
/*LIMPA O BUFFER DO TECLADO*/
void clear_buff(void);

/*INSERE UM VALOR NA ARVORE*/
void inserir(Abb **arvore);
/*REMOVE UM VALOR DA ARVORE*/
void remover(Abb **raiz);

/*ESCOLHE A FORMA DE EXIBICAO DA ARVORE NA TELA*/
void printLista(Abb *arvore);
/*EXIBE A ARVORE EM PRE-ORDEM*/
void printPreOrdem(Abb *arvore);
/*EXIBE A ARVORE EM EM ORDEM*/
void printOrdem(Abb *arvore);
/*EXIBE A ARVORE EM POS-ORDEM*/
void printPosOrdem(Abb *arvore);

/*BUSCA UM ELEMENTO DA ARVORE*/
void buscar(Abb *arvore);

/*=======================================================*/
int main() {
  Abb *raiz;
  clearWindow();
  raiz = inicializa();

  int opcao;

  do {
    opcao = menu();
    switch (opcao) {
    case 1:
      inserir(&raiz);
      clear_buff();
      getchar();
      break;
    case 2:
      remover(&raiz);
      break;
    case 3:
      printLista(raiz);
      clear_buff();
      getchar();
      break;
    case 4:
      buscar(raiz);
      clear_buff();
      getchar();
      break;
    }
    clearWindow();
  } while (opcao != 0);

  freeArvore(raiz);
}

/*=======================================================*/
void clearWindow() {
#ifdef __linux__
  system("clear");
#else
  system("cls");
#endif
}

/*=======================================================*/
void clear_buff() {
  int c;
  while ((c = getchar()) != '\n') {
  }
}

/*=======================================================*/
int menu() {
  int option;
  printf("1 - Inserir\n");
  printf("2 - Remover\n");
  printf("3 - Printar arvore\n");
  printf("4 - Buscas elemento\n");
  printf("0 - Sair\n");

  printf("\nOption: ");
  scanf("%d", &option);

  return option;
}

/*=======================================================*/
void printLista(Abb *arvore) {
  int n;
  printf("\n\n=====FORMA DE IMPRIMIR=====\n");
  printf("1 - Pre-ordem\n");
  printf("2 - Em ordem\n");
  printf("3 - Pos-ordem\n");
  do {
    printf("\nOpcao: ");
    scanf("%d", &n);
  } while (!(n > 0 && n < 4));

  switch (n) {
  case 1:
    printPreOrdem(arvore);
    break;
  case 2:
    printOrdem(arvore);
    break;
  case 3:
    printPosOrdem(arvore);
    break;
  }
}

/*=======================================================*/
void inserir(Abb **arvore) {
  int num;
  printf("\nInserir um valor: ");
  scanf("%d", &num);

  inserirNo(&(*arvore), num);
}

/*=======================================================*/
void remover(Abb **arvore) {
  int num;
  printf("\nRemover um valor: ");
  scanf("%d", &num);

  removeNo(&(*arvore), num);
}

/*=======================================================*/
void printPreOrdem(Abb *arvore) {
  if (!vazio(arvore)) {
    printf("%d ", getValor(arvore));
    printPreOrdem(noEsq(arvore));
    printPreOrdem(noDir(arvore));
  }
}

/*=======================================================*/
void printPosOrdem(Abb *arvore) {
  if (!vazio(arvore)) {
    printPosOrdem(noEsq(arvore));
    printPosOrdem(noDir(arvore));
    printf("%d ", getValor(arvore));
  }
}

/*=======================================================*/
void printOrdem(Abb *arvore) {
  if (!vazio(arvore)) {
    printOrdem(noEsq(arvore));
    printf("%d ", getValor(arvore));
    printOrdem(noDir(arvore));
  }
}

/*=======================================================*/
void buscar(Abb *arvore) {
  int num;
  printf("\nBuscar um valor: ");
  scanf("%d", &num);

  Abb *nodo = procurarNo(arvore, num);
  if (vazio(nodo)) {
    printf("Valor não esxiste na arvore\n");
  } else {
    printf("Valor foi encontrado!!!\n");
  }
}
