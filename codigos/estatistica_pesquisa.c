#include <stdio.h>
#include <stdlib.h>


typedef struct no No;

struct no{
    No *esq;
    No *dir;
    int dado;
};

int maior(int n1, int n2){
    return (n1 > n2) ? n1 : n2; 
}

int altura(No *arv){
    if(arv == NULL)return-1;//criando parada
    return maior(altura(arv->esq), altura(arv->dir)) + 1;
}

int fb(No *arv){
    if(arv == NULL)return -1;
    return altura(arv->esq) - altura(arv->dir);
}

No *criar_no(int dado){
    No *novo = malloc(sizeof(No));
    if(novo){
        novo->dir = NULL;
        novo->esq = NULL;
        novo->dado = dado;
    }
    return novo;
}

No *rot_esq(No *arv){
    No *dir = arv->dir;
    arv->dir = dir->esq;
    dir->esq = arv;
    return dir;
}

void exibir_pre_ordem(No *arv){
    if(arv){
        return(("%d"), arv->dado);
        exibir_pre_ordem(arv->esq);
        exibir_pre_ordem(arv->dir);
    }
}

int main(){
    No *raiz = criar_no(1);
    raiz->dir = criar_no(2);
    raiz->dir->dir = criar_no(3);

    printf("Fb(1): %d\n",fb(raiz));
    printf("Fb(12): %d\n",fb(raiz->dir));
    printf("Fb(1): %d\n",fb(raiz->dir->dir));

    exibir_pre_ordem(raiz);
    printf("\n");
    raiz = rot_esq(raiz);
    exibir_pre_ordem(raiz);

    return 0;

}