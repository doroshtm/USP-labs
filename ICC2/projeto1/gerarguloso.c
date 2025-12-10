#include <stdio.h>
#include <stdlib.h>

// typedef struct { 
//     unsigned long long n;
//     unsigned long long W;
// } Linha;

int main(void) {
    unsigned long long ns[] = {2, 20, 32, 50, 63, 256, 1000, 2048, 5000, 8192, 250000, 400000, 700000, 1000000};
    int quantidade = sizeof(ns)/sizeof(ns[0]);

    unsigned long long linhas[][2] = {
        {2ULL,      1000000ULL},
        {20ULL,     700000ULL},
        {32ULL,     400000ULL},
        {50ULL,     250000ULL},
        {63ULL,     8192ULL},
        {256ULL,    5000ULL},
        {1000ULL,   2048ULL},
        {2048ULL,   1000ULL},
        {5000ULL,   256ULL},
        {8192ULL,   63ULL},
        {250000ULL, 50ULL},
        {400000ULL, 32ULL},
        {700000ULL, 20ULL},
        {1000000ULL,2ULL}
    };
        


    int linhaquantidade = sizeof(linhas)/sizeof(linhas[0]);

    for(int i = 0; i < quantidade; ++i) {
        unsigned long long n = ns[i];

        unsigned long long W = 0;
        for(int j = 0; j < linhaquantidade; ++j) {
            if(linhas[j][0] == n) {
                W = linhas[j][1];
                break;
            }
        }

        if(W == 0) {
            W = n * 10ULL;
        }

        char filename[64];
        sprintf(filename, "input_g_%llu.txt", n);

        FILE *f = fopen(filename, "w");
        if(!f) {
            return 1;
        }

        fprintf(f, "%llu %llu\n", n, W);

        for(unsigned long long i = 1; i <= n; ++i) {
            fprintf(f, "%llu %llu\n", i, i*2ULL);
        }

        fclose(f);
        printf("%s (W=%llu)\n", filename, W);
    }
}
