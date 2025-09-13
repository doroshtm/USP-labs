#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 157

int main(void) {
    short N;
    scanf("%hd", &N);
    while(1) {
        char c = getchar();
        if(c == '\n' || c == EOF) {
            break;
        }
    }
    char **livros = calloc(N, sizeof(char *));
    short *quant = calloc(N, sizeof(short));
    for(short i = 0; i < N; ++i) {
        short charcount = 0;
        livros[i] = malloc(sizeof(char));
        char c;
        while ((c = getchar()) != '\n' && c != EOF) {
            ++charcount;
            livros[i] = realloc(livros[i], (charcount + 1) * sizeof(char)); 
            livros[i][charcount - 1] = c;
        }
        if(livros[i][charcount-1] == '\r') {
            livros[i][charcount-1] = '\0';
        }
        livros[i][charcount] = '\0';
        
        for(short j = 0; j < i; ++j) {
            if(livros[j] != NULL && strcmp(livros[i], livros[j]) == 0) {
                ++quant[j];
                free(livros[i]);
                livros[i] = NULL;
                break;
            }
        }
        if(livros[i] != NULL) {
            quant[i] = 1;
        }
    }
    printf("Catalogo de Livros:");
    short countUnico = 0;
    for(short i = 0; i < N; ++i) {
        if(livros[i] == NULL) {
            continue;
        }
        printf("\nLivro %d: \nTitulo: ", countUnico+1);
        short count = 0;
        while(1) {
            char c = livros[i][count];
            ++count;
            if(c == ',' || c == '\0')
                break;
            printf("%c", c);
        }
        ++count;
        printf("\nAutor: ");
        while(1) {
            char c = livros[i][count];
            ++count;
            if(c == ',' || c == '\0')
                break;
            printf("%c", c);
        }
        ++count;
        printf("\nAno: ");
        for(short max = count+4; count < max; ++count) {
            printf("%c", livros[i][count]);
        }
        printf("\nQuantidade: %d\n", quant[i]);
        ++countUnico;
    }
    for (short i = 0; i < N; ++i) {
        if(livros[i] != NULL) {
            free(livros[i]);
        }
    }
    free(livros);
    free(quant);
    return 0;
}
