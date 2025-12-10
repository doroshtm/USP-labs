#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void) {
    unsigned long long ns[] = {2, 20, 26, 28, 30, 31, 32, 33, 34, 50, 63, 256, 1000, 2048, 5000, 8192, 250000, 700000, 900000, 1000000};
    int qtd = sizeof(ns)/sizeof(ns[0]);

    for(int i = 0; i < qtd; ++i) {
        unsigned long long n = ns[i];
        char filename[64];
        sprintf(filename, "input_%llu.txt", n);

        FILE *f = fopen(filename, "w");
        if(!f) {
            perror("fopen");
            return 1;
        }

        unsigned long long W;
        if(n == 0) {
            W = 0;
        } else {
            double log2n = log2((double)n);
            W = (unsigned long long) floor(log2n);
        }

        fprintf(f, "%llu %llu\n", n, W);

        for(unsigned long long j = 1; j <= n; ++j) {
            fprintf(f, "%llu %llu\n", j, j * 2ULL);
        }

        fclose(f);
        printf("%s\n", filename);
    }
}
