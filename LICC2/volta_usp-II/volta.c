// Gabriel Carraro Salzedas
// Arthur de Castro Dias

#include<stdio.h>
#include<stdbool.h>

int main(void) {
    char buffer[1024];
    long countUsp[75000] = {0}, countExterno[75000] = {0};

    int tusp = 0, texterno = 0;
    while(fgets(buffer, sizeof(buffer), stdin)) {
        int count = 0;

        int i;
        for(i = 0; buffer[i] != '-' && buffer[i] != '\0'; ++i) {
            if(buffer[i] == ' ') {
                continue;
            }
            ++count;
        }
        
        
        if(buffer[i+2] == 'u') {
            countUsp[tusp] = count;
            ++tusp;
        } else {
            countExterno[texterno] = count;
            ++texterno;
        }
    }

    int quantComp = 0, quantTrocas = 0;
    int n = tusp;
    while(n-- > 1) {
        for(int i = 0; i < n; ++i, ++quantComp) {
            if(countUsp[i] > countUsp[i+1]) {
                int temp = countUsp[i];
                countUsp[i] = countUsp[i+1];
                countUsp[i+1] = temp;
                ++quantTrocas;
            }
        }
    };
        

    printf("USP - [");
    for(int i = 0; i < tusp; ++i) {
        printf("%d", countUsp[i]);
        if(i < tusp - 1) {
            printf(", ");
        }
    }
    printf("]\nComparações: %d, Trocas: %d\n", quantComp, quantTrocas);
    n = texterno;
    quantComp = 0, quantTrocas = 0;
    while(n-- > 1) {
        for(int i = 0; i < n; ++i, ++quantComp) {
            if(countExterno[i] > countExterno[i+1]) {
                int temp = countExterno[i];
                countExterno[i] = countExterno[i+1];
                countExterno[i+1] = temp;
                ++quantTrocas;
            }
        }
    };

    printf("\nExterna - [");
    for(int i = 0; i < texterno; ++i) {
        printf("%d", countExterno[i]);
        if(i < texterno - 1) {
            printf(", ");
        }
    }
    printf("]\nComparações: %d, Trocas: %d\n", quantComp, quantTrocas);



}