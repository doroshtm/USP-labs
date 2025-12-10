#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Brinquedo{
    char cor[9];
    float nota;
    float comprimento;
    int indice;
}Brinquedo;

//Função para comparação
int compara(Brinquedo a, Brinquedo b){
    if(strcmp(a.cor, b.cor) > 0){
        return 1;
    }else if(strcmp(a.cor, b.cor) < 0){
        return 0;
    }else{
        if(a.comprimento <  b.comprimento){
            return 0;
        }else if(a.comprimento > b.comprimento){
            return 1;
        }else{
            if(a.nota < b.nota){
                return 1;
            }else if(a.nota > b.nota){
                return 0;
            }else{
                return a.indice > b.indice;
            }
        }
    }
}

void bubbleSort(Brinquedo b[], int numBrinq){
    Brinquedo aux;
    for(int i=0; i<numBrinq; i++){
        for(int j=0; j<numBrinq-i-1; j++){
            if(compara(b[j], b[j+1])){
                aux = b[j+1];
                b[j+1] = b[j];
                b[j] = aux;
            }
        }
    }
}
int buscaBinaria(Brinquedo b[], Brinquedo chave, int inicio, int fim) {
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        if (compara(b[meio], chave)) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return inicio;
}


void insertionSort(Brinquedo b[], int n) {
    for (int i = 1; i < n; i++) {
        Brinquedo chave = b[i];
        int pos = buscaBinaria(b, chave, 0, i - 1);

        for (int j = i - 1; j >= pos; --j) {
            b[j + 1] = b[j];
        }
        b[pos] = chave;
    }
}

void merge(Brinquedo b[], Brinquedo aux[], int esq, int meio, int dir){
    int i = esq, j = meio, k = esq;
    while(i < meio && j < dir){
        if(compara(b[i],b[j])){
            aux[k++] = b[j++];
        }else{
            aux[k++] = b[i++];
        }
    }
    while(i < meio) {
        aux[k++] = b[i++];
    }
    while(j < dir) {
        aux[k++] = b[j++];
    }
    for(i=esq; i<dir; ++i) {
        b[i] = aux[i];
    }
}

void mergeSort(Brinquedo b[], int n){
    Brinquedo *aux = malloc(n * sizeof(Brinquedo));
    for(int tam = 1; tam < n; tam *= 2){
        for(int esq = 0; esq < n-tam; esq += 2*tam){
            int meio = esq + tam;
            int dir = (esq + 2*tam < n) ? esq + 2*tam : n;
            merge(b, aux, esq, meio, dir);
        }
    }
    free(aux);
}

void quickSort(Brinquedo v[], int inf, int sup) {
    int i = inf;
    int j = sup;
    Brinquedo pivo = v[(inf + sup) / 2];

    do {
        while (compara(pivo, v[i])) {
            ++i;
        }
        while (compara(v[j], pivo)) {
            --j;
        }

        if (i <= j) {
            Brinquedo aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            ++i;
            --j;
        }
    } while (i <= j);

    if (inf < j) {
        quickSort(v, inf, j);
    }
    if (i < sup) {
        quickSort(v, i, sup);
    }
}


int main(){
    int numBrinq, ord;
    scanf("%d", &numBrinq);
    Brinquedo brinq[numBrinq];
    for(int i = 0; i<numBrinq; i++){
        scanf("%s %f %f", brinq[i].cor, &brinq[i].comprimento, &brinq[i].nota);
        brinq[i].indice = i;
    }
    scanf("%d", &ord);
    switch(ord){
        case 1:
            bubbleSort(brinq, numBrinq);
            break;
        case 2:
            insertionSort(brinq, numBrinq);
            break;
        case 3:
            mergeSort(brinq, numBrinq);
            break;
        case 4:
            quickSort(brinq, 0, numBrinq - 1);
            break;
    }
    for(int i=0; i<numBrinq; i++){
        printf("%d;", brinq[i].indice);
    }
    printf("\n");
}