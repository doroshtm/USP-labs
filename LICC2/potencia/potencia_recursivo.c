//Gabriel Carraro Salzedas
//Arthur de Castro Dias
#include <stdio.h>

int potencia(int base, int exp){
    if(exp == 1){
        return base;
    }

    int metade = potencia(base, exp/2);
    if(exp % 2 == 0){
        return (metade * metade) % 1000;
    }else{
        return (metade * metade * base) % 1000;
    }
}

int main(){
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n",potencia(n, k));
}