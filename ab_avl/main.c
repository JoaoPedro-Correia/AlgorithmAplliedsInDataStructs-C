#include "arvoreAvl.h"
#include <stdio.h>
#include <stdlib.h>

#define espaco 5

long int contarLinhas(char *arquivo);
void inserirArquivo(char *arq, Avl **nodo, long int linhas);
long int lerArquivo(FILE *fl);

/*EXIBE O MENU NA TELA*/
int menu(void);
/*LIMPA A TELA*/
void clearWindow(void);
/*LIMPA O BUFFER DO TECLADO*/
void clear_buff(void);

/*INSERE UM VALOR NA ARVORE*/
void inserir(Avl **arvore);
/*REMOVE UM VALOR DA ARVORE*/
void remover(Avl **raiz);

/*ESCOLHE A FORMA DE EXIBICAO DA ARVORE NA TELA*/
void printLista(Avl *arvore);
/*EXIBE A ARVORE EM PRE-ORDEM*/
void printPreOrdem(Avl *arvore);
/*EXIBE A ARVORE EM EM ORDEM*/
void printOrdem(Avl *arvore);
/*EXIBE A ARVORE EM POS-ORDEM*/
void printPosOrdem(Avl *arvore);

/*BUSCA UM ELEMENTO DA ARVORE*/
void buscar(Avl *arvore);

void desenha_arvore_horiz(Avl *arvore, int depth, char *path, int direita);
void draw_arvore_hor(Avl *arvore);

/*=======================================================*/
int main(int argc, char *argv[]) {
  Avl *raiz;
  clearWindow();
  raiz = inicializa();

  if (argv[1] != NULL) {
    long int linhas = contarLinhas(argv[1]);
    inserirArquivo(argv[1], &raiz, linhas);
  }

  int opcao;

  do {
    opcao = menu();
    switch (opcao) {
    case 1:
      inserir(&raiz);
      break;
    case 2:
      remover(&raiz);
      break;
    case 3:
      draw_arvore_hor(raiz);
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
long int lerArquivo(FILE *fl) {
  long int num;
  fscanf(fl, "%ld", &num);

  return num;
}

/*=======================================================*/
void inserirArquivo(char *arq, Avl **nodo, long int linhas) {
  FILE *fl;
  long int val;
  int cont = 0;

  fl = fopen(arq, "r");

  printf("Lendo arquivo...\n");

  while (cont < linhas) {
    val = lerArquivo(fl);
    inserirNo(nodo, val);
    cont++;
  }

  fclose(fl);
}

/*=======================================================*/
long int contarLinhas(char *arquivo) {
  FILE *fl = fopen(arquivo, "r"); // ABRIR ARQUIVO PARA LEITURA
  char aux[100];
  long int i = 0; // VAI ARMAZENAR A QUANTIDADE DE LINHAS

  if (!fl) { // CASO NAO CONSIGA ABRI-LO
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  while (!feof(fl)) {
    fgets(aux, 100, fl);
    i++; // CONTA AS LINHAS
  }
  --i;

  fclose(fl);
  return (i); // RETORNA A QUANTIDADE DE ALUNOS
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
void printLista(Avl *arvore) {
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
void inserir(Avl **arvore) {
  int num;
  printf("\nInserir um valor: ");
  scanf("%d", &num);

  inserirNo(arvore, num);
}

/*=======================================================*/
void remover(Avl **arvore) {
  int num;
  printf("\nRemover um valor: ");
  scanf("%d", &num);

  removeNo(&(*arvore), num);
}

/*=======================================================*/
void printPreOrdem(Avl *arvore) {
  if (!vazio(arvore)) {
    printf("%d ", getValor(arvore));
    printPreOrdem(noEsq(&arvore));
    printPreOrdem(noDir(&arvore));
  }
}

/*=======================================================*/
void printPosOrdem(Avl *arvore) {
  if (!vazio(arvore)) {
    printPosOrdem(noEsq(&arvore));
    printPosOrdem(noDir(&arvore));
    printf("%d ", getValor(arvore));
  }
}

/*=======================================================*/
void printOrdem(Avl *arvore) {
  if (!vazio(arvore)) {
    printOrdem(noEsq(&arvore));
    printf("%d ", getValor(arvore));
    printOrdem(noDir(&arvore));
  }
}

/*=======================================================*/
void buscar(Avl *arvore) {
  int num;
  printf("\nBuscar um valor: ");
  scanf("%d", &num);

  Avl *nodo = procurarNo(arvore, num);
  if (vazio(nodo)) {
    printf("Valor não esxiste na arvore\n");
  } else {
    printf("Valor foi encontrado!!!\n");
  }
}

/*=======================================================*/
void draw_arvore_hor(Avl *arvore) {
  // should check if we don't exceed this somehow..
  char path[255] = {};

  // initial depth is 0
  desenha_arvore_horiz(arvore, 0, path, 0);
}

/*=======================================================*/
void desenha_arvore_horiz(Avl *arvore, int depth, char *path, int direita) {
  // stopping condition
  if (arvore == NULL)
    return;

  // increase spacing
  depth++;

  // start with direita no
  desenha_arvore_horiz(arvore->dir, depth, path, 1);

  // set | draw map
  path[depth - 2] = 0;

  if (direita)
    path[depth - 2] = 1;

  if (arvore->esq)
    path[depth - 1] = 1;

  // print root after spacing
  printf("\n");

  for (int i = 0; i < depth - 1; i++) {
    if (i == depth - 2)
      printf("*");
    else if (path[i])
      printf("|");
    else
      printf(" ");

    for (int j = 1; j < espaco; j++)
      if (i < depth - 2)
        printf(" ");
      else
        printf("-");
  }

  printf("%d-%d\n", getValor(arvore), getAltura(arvore));

  // vertical espacors below
  for (int i = 0; i < depth; i++) {
    if (path[i])
      printf("|");
    else
      printf(" ");

    for (int j = 1; j < espaco; j++)
      printf(" ");
  }

  // go to esquerda no
  desenha_arvore_horiz(arvore->esq, depth, path, 0);
}
