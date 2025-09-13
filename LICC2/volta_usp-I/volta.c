// Gabriel Carraro Salzedas
// Arthur de Castro Dias

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(void) {
    char buffer[1024];
    int countUsp[1000] = {0}, countExterno[1000] = {0};

    int tusp = 0, texterno = 0;
    while(fgets(buffer, sizeof(buffer), stdin)) {
        int len = strlen(buffer);

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
    
    printf("USP - [");
    for(int i = 0; i < tusp; ++i) {
        printf("%d", countUsp[i]);
        if(i < tusp - 1) {
            printf(", ");
        }
    }
    printf("]\nExterna - [");
    for(int i = 0; i < texterno; ++i) {
        printf("%d", countExterno[i]);
        if(i < texterno - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}