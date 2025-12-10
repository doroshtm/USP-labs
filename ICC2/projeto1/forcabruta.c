#include<stdio.h>
#include<stdlib.h>
#include<time.h>

unsigned long long pot2(unsigned long long);
int calculoValorMaximo(unsigned long long, unsigned int *, int *, unsigned int, unsigned long long*, unsigned long long*);

int main() {
    // quantidade de itens (n) não pode ser negativa, assim como os pesos dos itens e a capacidade da mochila (W)
    unsigned long long n; unsigned int W, *pesos;
    // valores podem ser negativos
    int *valores;
    printf("Digite o número de itens e a capacidade da mochila, nessa ordem: ");
    scanf("%llu %u",&n,&W);
    // como fazemos 2^n, n não pode ser maior que 63 (2^64 estourará o unsigned long long)
    if(n > 63ULL) {
        return 1;
    }

    pesos = malloc(n*sizeof(unsigned int));
    if(pesos == NULL) {
        return 1;
    }
    valores = malloc(n*sizeof(int));
    if(valores == NULL) {
        free(pesos);
        return 1;
    }
    
    for(unsigned int i = 0; i<n; ++i) {
        printf("Digite o peso e o valor do item %u, nessa ordem: ",(unsigned int)(i+1));
        scanf("%u %d",&pesos[i],&valores[i]);
    }

    unsigned long long *itensEscolhidos = malloc(n*sizeof(unsigned long long));
    if(itensEscolhidos == NULL) {
        free(pesos);
        free(valores);
        return 1;
    }
    unsigned long long numItensEscolhidos = 0;

    clock_t inicio = clock();

    int maiorvalor = calculoValorMaximo(n,pesos,valores,W,itensEscolhidos,&numItensEscolhidos);

    clock_t fim = clock();
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nTempo de execução: %.6f segundos\n", tempo_execucao);

    if(maiorvalor == -1) {
        free(pesos);
        free(valores);
        free(itensEscolhidos);
        return 1;
    }

    printf("Os itens escolhidos foram: ");
    for(unsigned long long i = 0; i < numItensEscolhidos; ++i) {
        printf("%llu ",itensEscolhidos[i]+1);
    }
    printf("\nDando um valor total de: %d",maiorvalor);
    free(pesos);
    free(valores);
    free(itensEscolhidos);
}

unsigned long long pot2(unsigned long long pot) {
    return 1ULL << pot;
}

int calculoValorMaximo(unsigned long long n, unsigned int *pesos, int *valores, unsigned int W, unsigned long long *itensEscolhidos, unsigned long long *numItensEscolhidos) {
    unsigned int somapesos = 0;
    int maiorvalor = 0;
    // 2^n combinações possíveis (pensamos aqui em n itens, cada um pode ou não estar na mochila -> n bits -> 2^n combinações)
    unsigned long long potencia = pot2(n);
    int somavalores;
    unsigned long long *tempItensEscolhidos = malloc(n*sizeof(unsigned long long));
    if(tempItensEscolhidos == NULL) {
        return -1;
    }
    unsigned long long tempNumItensEscolhidos = 0;
    // for para cada combinação possível
    for(unsigned long long i = 0; i<potencia; ++i) {
        somapesos = 0; somavalores = 0;
        // acredito que seria possível realizar sem esse segundo for, mas não consegui
        // for para cada item; paramos mais cedo no caso do peso dos itens já terem ultrapassado W; não paramos com somapesos < W para itens com peso nulo
        
        for(unsigned int j = 0; j<n; ++j) {
            if(pesos[j] + somapesos > W) {
                continue;
            }
            // cada inteiro i contém dentro de si os n bits que indicam se o item j (posição j entre n) está ou não na mochila 
            // isso significa que, caso o bit j de i seja 0, então o item na posição j não está na mochila
            if(((i >> j) & 1ULL) == 0ULL) {
                continue;
            }
            tempItensEscolhidos[tempNumItensEscolhidos++] = j;
            somavalores += valores[j];
            somapesos += pesos[j];
        }

        if(somavalores > maiorvalor && somapesos <= W) {
            maiorvalor = somavalores;
            *numItensEscolhidos = tempNumItensEscolhidos;
            for(unsigned long long k = 0; k < *numItensEscolhidos; ++k) {
                itensEscolhidos[k] = tempItensEscolhidos[k];
            }
        }
        tempNumItensEscolhidos = 0;
    }
    free(tempItensEscolhidos);
    return maiorvalor;
}