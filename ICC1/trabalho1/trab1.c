#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// definindo a constante pi
#define pi 3.141592

// definindo n como uma variável global para facilitar o acesso
long long n;

// definindo as duas funções que serão utilizadas no cálculo da DCT - uma para a DCT em si e outra para calcular os coeficientes aij
// como ambas retornam mais de um valor, optei por usar ponteiros para retornar os valores ao invés de variáveis globais para manter o código mais limpo
void DCTbidimensional(double matriz[][n], double dct[][n]);
void aij(int, int, double*, double*);

int main(void) {
    scanf("%lld", &n);

    // definindo as matrizes de entrada e saída
    double matriz[n][n];
    double dct[n][n];

    // lendo a matriz de entrada com os valores inseridos pelo usuário
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%lf", &matriz[i][j]);
        }
    }

    // a partir da matriz de entrada, chamamos a função para calcular a DCT bidimensional e armazenar o resultado na matriz dct
    // não é necessário retornar nada, pois a matriz dct é passada por referência e será alterada diretamente
    DCTbidimensional(matriz, dct);

    // imprimindo a matriz resultante da DCT
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%9.3lf ", dct[i][j]);
        }
        printf("\n");
    }

    return 0;
}


void DCTbidimensional(double matriz[][n], double dct[][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double ai, aj;

            // chamando a função aij para calcular os coeficientes aij
            aij(i, j, &ai, &aj);

            // calculando a DCT bidimensional através da fórmula - inicializado para zero para poder somar os valores
            dct[i][j] = 0.0;
            for (int x = 0; x < n; ++x) {
                for (int y = 0; y < n; ++y) {
                    dct[i][j] += matriz[x][y] * cos((2 * x + 1) * i * pi / (2 * n)) * cos((2 * y + 1) * j * pi / (2 * n));
                }
            }
            dct[i][j] *= ai * aj;
        }
    }
}

void aij(int i, int j, double* ai, double* aj) {
    *ai = (i == 0) ? sqrt(1.0 / n) : sqrt(2.0 / n);
    *aj = (j == 0) ? sqrt(1.0 / n) : sqrt(2.0 / n);
}