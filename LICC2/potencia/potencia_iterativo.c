//Gabriel Carraro Salzedas
//Arthur de Castro Dias
#include <stdio.h>

int potencia(int base, int exp){
    int pot=1;
    for( int i=0; i<exp; i++){
        pot *= base;
        pot%=1000;
    }
    return pot;
}

int main(){
    int n, k;
    scanf("%d %d", &n,&k);
    printf("%d\n",potencia(n, k));
}