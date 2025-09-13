#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


typedef struct {
    int dado;
    NO* proximo;
    NO* anterior;
} NO;

typedef struct {
    NO* ultimo;
    NO* primeiro;
} LISTA;


LISTA *lista_criar();

void lista_inserir(LISTA*, int);

void lista_imprimir(LISTA*);

void lista_liberar(LISTA *lista);

int main() {
    int n;

    scanf("%d", &n);
    LISTA *configInicial = lista_criar();
    for (int i = 0; i < 4; ++i) {
        int valor;
        scanf("%d", &valor);
        lista_inserir(configInicial, valor);
    }
    LISTA *configDesejada = lista_criar();
    for (int i = 0; i < 4; ++i) {
        int valor;
        scanf("%d", &valor);
        lista_inserir(configDesejada, valor);
    }

    scanf("%d", &n);
    LISTA **configsProibidas = malloc(n * sizeof(LISTA*));
    for (int i = 0; i < n; ++i) {
        configsProibidas[i] = lista_criar();
        for (int j = 0; j < 4; ++j) {
            int valor;
            scanf("%d", &valor);
            lista_inserir(configsProibidas[i], valor);
        }
    }
    bool **melhoresCaminhos = malloc(16*4);
    int diferencas[4];
    NO *atual;
    atual = configInicial->primeiro;
    for (int i = 0; i < 4; ++i) {
        diferencas[i] = atual->dado - configDesejada->primeiro->dado;
        atual = atual->proximo;
    }

    lista_liberar(configInicial);
    lista_liberar(configDesejada);
    for (int i = 0; i < n; ++i) {
        lista_liberar(configsProibidas[i]);
    }
    free(configsProibidas);

    return 0;
}


LISTA *lista_criar() {
    LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
    lista->ultimo = NULL;
    lista->primeiro = NULL;
    return lista;
}

void lista_inserir(LISTA *lista, int valor) {
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

void lista_imprimir(LISTA *lista) {
    NO* atual = lista->primeiro;
    while (atual != NULL) {
        printf("%d -> ", atual->dado);
        atual = atual->proximo;
    }
    printf("NULL\n");
}

void lista_liberar(LISTA *lista) {
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