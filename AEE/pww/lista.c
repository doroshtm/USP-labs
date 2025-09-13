#include <stdio.h>
#include <stdlib.h>
#include"lista.h"

struct no_ {
    int dado;
    NO* proximo;
    NO* anterior;
};

struct lista_ {
    NO* ultimo;
    NO* primeiro;
};



Lista* lista_criar() {
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->ultimo = NULL;
    lista->primeiro = NULL;
    return lista;
}

void lista_inserir(Lista* lista, int valor) {
    NO* novo = (NO*)malloc(sizeof(NO));
    novo->dado = valor;
    novo->proximo = lista->primeiro;
    novo->anterior = lista->ultimo;
    if (lista->ultimo != NULL) {
        lista->ultimo->proximo = novo;
    }
    lista->ultimo = novo;
    if (lista->primeiro == NULL) {
        lista->primeiro = novo;
    }
}

void lista_imprimir(Lista* lista) {
    NO* atual = lista->primeiro;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

void lista_liberar(Lista* lista) {
    if (lista->primeiro == NULL) {
        free(lista);
        return;
    }
    lista->primeiro->anterior->proximo = NULL;
    NO* atual = lista->primeiro;
    while (atual != NULL) {
        NO* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    free(lista);
}