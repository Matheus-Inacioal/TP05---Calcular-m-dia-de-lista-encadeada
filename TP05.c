#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
    int chave;
    struct Item *proximo; 
} Item;

typedef struct Lista {
    Item *cabeca; 
    int tamanho;
} Lista;


void exibirLista(Lista *lista) {
    printf("Lista: ");

    Item *atual = lista->cabeca; 

    while (atual != NULL) {
        printf("%d ", atual->chave);
        atual = atual->proximo;
    }

    printf("\n");
}

Lista *criarListaVazia() {
    Lista *novaLista = (Lista *)malloc(sizeof(Lista));

    if (novaLista == NULL) {
        printf("Erro ao alocar memória para a lista. \n");
        exit(1);
    }

    novaLista->cabeca = NULL;
    novaLista->tamanho = 0;

    return novaLista;
}


void inserirNaPosicao(Lista *lista, int posicao, Item *item) {
    if (posicao < 0 || posicao > lista->tamanho) {
        printf("Posicao invalida.\n");
        return;
    }

    if (posicao == 0) {
        item->proximo = lista->cabeca;
        lista->cabeca = item;
    } else {
        Item *temp = lista->cabeca;

        for (int i = 0; i < posicao - 1; i++) {
            temp = temp->proximo;
        }

        item->proximo = temp->proximo;
        temp->proximo = item;
    }

    lista->tamanho++;
}


void removerDaPosicao(Lista *lista, int posicao) {
    if (posicao < 0 || posicao >= lista->tamanho) {
        printf("Posicao invalida.\n");
        return;
    }

    if (posicao == 0) {
        Item *temp = lista->cabeca;
        lista->cabeca = lista->cabeca->proximo;
        free(temp);
    } else {
        Item *temp = lista->cabeca;

        for (int i = 0; i < posicao - 1; i++) {
            temp = temp->proximo;
        }

        Item *aux = temp->proximo;
        temp->proximo = aux->proximo;
        free(aux);
    }

    lista->tamanho--;
}


float calcularMedia(Lista *lista) {
    if (lista == NULL || lista->tamanho == 0) {
        printf("Lista vazia. Não é possível calcular a média.\n");
        return 0.0; 
    }

    Item *atual = lista->cabeca;
    int soma = 0;

    while (atual != NULL) {
        soma += atual->chave;
        atual = atual->proximo;
    }

    return (float)soma / lista->tamanho;
}

int main() {
    Lista *X = criarListaVazia();

    Item *I1 = (Item *)malloc(sizeof(Item));
    I1->chave = 10;

    Item *I2 = (Item *)malloc(sizeof(Item));
    I2->chave = 20;

    Item *I3 = (Item *)malloc(sizeof(Item));
    I3->chave = 30;

    Item *I4 = (Item *)malloc(sizeof(Item));
    I4->chave = 40;

    inserirNaPosicao(X, 0, I1);
    inserirNaPosicao(X, 0, I2);
    inserirNaPosicao(X, 0, I3);
    inserirNaPosicao(X, 0, I4);

    printf("Tamanho: %d\n", X->tamanho);
    exibirLista(X);

    removerDaPosicao(X, 0);

    printf("Tamanho: %d\n", X->tamanho);
    exibirLista(X);

    float media = calcularMedia(X);
    printf("Média: %.2f\n", media);

    return 0;
}