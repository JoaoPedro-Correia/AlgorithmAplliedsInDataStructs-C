/*ALUNO:
 * JOAO PEDRO CORREIA*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VAZIO -1

/*=======================================================*/
void clear_window(void);
int escolherArquivo(void);
int escolhaTamnhoHash(void);
int escolhaHashDuplo(void);
long int contarLinhas(char *arquivo);

void primoProximo(long int *e);
void primoAnterior(long int *e);
int verificarPrimo(long int e);
long int numeroPrimo(long int e, void mudarValor(long int *));

void initTabela(long int *t, long int tam);
long int *criarTabelaHash(long int);
void inserirArquivo(long int *t, char *arq,
                    void hashDuplo(long int *, long int));
long int lerArquivo(FILE *fl);
int ocupado(long int n);

long int hash(long int val);
long int hash2(long int val);
void inserirHashDuplo1(long int *t, long int n);
void inserirHashDuplo2(long int *tabela, long int val);

void printTabela(long int *tabela);

/*=======================================================*/
long int intervalo;

/*=======================================================*/
int main() {
  clear_window();

  long int *tabela;
  clock_t start, stop;
  double elapsed;
  int opcao;
  char *arquivo;

  /*ESCOLHA DO ARQUIVO*/
  opcao = escolherArquivo();
  switch (opcao) {
  case 1:
    arquivo = "randInt1K.txt";
    intervalo = contarLinhas(arquivo);
    break;
  case 2:
    arquivo = "randInt100K.txt";
    intervalo = contarLinhas(arquivo);
    break;
  }

  /*ESCOLHA DO TAMANHO DA TABELA HASH*/
  opcao = escolhaTamnhoHash();
  switch (opcao) {
  case 1:
    intervalo = intervalo * 1.1;
    break;
  case 2:
    intervalo = intervalo * 1.25;
    break;
  case 3:
    intervalo = intervalo * 1.5;
    break;
  }

  /*ESCOLHO COMO VAI SER FEITO O CALCULO DO HASH
   * USO PONTEIRO PARA FUNCAO*/
  void *hashDuplo;
  opcao = escolhaHashDuplo();
  switch (opcao) {
  case 1:
    hashDuplo = inserirHashDuplo1;
    break;
  case 2:
    hashDuplo = inserirHashDuplo2;
    break;
  }

  /*BUSCA O PROXIMO NUMERO PRIMO A PARTIR DE intervalo*/
  intervalo = numeroPrimo(intervalo, primoProximo);

  // printf("\n\nPrimo: %ld", intervalo);
  /*CRIA A TABELA HASH*/
  tabela = criarTabelaHash(intervalo);
  initTabela(tabela, intervalo);

  /*TEMPO DE INICIO*/
  start = clock();

  inserirArquivo(tabela, arquivo, hashDuplo);

  /*TEMPO FINAL*/
  stop = clock();

  /*EXIBO A TABELA NA TELA*/
  printTabela(tabela);

  /*DESALOCO A TABELA DA MEMORIA*/
  free(tabela);

  /*TEMPO PERCORRIDO EM SEGUNDOS*/
  elapsed = (double)(stop - start) / CLOCKS_PER_SEC;

  /*PRINT DO TEMPO*/
  printf("\n============== Tempo: %lfseg =================\n\n", elapsed);

  return 0;
}

/*=======================================================*/
int escolhaTamnhoHash() {
  int opt;

  printf("\nEscolha o tamanho da tabela hash\n");
  printf("1 - Mult. por 1.1\n");
  printf("2 - Mult. por 1.25\n");
  printf("3 - Mult. por 1.5\n");
  printf("\nEscolha: ");

  do {
    scanf("%d", &opt);
  } while (opt != 1 && opt != 2 && opt != 3);
  return opt;
}

/*=======================================================*/
int escolherArquivo() {
  int opt;

  printf("\nEscolha o arquivo\n");
  printf("1 - 1k numeros\n");
  printf("2 - 100k numeros\n");
  printf("\nEscolha: ");

  do {
    scanf("%d", &opt);
  } while (opt != 1 && opt != 2);

  return opt;
}

/*=======================================================*/
int escolhaHashDuplo() {
  int opt;

  printf("\nEscolha o Método do Hash Duplo\n");
  printf("1 - Primeiro Hash Duplo\n");
  printf("2 - Segundo Hash Duplo\n");
  printf("\nEscolha: ");

  do {
    scanf("%d", &opt);
  } while (opt != 1 && opt != 2);

  return opt;
}

/*=======================================================*/
void clear_window() {
  // PRE-PROCESSAMENTO DO SO
#ifdef __linux__ // SE FOR LINUX
  system("clear");
#else // SE FOR WINDOWS
  system("cls");
#endif
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
void primoProximo(long int *e) { ++*e; }

/*=======================================================*/
void primoAnterior(long int *e) { --*e; }

/*=======================================================*/
int verificarPrimo(long int e) {
  int i;
  // VERIFICA SE n=1 OU n=0
  if (e <= 1)
    return 0;

  // VERIFICA SE n=2 OU n=3
  if (e == 2 || e == 3)
    return 1;

  // VERIFICA SE EH DIVISIVEL POR 2 OU 3
  if (e % 2 == 0 || e % 3 == 0)
    return 0;

  for (i = 5; i * i <= e; i = i + 6)
    if (e % i == 0 || e % (i + 2) == 0)
      return 0;

  return 1;
}

/*=======================================================*/
long int numeroPrimo(long int e, void mudarValor(long int *)) {
  // VERIFICA SE O NUMERO EH PRIMO e altera seu valor COM O PONTEIRO PARA FUNÇÃO
  while (!verificarPrimo(e)) {
    mudarValor(&e);
  }

  return e;
}

/*=======================================================*/
long int *criarTabelaHash(long int tam) {
  return (long int *)malloc(tam * sizeof(long int));
}

/*=======================================================*/
void initTabela(long int *t, long int tam) {
  int i;
  for (i = 0; i < tam; i++) {
    t[i] = VAZIO;
  }
}

/*=======================================================*/
int ocupado(long int n) { return n != VAZIO; }

/*=======================================================*/
long int lerArquivo(FILE *fl) {
  long int num;
  fscanf(fl, "%ld", &num);

  return num;
}

/*=======================================================*/
void inserirArquivo(long int *t, char *arq,
                    void hashDuplo(long int *, long int)) {
  FILE *fl;
  long int val;
  int cont = 0;

  fl = fopen(arq, "r");

  printf("Lendo arquivo...\n");

  while (!feof(fl)) {
    val = lerArquivo(fl);
    hashDuplo(t, val);
    // printf("Foi %d\n", ++cont);
  }

  fclose(fl);
}

/*=======================================================*/
long int hash(long int val) { return val % intervalo; }

/*=======================================================*/
long int hash2(long int val) { return 1 + (val % (intervalo - 1)); }

/*=======================================================*/
void inserirHashDuplo1(long int *tabela, long int val) {
  long int i = hash(val);
  long int h2 = hash2(val);
  long int cont = 0;

  while (ocupado(tabela[i])) {
    if (++cont == intervalo) {
      exit(1); // TABELA CHEIA
      printf("Tabela Cheia\n");
    }

    i = (i + h2) % intervalo;
  }
  tabela[i] = val;
}

/*=======================================================*/
void inserirHashDuplo2(long int *tabela, long int val) {
  long int i = hash(val);
  long int c = intervalo;
  long int cont = 0;

  while (ocupado(tabela[i])) {
    c = numeroPrimo(--c, primoAnterior);
    // if (++cont == intervalo)
    //   exit(1); // CHEGOU NO MENOR NÚMERO PRIMO POSSÍVEL
    i = c - (val % c);
  }
  tabela[i] = val;
}

/*=======================================================*/
void printTabela(long int *tabela) {
  long int i;
  for (i = 0; i < intervalo; i++) {
    printf("[%ld] - %ld \n", i, tabela[i]);
  }
}
