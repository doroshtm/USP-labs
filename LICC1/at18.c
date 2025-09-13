#include<stdio.h>
#include<math.h>

double distanciaEuclidiana(int, double[][2]);

int main(void) {
    int N;
    scanf("%d",&N);
    
    double pontos[N][2];
    double dist = 0;

    dist = distanciaEuclidiana(N,pontos);
    printf("%.4lf\n",dist);
}


double distanciaEuclidiana(int quant, double pontos[][2]) {
    double dist = 0;

    for (int i = 0; i < quant; ++i) {
        scanf("%lf%lf", &pontos[i][0], &pontos[i][1]);
        if(i>0) {
            dist += sqrt(pow((pontos[i][0] - pontos[i-1][0]),2) + pow((pontos[i][1] - pontos[i-1][1]),2));
        }
    }

    return dist;
}