#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>

/*CONSTANTES DE TAMANHO
 * DOS ARRAY DE CHAR DOS NOMES E MATRICULA*/
#define NOME 60
#define MATRICULA 15

/*EXIBE O MENU NA TELA*/
int menu(void);
/*LIMPA A TELA*/
void clearWindow(void);
/*LIMPA O BUFFER DO TECLADO*/
void clear_buff(void);

long int contarEstudantes(char *file_name);
void lerArquivo(Abb **raiz, char *file_name,
                long int linhas); // Lista e o NOME do arquivo
void lerAluno(Abb **raiz, FILE *fl);
void remove_line_break(char *n);

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

void salvarOrdem(Abb *arvore, FILE *fl);
void salvar(Abb *raiz, char *file_name);

/*=======================================================*/
int main(int argc, char *argv[]) {
  Abb *raiz;
  clearWindow();
  raiz = inicializa();

  if (argv[1] == NULL) { // USUARIO NAO PASSOU O ARQUIVO
    printf("ERRO Arquivo não encontrado!");
    printf("\nForma de execução esperado 'arquivo.out local_do_arquivo.txt'\n");
    return 0;
  }

  long int linhas = contarEstudantes(argv[1]); // QUANTIDADE DE ALUNOS
  lerArquivo(&raiz, argv[1], linhas);          // LER ARQUIVO

  int opcao;

  do {
    /*EXIBE O MENU NA TELA E RETORNA A OOPCAO ESCOLHIDA*/
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
    case 5:
      salvar(raiz, argv[1]);
      clear_buff();
      getchar();
      break;
    }
    clearWindow();
  } while (opcao != 0);

  freeArvore(raiz);
}

/*=======================================================*/
long int contarEstudantes(char *file_name) {
  FILE *fl = fopen(file_name, "r"); // ABRIR ARQUIVO PARA LEITURA
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
  return (i / 2); // RETORNA A QUANTIDADE DE ALUNOS
}

/*=======================================================*/
void remove_line_break(char *n) {
  int len;
  len = strlen(n);
  if (n[len - 1] == '\n')
    n[--len] = 0; // remove '\n' e actualiza len
}

/*=======================================================*/
void lerAluno(Abb **raiz, FILE *fl) {
  // CRIO UM ARRAY DE CHAR PARA O NOME
  // CRIO UM ARRAY DE CHAR PARA MATRICULA
  char *student_name = (char *)malloc(NOME * sizeof(char));
  char *id_student = (char *)malloc(MATRICULA * sizeof(char));

  // ARMAZENO A MATRICULA
  fgets(id_student, MATRICULA, fl);
  remove_line_break(id_student);

  // ARMAZENO O NOME
  fgets(student_name, NOME, fl);
  remove_line_break(student_name);

  // ADICIONO NA LISTA O NOME E A MATRICULA
  inserirNo(raiz, id_student, student_name);
}

/*=======================================================*/
void lerArquivo(Abb **raiz, char *file_name,
                long int linhas) { // Lista e o NOME do arquivo

  FILE *fl = fopen(file_name, "r");
  int i = 0;
  if (!fl) {
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  while (i < linhas) {
    lerAluno(raiz, fl);
    i++;
  }

  fclose(fl);

  printf("Leitura de arquivo concluida\n");
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
  printf("5 - Salvar base de dados\n");
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
  char *nome = (char *)malloc(NOME * sizeof(char));
  char *matricula = (char *)malloc(MATRICULA * sizeof(char));

  clear_buff();
  printf("\nInserir um nome: ");
  scanf("%[^\n]s", nome);

  clear_buff();
  printf("\nInserir a matrícula: ");
  scanf("%[^\n]s", matricula);

  inserirNo(&(*arvore), matricula, nome);
}

/*=======================================================*/
void remover(Abb **arvore) {
  char matricula[MATRICULA];

  clear_buff();
  printf("\nInserir a matrícula: ");
  scanf("%[^\n]s", matricula);
  printf("\n%s", matricula);

  removeNo(&(*arvore), matricula);
}

/*=======================================================*/
void printPreOrdem(Abb *arvore) {
  if (!vazio(arvore)) {
    printf("%s ", getMatricula(arvore));
    printf("%s\n", getNome(arvore));
    printPreOrdem(noEsq(arvore));
    printPreOrdem(noDir(arvore));
  }
}

/*=======================================================*/
void printPosOrdem(Abb *arvore) {
  if (!vazio(arvore)) {
    printPosOrdem(noEsq(arvore));
    printPosOrdem(noDir(arvore));
    printf("%s ", getMatricula(arvore));
    printf("%s\n", getNome(arvore));
  }
}

/*=======================================================*/
void printOrdem(Abb *arvore) {
  if (!vazio(arvore)) {
    printOrdem(noEsq(arvore));
    printf("%s ", getMatricula(arvore));
    printf("%s\n", getNome(arvore));
    printOrdem(noDir(arvore));
  }
}

/*=======================================================*/
void buscar(Abb *arvore) {
  char matricula[MATRICULA];

  clear_buff();
  printf("\nInserir a matrícula: ");
  scanf("%[^\n]s", matricula);

  Abb *nodo = procurarNo(arvore, matricula);
  if (vazio(nodo)) {
    printf("Valor não esxiste na arvore\n");
  } else {
    printf("Valor foi encontrado!!!\n");
  }
}

/*=======================================================*/
void salvarOrdem(Abb *arvore, FILE *fl) {
  if (!vazio(arvore)) {
    salvarOrdem(noEsq(arvore), fl);
    fprintf(fl, "%s\n", getMatricula(arvore)); // MATRICULA
    fprintf(fl, "%s\n", getNome(arvore));      // NOME
    salvarOrdem(noDir(arvore), fl);
  }
}

/*=======================================================*/
void salvar(Abb *raiz, char *file_name) {
  FILE *fl = fopen(file_name, "w+");

  if (!fl) {
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  salvarOrdem(raiz, fl);

  fclose(fl);

  printf("\nCopiado com sucesso!");
}
