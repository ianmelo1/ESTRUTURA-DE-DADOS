#include <stdio.h>
#include <stdlib.h>

typedef struct no No;

struct no {
    int dado;
    No *esq;
    No *dir;
};

No *criar_no(int valor) {
    No *novo_no = malloc(sizeof(No));
    if (novo_no) {
        novo_no->esq = NULL;
        novo_no->dir = NULL;
        novo_no->dado = valor;
    }
    return novo_no;
}

void exibir(No *no) {
    if (no) {
        printf("(%d)", no->dado);
        exibir(no->esq);
        exibir(no->dir);
    }
}

int main() {
    No *raiz = criar_no(1);
    raiz->esq = criar_no(2);
      raiz->esq->esq = criar_no(4);
      raiz->esq->dir = criar_no(5);
    raiz->dir = criar_no(6);
      raiz->dir->esq = criar_no(7);
      raiz->dir->dir = criar_no(8);
    exibir(raiz);
    return 0;
}
