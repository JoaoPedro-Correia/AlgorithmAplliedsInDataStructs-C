//!!AS VARIAVEIS QUE ARMAZENAM A MATRICULA SÃO CHAMADAS DE 'ID'

/*PRE-PROCESSAMENTO DAS FUNCOES IMPORTADAS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*CHAMO A BIBLIOTECA DA LISTA*/
/*list.h TEM DUAS ESTRUTURAS,
 * NODE E LIST*/
#include "cidades.h"
#include "list.h"
#include "node.c"

long int contar_linhas(char *file_name);
/*REMOVE A QUEBRA DE LINHA DO ARRAY DE CHAR*/
void remove_line_break(char *n);
/*ADICIONO O ESTUDANTE DO ARQUIVO NA LISTA*/
void get_file_element(List *l, FILE *fl);
/*LER AQUIVO*/
void read_file(List *, char *, long int); // Lista e o NOME do arquivo
/*LIMPO O TERMINAL*/
void clear_window(void);
/*LIMPO O BUFFER DO COMPUTADOR*/
void clear_buff(void);
/*PRINTA TODOS OS ELEMENTOS DA LISTA*/
void list_print(List *l);
/*EXIBE A LISTA NA TELA EM SUA POSIÇÃO NA TABELA HASH*/
void printList(List *);

long int lines;
/*------------------------------------------------------------*/
// PASSO O NOME DO ARQUIVO PARA *argv
int main(int argc, char *argv[]) {
  int option;
  List *list;

  if (argv[1] == NULL) { // USUARIO NAO PASSOU O ARQUIVO
    printf("ERRO Arquivo não encontrado!");
    printf("\nForma de execução esperado 'arquivo.out local_do_arquivo.txt'\n");
    return 0;
  }

  lines = contar_linhas(argv[1]); // QUANTIDADE DE CIDADES

  /*CRIA UM ARRAY DE LISTA*/
  list = list_new_vector(lines); // CRIO O ARRYLIST

  read_file(list, argv[1], lines); // LER ARQUIVO

  printList(list);

  /*DESALOCO TODO ARRAY E SEUS ALEMENTOS*/
  list_clear_vector(list, lines);
  return 0;
}

/*------------------------------------------------------------*/
// PROCURA O NUMERO PRIMO MAIS PROXIMO AO VALOR
long int next_prime_number(long int e) {
  int i = 3;
  while (i <= e / 2) {
    /* SE e E DIVISIVEL POR i, ENTAO e NAO É PRIMO
     * SOMO MAIS 1 NO e E i = 2*/
    if (e % i == 0) {
      e++;
      i = 3;
    }
    i++;
  }

  return e;
}

/*------------------------------------------------------------*/
long int contar_linhas(char *file_name) {
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
  return i; // RETORNA A QUANTIDADE DE ALUNOS
}

/*------------------------------------------------------------*/
void remove_line_break(char *n) {
  int len;
  len = strlen(n);
  if (n[len - 1] == '\n')
    n[--len] = 0; // remove '\n' e actualiza len
}

/*------------------------------------------------------------*/
void get_file_element(List *l, FILE *fl) {
  int origem, destino, distancia;

  // ARMAZENO A MATRICULA
  fscanf(fl, "%d", &origem);
  // remove_line_break(id_student);

  fscanf(fl, "%d", &destino);

  // ARMAZENO O NOME
  fscanf(fl, "%d", &distancia);
  // remove_line_break(student_name);

  // ADICIONO NA LISTA O NOME E A MATRICULA
  list_add(&l[origem - 1], destino, distancia);
}

/*------------------------------------------------------------*/
void read_file(List *l, char *file_name,
               long int line) { // Lista e o NOME do arquivo

  FILE *fl = fopen(file_name, "r");
  int i = 0;
  if (!fl) {
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  while (!feof(fl)) {
    get_file_element(l, fl);
    i++;
  }

  fclose(fl);

  printf("Leitura de arquivo concluida\n");
}

/*------------------------------------------------------------*/
void clear_buff() {
  int c;
  while ((c = getchar()) != '\n') {
  }
}

/*------------------------------------------------------------*/
int **initVetor() {
  int i, e;
  int **vetor;

  vetor = (int **)malloc(lines * sizeof(int *));
  for (i = 0; i < lines; i++) {
    vetor[i] = (int *)malloc(lines * sizeof(int));
  }

  for (i = 0; i < lines; i++) {
    for (e = 0; e < lines; e++) {
      vetor[i][e] = 0;
    }
  }

  return vetor;
}

/*------------------------------------------------------------*/
void listForVetor(List *list, int **vetor) {
  int i;

  for (i = 0; i < lines; i++) {
    Node *no = get_first_element(&list[i]);
    while (!node_empty(no)) {
      vetor[i][get_id(no)] = get_distancia(no);
      no = node_next(no);
    }
  }
}

/*------------------------------------------------------------*/
void freeVetor(int **vetor) {
  int i;

  for (i = 0; i < lines; i++) {
    free(vetor[i]);
  }
  free(vetor);
}

/*------------------------------------------------------------*/
void printList(List *list) {
  int i, e; // CONTADOR
  int **vetor;

  vetor = initVetor();

  listForVetor(list, vetor);

  printf("\n\n====================Vetor=========================\n");
  for (i = 0; i < lines; i++) { // ANDO PELA TABELA
    for (e = 0; e < lines; e++) {
      printf("%d\t\b", vetor[i][e]);
    }
    printf("\n");
  }

  freeVetor(vetor);
}
