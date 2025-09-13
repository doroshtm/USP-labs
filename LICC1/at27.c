#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Discente {
    char nome[101];
    int nUSP;
    char assunto[101];
};

int main(void) {
    short N;
    char Nchar[50];
    fgets(Nchar, sizeof(Nchar), stdin);
    sscanf(Nchar, "%hd", &N);

    struct Discente *discentes = malloc(sizeof(struct Discente)*N);
    
    for(int i = 0; i < N; ++i) {
        fgets(discentes[i].nome, sizeof(discentes[i].nome), stdin);
        fgets(Nchar, sizeof(Nchar),stdin);
        sscanf(Nchar, "%d", &discentes[i].nUSP);
        short tam = strlen(discentes[i].nome);
        if(discentes[i].nome[tam-1] == '\n') {
            discentes[i].nome[tam-1] = '\0';
        }
        fgets(discentes[i].assunto, 100, stdin);
        tam = strlen(discentes[i].assunto);
        if(discentes[i].assunto[tam-1] == '\n') {
            discentes[i].assunto[tam-1] = '\0';
        }

        printf("Discente %d:\n", i+1);
        printf("Nome: %s\n", discentes[i].nome);
        printf("Número USP: %d\n", discentes[i].nUSP);
        printf("Assunto: %s\n\n", discentes[i].assunto);
    }

    int M;
    fgets(Nchar, sizeof(Nchar),stdin);
    sscanf(Nchar, "%d", &M);

    discentes = realloc(discentes, sizeof(struct Discente)*(N+M));
    for(int i = N; i < N+M; ++i) {
        fgets(discentes[i].nome, sizeof(discentes[i].nome), stdin);
        fgets(Nchar, sizeof(Nchar),stdin);
        sscanf(Nchar, "%d", &discentes[i].nUSP);
        short tam = strlen(discentes[i].nome);
        if(discentes[i].nome[tam-1] == '\n') {
            discentes[i].nome[tam-1] = '\0';
        }
        fgets(discentes[i].assunto, 100, stdin);
        tam = strlen(discentes[i].assunto);
        if(discentes[i].assunto[tam-1] == '\n') {
            discentes[i].assunto[tam-1] = '\0';
        }

        printf("Discente %d:\n", i+1);
        printf("Nome: %s\n", discentes[i].nome);
        printf("Número USP: %d\n", discentes[i].nUSP);
        printf("Assunto: %s\n\n", discentes[i].assunto);
    }

    free(discentes);



}