#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct coeficiente {
    float valor;
    unsigned long long indice;
};

void merge(struct coeficiente *, unsigned long long, unsigned long long, unsigned long long);
void mergeSort(struct coeficiente *, unsigned long long);
int calculoValorMaximo(unsigned long long, unsigned int, struct coeficiente *, unsigned int *, int *, unsigned long long *, unsigned long long*);

int main(void) {
    // quantidade de itens (n) não pode ser negativa, assim como os pesos dos itens e a capacidade da mochila (W)
    unsigned long long n; unsigned int W, *pesos;
    // valores podem ser negativos
    int *valores;
    printf("Digite o número de itens e a capacidade da mochila, nessa ordem: ");
    scanf("%llu %u",&n,&W);

    pesos = malloc(n*sizeof(unsigned int));
    if(pesos == NULL) {
        return 1;
    }
    valores = malloc(n*sizeof(int));
    if(valores == NULL) {
        free(pesos);
        return 1;
    }
    struct coeficiente *coeficientes = malloc(n*sizeof(struct coeficiente));
    if(coeficientes == NULL) {
        free(pesos);
        free(valores);
        return 1;
    }
    
    for(unsigned long long i = 0; i < n; ++i) {
        printf("Digite o peso e o valor do item %llu, nessa ordem: ", i+1);
        scanf("%u %d",&pesos[i],&valores[i]);
        // se o peso for 0, o coeficiente é, em teoria, infinito (sempre vale a pena pegar o item)
        coeficientes[i].indice = i;
        if(pesos[i] == 0) {
            coeficientes[i].valor = __FLT_MAX__;
            continue;
        }
    coeficientes[i].valor = (float)valores[i] / (float)pesos[i];
    }
    clock_t inicio = clock();
    mergeSort(coeficientes, n);
    unsigned long long *itensEscolhidos = malloc(n*sizeof(unsigned long long));
    if(itensEscolhidos == NULL) {
        free(pesos);
        free(valores);
        free(coeficientes);
        return 1;
    }
    unsigned long long numItensEscolhidos = 0;

    int maiorvalor = calculoValorMaximo(n,W,coeficientes,pesos,valores,itensEscolhidos,&numItensEscolhidos);
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %lf segundos\n", tempo);

    printf("Os itens escolhidos foram: ");
    for(unsigned long long i = 0; i < numItensEscolhidos; ++i) {
        printf("%llu ",itensEscolhidos[i]+1);
    }
    printf("\nDando um valor total de: %d",maiorvalor);
    free(pesos);
    free(valores);
    free(coeficientes);
    free(itensEscolhidos);
}

int calculoValorMaximo(unsigned long long n, unsigned int W, struct coeficiente *coeficientes, unsigned int *pesos, int *valores, unsigned long long *itensEscolhidos, unsigned long long *numItensEscolhidos) {
    unsigned long long somapesos = 0;
    int somavalores = 0;
    // para cada item, na ordem decrescente de valor/peso; saímos do loop quando não há mais itens ou quando a mochila está cheia
    for(unsigned long long i = 0; i < n; ++i) {
        unsigned long long pos = coeficientes[i].indice;
        if(pesos[pos] < 0) {
            break;
        }
        if(somapesos + pesos[pos] > W) {
            continue;
        }
        itensEscolhidos[(*numItensEscolhidos)++] = pos;
        somavalores += valores[pos];
        somapesos += pesos[pos];
    }
    return somavalores;
}

void mergeSort(struct coeficiente *arr, unsigned long long n) {
    for(unsigned long long tamanho = 1; tamanho < n; tamanho *= 2ULL) {
        for(unsigned long long inicio = 0; inicio < n - 1ULL; inicio += 2ULL * tamanho) {
            unsigned long long meio = inicio + tamanho - 1ULL;
            unsigned long long fim = (inicio + 2ULL * tamanho - 1ULL < n - 1ULL) ? (inicio + 2ULL * tamanho - 1ULL) : (n - 1ULL);
            if(meio < fim) {
                merge(arr, inicio, meio, fim);
            }
        }
    }
}

void merge(struct coeficiente *arr, unsigned long long inicio, unsigned long long meio, unsigned long long fim) {
    unsigned long long n1 = meio - inicio + 1;
    unsigned long long n2 = fim - meio;

    struct coeficiente *L = malloc(n1 * sizeof(struct coeficiente));
    if (L == NULL) {
        return;
    }
    struct coeficiente *R = malloc(n2 * sizeof(struct coeficiente));
    if (R == NULL) {
        free(L);
        return;
    }

    for (unsigned long long i = 0; i < n1; ++i) {
        L[i] = arr[inicio + i];
    }
    for (unsigned long long j = 0; j < n2; ++j) {
        R[j] = arr[meio + 1 + j];
    }

    unsigned long long i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        if (L[i].valor >= R[j].valor) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}