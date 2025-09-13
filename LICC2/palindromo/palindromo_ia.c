#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {
    char buffer[1024];

    // lê cada linha até EOF
    while (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        // remove o newline, se existir
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[--len] = '\0';
        }

        // constrói uma versão só com alfanuméricos em minúsculas
        char cleaned[1024];
        size_t k = 0;
        for (size_t i = 0; i < len; i++) {
            unsigned char c = buffer[i];
            if (isalnum(c)) {
                cleaned[k++] = tolower(c);
            }
        }
        cleaned[k] = '\0';

        // considera palíndromo se tiver até 1 caractere
        if (k <= 1) {
            printf("Sim\n");
            continue;
        }

        // testa de ponta a ponta
        size_t left = 0, right = k - 1;
        int is_palindrome = 1;
        while (left < right) {
            if (cleaned[left] != cleaned[right]) {
                is_palindrome = 0;
                break;
            }
            left++;
            right--;
        }

        if (is_palindrome) {
            printf("Sim\n");
        } else {
            printf("Não\n");
        }
    }

    return 0;
}
