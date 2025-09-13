#include<stdio.h>
#include<stdbool.h>
#include<string.h>

bool palindromo_recursivo(char *, int, int);

int main() {
    char palavra[200];
    while(fgets(palavra, sizeof(palavra), stdin)) {
        printf("%s", palindromo_recursivo(palavra, 0, strlen(palavra) - 1) ? "Sim\n" : "Não\n");
    }
    return 0;
}


bool palindromo_recursivo(char *palavra, int inicio, int fim) {
    while(palavra[inicio] && (palavra[inicio] < 97 || palavra[inicio] > 122) && (palavra[inicio] < 48 || palavra[inicio] > 57) && (palavra[inicio] < 65 || palavra[inicio] > 90)) {
        ++inicio;
    }
    while(palavra[fim] && (palavra[fim] < 97 || palavra[fim] > 122) && (palavra[fim] < 48 || palavra[fim] > 57) && (palavra[fim] < 65 || palavra[fim] > 90)) {
        --fim;
        if(fim < 0) {
            break;
        }
    }
    if(fim < 0) {
        fim = 0;
    }
    if(inicio >= fim) {
        return true;
    }

    if(palavra[inicio] >= 65 && palavra[inicio] <= 90) {
        palavra[inicio] += 32;
    }
    if(palavra[fim] >= 65 && palavra[fim] <= 90) {
        palavra[fim] += 32;
    }

    if(palavra[inicio] != palavra[fim]) {
        return false;
    }

    return palindromo_recursivo(palavra, inicio + 1, fim - 1);
}