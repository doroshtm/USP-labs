#include<stdio.h>

#define pi 3.14
int main() {
    // m, m, kg/m³, kg, kg, m³
    float diametro, altura, densidade, massaDesejada, massaReal, volume;

    scanf("%f %f %f %f",&diametro,&altura,&densidade,&massaDesejada);

    volume = pi*(diametro/2)*(diametro/2)*altura;
    massaReal = volume*densidade;

    printf("Massa obtida: %f toneladas\n",massaReal/1000);

    if(massaDesejada*1.05 >= massaReal && massaDesejada*0.95 <= massaReal) {
        printf("OK!");
    } else {
        printf("FALSO!");
    }
}