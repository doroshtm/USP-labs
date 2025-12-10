#include<stdio.h>

int numeroDeCaracteres(char str[], int ind, int cont){
    if(str[ind] == '\0'){
        return cont;
    }
    else if(str[ind] != ' '){
        cont++;
    }
    ind++;
    return numeroDeCaracteres(str, ind, cont);
}

int main(){
    char str[101], comu[10];
    int usp[100], ext[100], i=0, j=0, c;
    while(scanf("%[^-] %[^\n]", str, comu) != EOF){
        if(!strcmp(comu, "- usp")){
            usp[i] = numeroDeCaracteres(str, 0, 0);
            i++;
        }else{
            ext[j] = numeroDeCaracteres(str, 0, 0);
            j++;
        }
        while ((c = getchar()) != '\n' && c != EOF);
    }
