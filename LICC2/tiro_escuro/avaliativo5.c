//Arthur de Castro Dias - 16855302
//Gabriel Carraro Salzedas - 16827905
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"util.h"

void preencherVetor(char *dispo, int *v, int N){
    if(!strcmp(dispo, "reverse")){
        for(int i=N; i>0; i--){
            v[N-i] = i;
        }
    }else if(!strcmp(dispo, "random")){
        int seed = 12345;
        for(int i=0; i<N; i++){
            int numero_aleatorio = get_random(&seed, N);
            v[i] = numero_aleatorio;
        }
    }else{
        for(int i=1; i<=N; i++){
            v[i-1] = i;
        }
    }
}

void radixSort(int *v, int esq, int dir, int bit) {
    if (esq >= dir || bit < 0) {
        return;
    }

    int i = esq, j = dir;
    while (i <= j) {
        while (i <= j && ((v[i] >> bit) & 1) == 0) {
            ++i;
        }
        while (i <= j && ((v[j] >> bit) & 1) == 1) {
            --j;
        }
        if (i < j) {
            int tmp = v[i];
            v[i] = v[j];
            v[j] = tmp;
            ++i;
            --j;
        }
    }
    radixSort(v, esq, j, bit - 1);
    radixSort(v, i, dir, bit - 1);
}

void insercao_por_passo(int *vetor, size_t n, size_t passo) {
    for (size_t i = passo; i < n; ++i) {
        int chave = vetor[i];
        size_t j = i;
        while (j >= passo && vetor[j - passo] > chave) {
            vetor[j] = vetor[j - passo];
            j -= passo;
        }
        vetor[j] = chave;
    }
}

void shellsort(int *vetor, size_t n) {
    if (n < 2) {
        return;
    }
    size_t sequencia_ciura[] = {1,4,10,23,57,132,301,701,1750,0};
    size_t m = 0;
    while (sequencia_ciura[m]) {
        ++m;
    }
    size_t capacidade_passos = m;
    size_t *passos = (size_t *)0;
    if (n > 1750) {
        capacidade_passos = m;
        size_t k = 1750;
        while (k < n) {
            k = (size_t)(k * 2.25 + 0.5);
            ++capacidade_passos;
        }
        passos = (size_t *)malloc(capacidade_passos * sizeof(size_t));
        if (!passos) {
            for (size_t i = m; i-- > 0; ) {
                insercao_por_passo(vetor, n, sequencia_ciura[i]);
            }
            return;
        }
        for (size_t i = 0; i < m; ++i) {
            passos[i] = sequencia_ciura[i];
        }
        size_t indice = m;
        size_t atual = 1750;
        while (indice < capacidade_passos) {
            atual = (size_t)(atual * 2.25 + 0.5);
            passos[indice++] = atual;
        }
    }
    if (passos) {
        for (size_t i = capacidade_passos; i-- > 0; ) {
            insercao_por_passo(vetor, n, passos[i]);
        }
        free(passos);
    } else {
        for (size_t i = m; i-- > 0; ) {
            insercao_por_passo(vetor, n, sequencia_ciura[i]);
        }
    }
}

void quickSort(int *v, int N){
    if(N <= 1){
        return;
    }
    int pivo = v[N/2];
    int i = 0, j = N - 1, aux;
    while (i <= j) {
        while (v[i] < pivo) {
            ++i;
        }
        while (v[j] > pivo) {
            --j;
        }
        if (i <= j) {
            aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            ++i;
            --j;
        }
    }
    quickSort(v, j + 1);
    quickSort(v + i, N - i);
}

void shellsortantigo(int *v, int N, int h[]){
    int incr;
    for(int i=0; i<15; i++){
        incr = h[i];
        for(int j=0; j+incr<=N; j++){
            for(int k = j+incr; k+incr<=N; k+=incr){
                if(v[j] > v[k]){
                    int aux = v[j];
                    v[j] = v[k];
                    v[k] = aux;
                }
            }
        }
    }
}

void mergesort(int *v, int n) {
    int *temp = malloc(n * sizeof(int));
    if (!temp) {
        return;
    }

    for (int i = 1; i < n; i *= 2) {
        for (int j = 0; j < n; j += 2*i) {
            int meio = j + i;
            int dir = j + 2*i;
            if (meio > n) {
                meio = n;
            }
            if (dir > n) {
                dir = n;
            }

            int i = j, j = meio, k = j;
            while (i < meio && j < dir) {
                temp[k++] = (v[i] <= v[j]) ? v[i++] : v[j++];
            }
            while (i < meio) {
                temp[k++] = v[i++];
            }
            while (j < dir) {
                temp[k++] = v[j++];
            }
        }
        for (int i = 0; i < n; ++i) {
            v[i] = temp[i];
        }
    }
    free(temp);
}

int main(){
    int N, id;
    char disposicao[8];
    scanf("%d", &N);
    scanf("%s", disposicao);
    scanf("%d", &id);
    int *vetor = malloc(sizeof(int) * N);
    preencherVetor(disposicao, vetor, N);
    switch(id){
        case 1:
            quickSort(vetor, N);
            break;
        case 2:
            shellsort(vetor, N);
            break;
        case 3:
            radixSort(vetor, 0, N-1, 31);
            break;
        case 4:
            // TENTATIVA ANTIGA DE SHELLSORT COM H DE KNUTH:
            int h[15];
            h[14] = 1;
            for(int i = 13; i>=0; i--){
                h[i] = 3*h[i+1] + 1;
            }
            shellsortantigo(vetor, N, h);
            break;
        case 5:
            mergesort(vetor, N);
            break;
            
    }
    init_crc32();
    uint32_t saida = crc32(0, vetor, N * sizeof(int));
    printf("%08X", saida);
    free(vetor);
}

//init_crc32();
//uint32_t saida = crc32(0, vetor, N * sizeof(int));
//printf("%08X", saida);
