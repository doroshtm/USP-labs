#include<stdio.h>
#include<stdlib.h>

void estendido(unsigned int, unsigned int, long long*);
int main () {
    unsigned int d,a;
    printf("Insira o d e depois o número a ser invertido: ");
    scanf("%u %u", &d, &a);
    long long *mcd = (long long*) malloc(3 * sizeof(long long));
    mcd[0] = 0;
    estendido(d,a,mcd);
    if(mcd[0] != 1) {
        printf("O número %u não é invertível módulo %u\n", a, d);
    } else {
        long long inverso = mcd[2];
        if(inverso < 0) {
            inverso += d;
        }
        printf("O inverso de %u módulo %u é %u\n", a, d, inverso);
    }

    free(mcd);

    return 0;

}

void estendido(unsigned int d, unsigned int a, long long* mcd) {
    // parando antes porque só nos importa o caso em que o mdc é 1
    if(d % a == 0) {
        mcd[0] = a;
        mcd[1] = 0;
        mcd[2] = 1;
        return;
    }
    
    estendido(a, d % a, mcd);
    if(mcd[0] == 1) {
        long long temp = mcd[1];
        mcd[1] = mcd[2]; 
        mcd[2] = temp - (d / a) * mcd[2];
    }

    return;
}