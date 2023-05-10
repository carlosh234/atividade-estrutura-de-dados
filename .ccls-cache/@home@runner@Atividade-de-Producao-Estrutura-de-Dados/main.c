#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nome[20];
  float nota;
  int turma;
} Aluno;

typedef struct No {
  Aluno aluno;
  struct No *ant;
  struct No *prox;
} No;

typedef struct {
  No *inicio;
  No *fim;
} Lista;

No *criar_no(Aluno aluno) {
  No *no = (No *)malloc(sizeof(No));
  no->aluno = aluno;
  no->ant = NULL;
  no->prox = NULL;
  return no;
}

void inicializar_lista(Lista *lista) {
  lista->inicio = NULL;
  lista->fim = NULL;
}

void inserir_no_inicio(Lista *lista, Aluno aluno) {
  No *no = criar_no(aluno);

  if (lista->inicio == NULL) {
    lista->inicio = no;
    lista->fim = no;
  } else {
    no->prox = lista->inicio;
    lista->inicio->ant = no;
    lista->inicio = no;
  }
}

void inserir_no_final(Lista *lista, Aluno aluno) {
  No *no = criar_no(aluno);

  if (lista->inicio == NULL) {
    lista->inicio = no;
    lista->fim = no;
  } else {
    no->ant = lista->fim;
    lista->fim->prox = no;
    lista->fim = no;
  }
}

void inserir_no_meio(Lista *lista, Aluno aluno, int posicao) {
  No *no = criar_no(aluno);
  No *atual = lista->inicio;
  int cont = 1;

  if (posicao == 1) {
    inserir_no_inicio(lista, aluno);
    return;
  }

  while (cont < posicao - 1) {
    if (atual == NULL) {
      printf("Posição aponta para NULL!\n");
      return;
    }
    atual = atual->prox;
    cont++;
  }

  if (atual == NULL) {
    printf("Posição aponta para NULL!\n");
    return;
  }

  no->prox = atual->prox;
  no->ant = atual;
  if (atual->prox != NULL) {
    atual->prox->ant = no;
  }
  atual->prox = no;
}

void imprimir_lista(Lista lista) {
  No *atual = lista.inicio;

  printf("===========IMPRIMINDO LISTA==========\n\n");

  while (atual != NULL) {
    printf("{nome: %s, nota: %.2f, turma: %d},\n", atual->aluno.nome,
           atual->aluno.nota, atual->aluno.turma);

    atual = atual->prox;
  }

  printf("=====================================\n\n");
}

void imprimir_lista_ao_contrario(Lista lista) {
  No *fim = lista.fim;

  printf("====IMPRIMINDO LISTA AO CONTRARIO====\n\n");
  while (fim != NULL) {
    printf("{nome: %s, nota: %.2f, turma: %d},\n", fim->aluno.nome,
           fim->aluno.nota, fim->aluno.turma);
    fim = fim->ant;
  }

  printf("=====================================\n\n");
}

void excluir_lista(Lista *lista) {
  No *atual = lista->inicio;
  No *prox;

  while (atual != NULL) {
    prox = atual->prox;
    free(atual);
    atual = prox;
  }

  lista->inicio = NULL;
  lista->fim = NULL;
}

void excluir_no_meio(Lista *lista, int posicao) {
  if (posicao < 1) {
    return;
  }

  No *atual = lista->inicio;
  int count = 1;

  while (count < posicao) {
    if (atual == NULL) {

      return;
    }
    atual = atual->prox;
    count++;
  }

  if (atual == NULL) {
    printf("Posicao aponta para NULL!\n");
    return;
  }

  if (atual == lista->inicio && atual == lista->fim) {
    lista->inicio = NULL;
    lista->fim = NULL;
  } else if (atual == lista->inicio) {
    lista->inicio = atual->prox;
    atual->prox->ant = NULL;
  } else if (atual == lista->fim) {
    lista->fim = atual->ant;
    atual->ant->prox = NULL;
  } else {
    atual->ant->prox = atual->prox;
    atual->prox->ant = atual->ant;
  }
  free(atual);
}

int main() {
  Lista lista;
  inicializar_lista(&lista);

  Aluno joao;
  strcpy(joao.nome, "João");
  joao.nota = 5.0;
  joao.turma = 1;

  Aluno maria;
  strcpy(maria.nome, "Maria");
  maria.nota = 3.0;
  maria.turma = 3;

  Aluno paula;
  strcpy(paula.nome, "Paula");
  paula.nota = 9.75;
  paula.turma = 1;

  Aluno carlos;
  strcpy(carlos.nome, "Carlos");
  carlos.nota = 10.0;
  carlos.turma = 2;

  inserir_no_inicio(&lista, joao);
  inserir_no_final(&lista, maria);
  inserir_no_final(&lista, paula);
  inserir_no_meio(&lista, carlos, 3);

  printf("Adionando João no inicio, Maria no final,Paula no final e Carlos na "
         "terceira posição:\n\n");
  imprimir_lista(lista);
  imprimir_lista_ao_contrario(lista);

  excluir_no_meio(&lista, 2);
  excluir_no_meio(&lista, 3);

  printf("Lista após excluir Maria e Paula:\n\n");
  imprimir_lista(lista);
  imprimir_lista_ao_contrario(lista);

  excluir_lista(&lista);

  printf("Após excluir toda a lista:\n\n");
  imprimir_lista(lista);
  imprimir_lista_ao_contrario(lista);
  return 0;
}