#include<stdio.h>

int readInt();
double readDouble();
void printDouble(double);

int main (void) {
    int n = readInt();
    double notas[n];
    for (int i = 0; i < n; ++i) {
        notas[i] = readDouble();
    }
    double media;
    for (int i = 0; i < n; ++i) {
        media += 1/(notas[i]+1);
    }
    media = n/media - 1;

    printDouble(media);
}


int readInt() {
    int n;
    scanf("%d", &n);
    return n;
}

double readDouble() {
    double nota;
    scanf("%lf", &nota);
    return nota;
}

void printDouble(double val) {
    printf("%.2lf\n", val);
}