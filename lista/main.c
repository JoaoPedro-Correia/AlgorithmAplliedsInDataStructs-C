/*PRE-PROCESSAMENTO DAS FUNCOES IMPORTADAS*/
#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif

#ifndef STDLIB_H
#define STDLIB_H
#include <stdlib.h>
#endif

/*CHAMO A BIBLIOTECA DA LISTA*/
#include "list.h"

/*LIMPO O TERMINAL*/
void clear_window(void);
/*LIMPO O BUFFER DO COMPUTADOR*/
void clear_buff(void);
/*EXIBE O MENU PRINCIPAL*/
int menu(void);
/*ADICIONA ALGUM NUMERO NA LISTA*/
void add_element(List *);
/*REMOVE ALGUM NUMERO DA LISTA*/
void remove_element(List *);
/*EXIBE A LISTA NA TELA*/
void print_list(List *);
/*PROCURA ALGUM NUMERO NA LISTA*/
void search_element(List *);

int main() {
  int option;
  List *list;

  /*CRIA UMA LISTA*/
  list = list_new();

  // LUPIM DO PROGRAMA
  // SAI COM A OPCAO '0'
  do {
    /*LIMPA O TERMINAL*/
    clear_window();
    // EXIBE O MENU
    option = menu();

    // CHAMA A FUNCAO SELECIONADA PELO USUARIO
    switch (option) {
    case 1:
      add_element(list);
      getchar();
      break;
    case 2:
      remove_element(list);
      getchar();
      break;
    case 3:
      print_list(list);
      getchar();
      break;
    case 4:
      search_element(list);
      getchar();
      break;
    }
    // LIMPA O BUFFER
    clear_buff();
  } while (option != 0);

  list_clear(list);
  return 0;
}

void clear_buff() {
  int c;
  while ((c = getchar()) != '\n') {
  }
}

void clear_window() {
  // PRE-PROCESSAMENTO DO SO
#ifdef __linux__ // SE FOR LINUX
  system("clear");
#else // SE FOR WINDOWS
  system("cls");
#endif
}

int menu() {
  int option;
  printf("1 - Inserir\n");
  printf("2 - Remover\n");
  printf("3 - Printar listas\n");
  printf("4 - Buscas elemento\n");
  printf("0 - Sair\n");

  scanf("%d", &option);

  return option;
}

void add_element(List *list) {
  int num;
  printf("\nAdicionar número: ");
  scanf("%d", &num);

  list_add(list, num);
}

void remove_element(List *list) {
  int num;
  printf("\nRemover número: ");
  scanf("%d", &num);

  int r = list_remove(list, num);

  if (r == 1) { // REMOVEU O NUMERO
    printf("\nRemovido com sucesso!\n");
  } else { // NAO TEM O NUMERO NA LISTA
    printf("\nLista não tem o valor\n");
  }
}

void print_list(List *list) {
  int num = get_total(list); // PEGA O TAMANHO DA LISTA
  int i, val; // CONTADOR E VARIAVEL QUE ARMAZENA OS VALORES DA LISTA

  printf("\n[");
  for (i = 0; i < num; i++) {
    val = list_search(list, i); // BUSCA O VALOR NA POSICAO i
    printf("%d ", val);         // PRINTA O VALOR
  }
  printf("\b]\n");
}

void search_element(List *list) {
  int num;
  printf("\nBuscar número: ");
  scanf("%d", &num);

  int s = list_search_element(list, num);

  if (s == 1) { // ACHOU O VALOR
    printf("\nAchou o valor!\n");
  } else { // NAO ACHOU O VALOR
    printf("\nNão achou o elemento\n");
  }
}
