#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void gerarordenado(unsigned int *, unsigned int);
void gerarinverso(unsigned int *, unsigned int);
void geraraleatorio(unsigned int *, unsigned int);

int main(void) {
    //declaração do vetor contendo os tamanhos de cada input
    unsigned int ns[] = {100, 1000, 10000, 100000};
    //qtd contém o tamanho de inputs
    unsigned int qtd = sizeof(ns)/sizeof(ns[0]);

    gerarordenado(ns, qtd);
    gerarinverso(ns, qtd);
    geraraleatorio(ns, qtd);
}

void gerarordenado(unsigned int *ns, unsigned int quant) {
    for(unsigned int i = 0; i < quant; ++i) {
        unsigned int n = ns[i];
        char filename[64];
        //Geração de nome dinâmico de acordo com o input input e o nome
        //É armazenado em filename.
        sprintf(filename, "input_%u-o.txt", n);
        //O modo w, além de possibilitar a escrita de arquivo ele gera um novo
        //arquivo caso o enviado não exista
        FILE *f = fopen(filename, "w");
        //Tratamento para falah do ponteiro
        if(!f) {
            perror("fopen");
            exit(1);
        }
        //Escreve na primeira linha do arquivo o tamanho do input
        fprintf(f, "%u\n", n);
        //Cada linha do arquivo conterá um valor, sendo posicionado de forma crescente
        for(unsigned int j = 1; j <= n; ++j) {
            unsigned int res = ((unsigned long long)j * j) / 100;
            fprintf(f, "%u\n", res);
        }
        fclose(f);
        printf("%s\n", filename);
    }
}

void gerarinverso(unsigned int *ns, unsigned int quant) {
    for(unsigned int i = 0; i < quant; ++i) {
        unsigned int n = ns[i];
        char filename[64];
        sprintf(filename, "input_%u-i.txt", n);

        FILE *f = fopen(filename, "w");
        if(!f) {
            perror("fopen");
            exit(1);
        }

        fprintf(f, "%u\n", n);
        //Análogo ao gerarordenado, mas os elementos são colocados de forma inversamente ordenada
        for(unsigned int j = n; j >= 1; --j) {
            unsigned int res = (unsigned int)(((unsigned long long)j * j) / 100);
            fprintf(f, "%u\n", res);
        }
        fclose(f);
        printf("%s\n", filename);
    }
}

void geraraleatorio(unsigned int *ns, unsigned int quant) {
    //Geração de 5 arquivos diferentes com números aletários
    for(unsigned int i = 0; i < 5; ++i) {
        for(unsigned int j = 0; j < quant; ++j) {
            unsigned int n = ns[j];
            char filename[64];
            sprintf(filename, "input_%u-%u-a.txt", n, i);

            FILE *f = fopen(filename, "w");
            if(!f) {
                perror("fopen");
                exit(1);
            }
            fprintf(f, "%u\n", n);
            //Variáveis para armazenar o maior valor e o índice que o contém
            unsigned int maxVal = 0;
            unsigned int maxIndex = 0;

            for(unsigned int k = 0; k < n; ++k) {
                //Função rand da stdlib retorna um valor aleatório.
                unsigned int val = rand() % (n * 10);
                fprintf(f, "%u\n", val);

                if(k == 0 || val > maxVal) {
                    maxVal = val;
                    maxIndex = k;
                }
            }
            fclose(f);
            //Retorno ao usuário do ínidice do maior valor do arquivo para uso no radixSort
            //numa situação real, teríamos que percorrer o vetor pra achar o índice do maior pro radix funcionar
            printf("%s INDICE DO MAIOR: %u\n", filename, maxIndex);
        }
    }
}