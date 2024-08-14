//!!AS VARIAVEIS QUE ARMAZENAM A MATRICULA SÃO CHAMADAS DE 'ID'

/*PRE-PROCESSAMENTO DAS FUNCOES IMPORTADAS*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
void get_file_element(List *l, FILE *fl, int n, int origem);
/*LER AQUIVO*/
void read_file(List *, char *, long int); // Lista e o NOME do arquivo
/*PRINTA TODOS OS ELEMENTOS DA LISTA*/
void list_print(List *l);
/*EXIBE A LISTA NA TELA EM SUA POSIÇÃO NA TABELA HASH*/
void printList(List *list);

void escolherCidadeInicial(List *list, int *menorCaminho);

void printListaCidades();
void printMenorCaminho(int *caminho);
int primAlgoritmo(List *list, int *menorCaminho);

int lines;
/*------------------------------------------------------------*/
// PASSO O NOME DO ARQUIVO PARA *argv
int main(int argc, char *argv[]) {
  List *list;
  clock_t start, stop;
  double diferenca;

  char arquivo[] = "entrada_100.txt";

  lines = contar_linhas(arquivo); // QUANTIDADE DE CIDADES
  int menorCaminho[lines];

  /*CRIA UM ARRAY DE LISTA*/
  list = list_new_vector(lines); // CRIO O ARRYLIST

  read_file(list, arquivo, lines); // LER ARQUIVO

  // printList(list);

  int pesoTotal = primAlgoritmo(list, menorCaminho);

  printMenorCaminho(menorCaminho);
  printf("Peso Total: %d\n", pesoTotal);

  /*DESALOCO TODO ARRAY E SEUS ALEMENTOS*/
  list_clear_vector(list, lines);
  return 0;
}

/*------------------------------------------------------------*/
void printMenorCaminho(int *caminho) {
  int i;
  printf("\n---ARVORE GERADORA MINIMA CRIADA---\n");
  for (i = 0; i < lines; i++) {
    printf("%d - ", caminho[i]);
    printCidade(caminho[i]);
    printf("\n");
  }
}

/*------------------------------------------------------------*/
void escolherCidadeInicial(List *list, int *menorCaminho) {
  int opcao;

  printf("---Escolha a cidade inicial---\n");
  printListaCidades();
  printf("Opcao: ");
  scanf("%d", &opcao);

  menorCaminho[0] = opcao;
}

/*------------------------------------------------------------*/
long int contar_linhas(char *file_name) {
  FILE *fl = fopen(file_name, "r"); // ABRIR ARQUIVO PARA LEITURA
  int i;

  fscanf(fl, "%d", &i);

  fclose(fl);
  return i; // RETORNA A QUANTIDADE DE ALUNOS
}

/*------------------------------------------------------------*/
void get_file_element(List *l, FILE *fl, int n, int origem) {
  int destino;
  float distancia;

  for (destino = 0; destino < n; destino++) {

    fscanf(fl, "%f;", &distancia);

    // ADICIONANDO A DISTANCIA DAS CIDADES ADJACENTES
    if (distancia != 0)
      list_add(&l[origem], destino, distancia);
  }
}

/*------------------------------------------------------------*/
void read_file(List *l, char *file_name,
               long int line) { // Lista e o NOME do arquivo

  FILE *fl = fopen(file_name, "r");
  int i = 0, qtCidades;
  if (!fl) {
    printf("ERRO ao abrir o Arquivo!\n");
    exit(1);
  }

  fscanf(fl, "%d", &lines);

  while (!feof(fl)) {
    get_file_element(l, fl, qtCidades, i);
    i++;
  }

  fclose(fl);

  printf("Leitura de arquivo concluida\n");
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
      vetor[i][get_id(no) - 1] = get_distancia(no);
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
void list_print(List *l) {
  Node *n = get_first_element(l);
  while (!node_empty(n)) { // PERCORRE TODOS OS ELEMENTOS DA LISTA
    printf("\n [%d, %f]", get_id(n), get_distancia(n));
    n = node_next(n);
  } // EXIBE O INDICE DO ARRAY
}

/*------------------------------------------------------------*/
void printList(List *list) {
  int i; // CONTADOR

  printf("\n\n==========LISTA=============\n");
  for (i = 0; i < lines; i++) { // ANDO PELA TABELA
    printf("\n(%d)", i + 1);
    list_print(&list[i]); // EXIBE A LISTA DO INDICE i
  }
}

/*------------------------------------------------------------*/
void printListaCidades() {
  int i;
  for (i = 0; i <= lines; i++) {
    printf("%d - ", i);
    printCidade(i);
    printf("\n");
  }
}

/*------------------------------------------------------------*/
int verificarCidadesVisitadas(int cidadeCandidata, int *cidades, int qntd) {
  int i;
  for (i = 0; i < qntd; i++) {
    if (cidades[i] == cidadeCandidata) {
      return 0;
    }
  }
  return 1;
}

/*------------------------------------------------------------*/
// RETORNA A CIDADE MAIS PERTA E
// QUE NAO FOI VISITADA AINDA DO NO
int buscarMenorCaminho(Node *no, int *cidades, int qntd,
                       float *distPercorrida) {
  int cidadeProxima;
  *distPercorrida = 9999;

  while (!node_empty(no)) {
    if (get_distancia(no) < *distPercorrida) {
      if (verificarCidadesVisitadas(get_id(no), cidades,
                                    qntd)) { // CIDADE NAO FOI SELECIONADA
        cidadeProxima = get_id(no);
        *distPercorrida = get_distancia(no);
      }
    }
    no = node_next(no);
  }
  return cidadeProxima;
}

/*------------------------------------------------------------*/
int buscarCidadeProxima(List *list, int *cidades, int qntd,
                        float *distPercorrida) {
  int i;
  float distCandidata, proximaCidade;
  int menorDistancia = 9999;

  for (i = 0; i < qntd; i++) {
    int atual = cidades[i];
    int cidadeCandidata =
        buscarMenorCaminho(list[atual].first, cidades, qntd, &distCandidata);

    if (distCandidata < menorDistancia) {
      proximaCidade = cidadeCandidata;
      *distPercorrida = distCandidata;
      menorDistancia = distCandidata;
    }
  }
  return proximaCidade;
}

/*------------------------------------------------------------*/
int primAlgoritmo(List *list, int *menorCaminho) {
  clock_t start, stop;

  escolherCidadeInicial(list, menorCaminho);
  int cidsPercorridas = 1;
  float distanciaPercorrida, distanciaTotal = 0;

  start = clock();

  for (; cidsPercorridas < lines; cidsPercorridas++) {
    int cidade = buscarCidadeProxima(list, menorCaminho, cidsPercorridas,
                                     &distanciaPercorrida);
    menorCaminho[cidsPercorridas] = cidade; // SALVO A CIDADE COM VISITADA
    distanciaTotal += distanciaPercorrida;  // SOMA DO PESO
  }

  stop = clock();

  // PRINT DO TEMPO DE EXECUCAO
  printf("\n\n-----TEMPO DE EXECUCAO: %lf\n\n",
         ((double)(stop - start) / CLOCKS_PER_SEC));

  return distanciaTotal;
}
