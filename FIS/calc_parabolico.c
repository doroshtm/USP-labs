// Igual ao calc_parabolico_logica.c em textos/estrutura, com a única diferença de usar tolerâncias para comparações de ponto flutuante
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159
#define gravidade 9.81

// Tolerâncias (diferença exclusiva desse código)
#define EPS_POS 1e-2   // tolerância para posições (m)
#define EPS_T   1e-3   // tolerância para tempos (s)

double *bhaskara(double,double,double);

int main() {
    int escolha = 7;
    printf("Todos os valores devem ser inseridos em unidades do SI (m, s, m/s, m/s²)\n");
    double Sox,Soy,Sx,Sy,Vo,ax,t,theta,Vox,Voy;
                
    do {
        switch(escolha) {
            case 7:
                printf("Digite a posição inicial no eixo x: ");
                scanf("%lf",&Sox);
                printf("Digite a posição inicial no eixo y: ");
                scanf("%lf",&Soy);
                printf("Digite a velocidade inicial: ");
                scanf("%lf",&Vo);
                printf("Digite a resistência do ar (em módulo): ");
                scanf("%lf",&ax);
                printf("Digite o ângulo de inclinação (em graus): ");
                scanf("%lf",&theta);

                theta *= (PI/180);
                Vox = Vo*cos(theta);
                Voy = Vo*sin(theta);
                break;
            case 1:
                printf("Digite a posição desejada no eixo x: ");
                scanf("%lf",&Sx);
                printf("Digite a posição desejada no eixo y: ");
                scanf("%lf",&Sy);

                // Calcula tempos candidatos pelo eixo X
                double *raizesX = bhaskara(-ax/2,Vox,Sox-Sx);
                if (raizesX == NULL) {
                    printf("Não foi possível calcular o tempo para a posição x desejada.\n");
                    break;
                }
                double t1 = raizesX[0];
                double t2 = raizesX[1];
                free(raizesX);

                int found = 0;
                double t_sol2 = -1;

                // Verifica se algum tempo de X bate com Sy (com tolerância)
                double cand[2] = {t1, t2};
                for (int i = 0; i<2; ++i) {
                    double ti = cand[i];
                    if (ti < 0) {
                        continue;
                    }
                    double yti = Soy + Voy*ti - gravidade*ti*ti/2;
                    if (fabs(yti - Sy) <= EPS_POS) {
                        found = 1;
                        t_sol2 = ti;
                        break;
                    }
                }

                if (found) {
                    printf("O tempo para chegar na posição desejada é: %.2f segundos\n",t_sol2);
                } else {
                    printf("Não foi possível encontrar um tempo válido para a posição desejada.\n\n");
                }
                break;

            case 2:
                printf("Digite o tempo desejado: ");
                scanf("%lf",&t);
                
                Sx = Sox + Vox*t + (-ax*t*t)/2;
                Sy = Soy + Voy*t + (-gravidade*t*t)/2;
                printf("A posição no tempo %.2f segundos é: (%.2f, %.2f)\n\n",t,Sx,Sy);

                break;
            case 3:
                printf("Digite a posição desejada no eixo x: ");
                scanf("%lf",&Sx);
                printf("Digite a posição desejada no eixo y: ");
                scanf("%lf",&Sy);

                double Vx,Vy,V;
                double t_sol = -1;

                // Resolve pelo eixo X e valida com o eixo Y (com tolerância)
                double *raizesX2 = bhaskara(-ax/2,Vox,Sox-Sx);
                if (raizesX2 != NULL) {
                    double t1 = raizesX2[0];
                    double t2 = raizesX2[1];
                    free(raizesX2);

                    double cand[2] = {t1,t2};
                    for (int i = 0; i<2; ++i) {
                        double ti = cand[i];
                        if (ti < 0) continue;
                        double yti = Soy + Voy*ti - gravidade*ti*ti/2;
                        if (fabs(yti - Sy) <= EPS_POS) {
                            t_sol = ti;
                            break;
                        }
                    }
                }

                if (t_sol < 0) {
                    printf("Não foi possível determinar um tempo que satisfaça (Sx, Sy) simultaneamente.\n");
                    break;
                }

                Vx = Vox + (-ax)*t_sol;
                Vy = Voy + (-gravidade)*t_sol;
                V = sqrt(Vx*Vx + Vy*Vy);

                printf("A velocidade na posição (%.2f, %.2f) é: %.2f m/s.\nNo eixo x, temos: %.2f m/s; no eixo y, temos: %.2f m/s\n\n",Sx,Sy,V,Vx,Vy);
                break;

            case 4:
                printf("Digite o tempo desejado: ");
                scanf("%lf", &t);
                double Vx2, Vy2, V2;
                Vx2 = Vox + (-ax)*t;
                Vy2 = Voy + (-gravidade)*t;

                V2 = sqrt(Vx2*Vx2 + Vy2*Vy2);
                printf("A velocidade no tempo %.2f segundos é: %.2f m/s.\nNo eixo x, temos: %.2f m/s; no eixo y, temos: %.2f m/s\n\n",t,V2,Vx2,Vy2);
                break;
            case 5:
                printf("Digite as informações do segundo movimento:\n");
                double Sox2,Soy2,Vo2,ax2,theta2,Vox2,Voy2;
                printf("Digite a posição inicial no eixo x: ");
                scanf("%lf",&Sox2);
                printf("Digite a posição inicial no eixo y: ");
                scanf("%lf",&Soy2);
                printf("Digite a velocidade inicial: ");
                scanf("%lf",&Vo2);
                printf("Digite a resistência do ar (em módulo): ");
                scanf("%lf",&ax2);
                printf("Digite o ângulo de inclinação (em graus): ");
                scanf("%lf",&theta2);
                theta2 *= (PI/180);
                Vox2 = Vo2*cos(theta2);
                Voy2 = Vo2*sin(theta2);

                double t_sol3 = -1;

                double *raizesX3 = bhaskara((ax2-ax)/2,(Vox-Vox2), (Sox-Sox2));
                if (raizesX3 != NULL) {
                    double candX[2] = {raizesX3[0],raizesX3[1]};
                    free(raizesX3);

                    for (int i = 0; i<2; ++i) {
                        double ti = candX[i];
                        if (ti<0){
                            continue;
                        }

                        double y1 = Soy + Voy*ti - gravidade*ti*ti/2;
                        double y2 = Soy2 + Voy2*ti - gravidade*ti*ti/2;

                        if (fabs(y1 - y2) <= EPS_POS) {
                            t_sol3 = ti;
                            break;
                        }
                    }
                }

                if (t_sol3 >= 0) {
                    printf("O tempo para o encontro dos dois movimentos é: %.2f segundos\n",t_sol3);
                } else {
                    printf("Não foi possível encontrar um tempo válido para o encontro dos dois movimentos.\n\n");
                }
                break;

            case 6:
                if (Voy <= 0) {
                    printf("O movimento não possui subida (Voy <= 0).\n");
                    break;
                }
                // Tempo até o ponto mais alto: Vy = 0
                t = Voy / gravidade;

                // Posição nesse instante
                Sx = Sox + Vox*t +(-ax*t*t)/2;
                Sy = Soy + Voy*t - (gravidade*t*t)/2;

                printf("Ponto mais alto atingido em %.2f segundos.\n",t);
                printf("Posição no ponto mais alto: (%.2f, %.2f)\n",Sx,Sy);
                break;

            case 0:
                return 1;
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
        printf("\n\n");

        printf("Escolha uma opção:\n");
        printf("1 - Calcular o tempo para chegar em uma posição\n");
        printf("2 - Calcular a posição em um determinado tempo\n");
        printf("3 - Calcular a velocidade em uma determinada posição\n");
        printf("4 - Calcular a velocidade em um determinado tempo\n");
        printf("5 - Calcular o ponto de encontro entre dois movimentos\n");
        printf("6 - Calcular o ponto mais alto\n");
        printf("7 - Digitar novos valores\n");
        printf("0 - Sair\n");

        scanf("%d",&escolha);
    }while(escolha != 0);
}

double *bhaskara(double a, double b, double c) {
    // Caso linear com tolerância robusta
    if (fabs(a) < 1e-8) {
        if (fabs(b) < 1e-12) {
            return NULL; // sem solução
        }
        double *raizes = (double*)malloc(2 * sizeof(double));
        double root = -c / b;
        raizes[0] = root;
        raizes[1] = root;
        return raizes;
    }

    double delta = b*b - 4.0*a*c;

    // Tolerância relativa de escala para delta (mais robusta numericamente)
    double scale = b*b + fabs(4*a*c) + 1.0;
    double delta_tol = 1e-6 * scale;

    if (delta < -delta_tol) {
        printf("Não existem raízes reais.\n");
        return NULL;
    }

    double *raizes = (double*)malloc(2 * sizeof(double));

    if (fabs(delta) <= delta_tol) {
        double root = -b / (2*a);
        raizes[0] = root;
        raizes[1] = root;
    } else {
        double sqrt_delta = sqrt(fmax(delta, 0));
        // Fórmula numericamente estável
        double q = -0.5 * (b + copysign(1.0, b) * sqrt_delta);
        double r1 = q / a;
        double r2 = c / q;
        // Ordena para consistência
        if (r1 <= r2) { 
            raizes[0] = r1; raizes[1] = r2;
        }
        else {
            raizes[0] = r2; raizes[1] = r1;
        }
    }
    return raizes;
}
