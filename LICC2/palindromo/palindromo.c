#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

bool verificarPalindromo(char *, int);

int main() {
    char letra;
    int tam = 0;
    char *palavra = (char *)malloc(200 * sizeof(char));
    int i;
    for(i = 0; (letra = fgetc(stdin)) != EOF; ++i) {
        if(letra >= 65 && letra <= 90) {
            letra += 32;
        } else if((letra < 97 || letra > 122) && letra != 10 && (letra < 48 || letra > 57)) {
            --i;
            continue;
        }

        palavra[i] = letra;
        if(letra != '\n') {
            continue;
        }

        tam = i;
        i = -1;

        printf("%s", verificarPalindromo(palavra, tam) ? "Sim\n" : "Não\n");

        free(palavra);
        palavra = (char *)malloc(200 * sizeof(char));
    }

    printf("%s", verificarPalindromo(palavra, i) ? "Sim\n" : "Não\n");
    free(palavra);
}

bool verificarPalindromo(char *palavra, int tam) {
    if(tam < 2) {
        return 1;
    }

    for(int j = 0; j < tam/2; ++j) {
        if(palavra[j] != palavra[tam-1-j]) {
            return 0;
        }
    }
    return 1;
}