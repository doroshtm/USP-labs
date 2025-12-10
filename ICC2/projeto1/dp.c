#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct item_{
    unsigned long long peso;
    long double valor;
    unsigned long long id;
} ITEM;

long double valorMaximo(ITEM itens[], unsigned long long tam, unsigned long long peso, long double **tabulacao){
    if(tam == 0 || peso == 0){
        return 0;
    }
    for(unsigned long long i=1; i<tam+1; i++){
        for(unsigned long long j=1; j<peso+1; j++){
            long double valor1 = 0;
            if(itens[i-1].peso <= j){
                valor1 = itens[i-1].valor + tabulacao[i-1][j - itens[i-1].peso];
            }
            long double valor2 = tabulacao[i-1][j];
            if(valor1 > valor2){
                tabulacao[i][j] = valor1;
            }else{
                tabulacao[i][j] = valor2;
            }
        }
    }
    return tabulacao[tam][peso];
}

int main(){
    unsigned long long n, w;
    printf("Digite a quantidade de itens dosponibilizados: ");
    if(scanf("%llu", &n) != 1) return 1;
    printf("Digite a capacidade total da mochila: ");
    if(scanf("%llu", &w) != 1) return 1;
    ITEM *itens = malloc(n * sizeof(ITEM));
    if(!itens) return 1;
    for(unsigned long long i = 0; i< n; i++){
        printf("Peso do item %llu: ", i+1);
        if(scanf("%llu", &(itens[i].peso)) != 1){ free(itens); return 1; }
        printf("Valor do item %llu: ", i+1);
        if(scanf("%Lf", &(itens[i].valor)) != 1){ free(itens); return 1; }
        itens[i].id = i;
    }
    size_t linhas = (size_t)(n + 1);
    size_t colunas = (size_t)(w + 1);
    long double *bloco = calloc(linhas * colunas, sizeof(long double));
    if(!bloco) { 
        free(itens);
        return 1;
    }
    long double **tabulacao = malloc(linhas * sizeof(long double *));
    if(!tabulacao) {
        free(bloco);
        free(itens);
        return 1;
    }
    for(size_t i = 0; i < linhas; i++){
        tabulacao[i] = bloco + i * colunas;
    }
    clock_t inicio = clock();
    long double resultado = valorMaximo(itens, n, w, tabulacao);
    clock_t fim = clock();
    printf("Maior valor que pode ser carregado na mochila: %.2Lf\n", resultado);
    printf("Itens usados:\n");
    for (unsigned long long i = n; i > 0; i--) {
        if (tabulacao[i][w] != tabulacao[i-1][w]) {
            printf("Item %llu\n", itens[i-1].id+1);
            w -= itens[i-1].peso;
        }
    }
    free(tabulacao);
    free(bloco);
    free(itens);
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %lf segundos\n", tempo);
    return 0;
}
