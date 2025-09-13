#include <stdio.h>

int fast_power(int base, unsigned int exponent, int mod) {
    int result = 1;

    while (exponent > 0) {
        if (exponent % 2 == 1) {           // Se o bit atual do expoente for 1
            result = (result * base) % mod;
        }
        base = (base * base) % mod;        // Eleva base ao quadrado
        exponent = exponent / 2;           // Desloca o expoente para a direita
    }

    return result;
}

int main() {
    int n;
    unsigned int k;
    scanf("%d %u", &n, &k);

    int result = fast_power(n, k, 1000);

    // Imprime ignorando zeros à esquerda
    printf("%d\n", result);

    return 0;
}
