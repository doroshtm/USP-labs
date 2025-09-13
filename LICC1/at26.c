#include<stdio.h>
#include<string.h>

struct Data {
    int dia;
    int mes;
    int ano;
};

struct Hora {
    int hora;
    int minuto;
    int segundo;
};


struct Dia {
    struct Data data;
    struct Hora hora;
    char titulo[100];
};

int main (void) {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        struct Dia day;
        char tit[100];
        int dia,mes,ano,hora,minuto,segundo;

        scanf("%d",&dia);
        scanf("%d",&mes);
        scanf("%d",&ano);
        scanf("%d",&hora);
        scanf("%d",&minuto);
        scanf("%d",&segundo);
        while(1) {
            char c = getchar();
            if(c == '\n' || c == EOF) {
                break;
            }
        }
        fgets(tit,100,stdin);
        
        day.data.dia = dia;
        day.data.mes = mes;
        day.data.ano = ano;
        day.hora.hora = hora;
        day.hora.minuto = minuto;
        day.hora.segundo = segundo;
        strcpy(day.titulo,tit);

        printf("%02d/%02d/%d - %02d:%02d:%02d\n",day.data.dia,day.data.mes,day.data.ano,day.hora.hora,day.hora.minuto,day.hora.segundo);
        printf("%s",day.titulo);

    }
    
}