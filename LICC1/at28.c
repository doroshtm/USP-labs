#include <stdio.h>

int main(void) {
    char file[100];
    scanf("%s", file);
    FILE *arquivo = fopen(file, "r");

    int count = 0;
    char ch;
    while ((ch = fgetc(arquivo)) != EOF) {
        count++;
    }

    printf("%d", count);
    fclose(arquivo);
}