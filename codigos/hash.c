#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[250];
    int idade;
} Pessoa;

typedef struct no {
    int chave;
    Pessoa valor;
    struct no *prox;
} NoChaveValor;

typedef struct lista {
    NoChaveValor *inicio;
    int size;
} ListaEnc;

typedef struct {
    ListaEnc *listas;
    int (*h)(int valor);
} HashTable;

int hash10(int idade) {
    return idade % 10;
}

HashTable *criarTabelaHash(int size, int (*h)(int)) {
    HashTable *ht = malloc(sizeof(HashTable));
    if (!ht) return NULL;

    ht->listas = calloc(size, sizeof(ListaEnc));
    if (!ht->listas) {
        free(ht);
        return NULL;
    }

    ht->h = h;
    return ht;
}

NoChaveValor *criarNo(int chave, Pessoa valor) {
    NoChaveValor *novo = malloc(sizeof(NoChaveValor));
    if (novo) {
        novo->chave = chave;
        novo->valor = valor;
        novo->prox = NULL;
    }
    return novo;
}

void inserir(Pessoa p, HashTable *ht) {
    if (!ht) return;

    int h = ht->h(p.idade);
    ListaEnc *lista = &ht->listas[h];

    NoChaveValor *atual = lista->inicio;
    while (atual) {
        if (atual->chave == p.idade) {
            atual->valor = p; // sobrescreve
            return;
        }
        atual = atual->prox;
    }

    NoChaveValor *novo = criarNo(p.idade, p);
    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->size++;
}

NoChaveValor *getValue(HashTable *ht, int key) {
    if (!ht) return NULL;

    int h = ht->h(key);
    ListaEnc *lista = &ht->listas[h];

    NoChaveValor *atual = lista->inicio;
    while (atual) {
        if (atual->chave == key) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void delKey(HashTable *ht, int key) {
    if (!ht) return;

    int h = ht->h(key);
    ListaEnc *lista = &ht->listas[h];
    NoChaveValor *atual = lista->inicio;
    NoChaveValor *anterior = NULL;

    while (atual) {
        if (atual->chave == key) {
            if (anterior) {
                anterior->prox = atual->prox;
            } else {
                lista->inicio = atual->prox;
            }
            free(atual);
            lista->size--;
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

int main() {
    HashTable *ht = criarTabelaHash(10, hash10);

    Pessoa p1 = {"Ana", 25};
    Pessoa p2 = {"Bruno", 35};
    Pessoa p3 = {"Carlos", 45};

    inserir(p1, ht);
    inserir(p2, ht);
    inserir(p3, ht);

    NoChaveValor *res = getValue(ht, 35);
    if (res) {
        printf("Encontrado: %s (%d)\n", res->valor.nome, res->valor.idade);
    }

 

    delKey(ht, 25);
    free(ht->listas);
    free(ht);

    return 0;
}
