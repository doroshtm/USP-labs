#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char file[100];
    scanf("%s ", file);
    FILE *arquivo = fopen(file, "a+");
    char linha[50];
    while(!feof(stdin)){
        char ope[3];
        for (int j = 0; j < 3; ++j) {
            ope[j] = getchar();
        }
        getchar();
        fgets(linha, sizeof(linha), stdin);
        if (ope[0] == 'A') {
            linha[strcspn(linha, "\n")] = 0; 
            fputs("\n", arquivo);
            fputs(linha, arquivo);
        } else if (ope[0] == 'D') {
            int linhapos = atoi(linha);
            char buffer[2000];
            int count = 0;
            FILE *temp = fopen("temp.txt", "w");
            while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
                if (count != linhapos) {
                    buffer[strcspn(buffer, "\n")] = 0; 
                    if (count != 0 && !(count == 1 && linhapos == 0)) {
                        fputs("\n", temp);
                    }
                    fputs(buffer, temp);
                }
                ++count;
            }
            fclose(arquivo);
            fclose(temp);
            remove(file);
            rename("temp.txt", file);
            arquivo = fopen(file, "a+");
        }
        rewind(arquivo);
    }

    char buffer[2000];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        fputs(buffer, stdout);
    }
    fclose(arquivo);
    return 0;
}