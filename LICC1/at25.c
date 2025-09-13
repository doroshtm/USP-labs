#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 10001

int main (void) {
    char *s = (char *)calloc(MAX,sizeof(char));
    char *t = (char *)calloc(MAX,sizeof(char));
    char *prefixo = (char *)calloc(MAX,sizeof(char));
    scanf("%s %s",s,t);

    int count = 0, countin = 0, precount = 0;

    for(int i = 0; i < strlen(s); ++i) {
        if(s[i] != t[countin]) {
            if(countin!=0) {
                i = precount+1;
            }
            precount = i;
            countin = 0;
        }
        if(s[i] == t[countin]) {
            prefixo[countin] = s[i];
            ++countin;
            if(countin > count) {
                ++count;
            }
        }
    }

    printf("%d %s", count, prefixo);

    free(s);
    free(t);
    free(prefixo);

}