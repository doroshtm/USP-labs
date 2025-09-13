#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 101
int main(void) {
    int n, b;
    scanf("%d %d", &n, &b);
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    char *s = (char *)malloc(MAX * sizeof(char));
    for(int i = 0; i < n; ++i) {
        fgets(s, MAX, stdin);
        if(s[strlen(s) - 1] == '\n') {
            s[strlen(s) - 1] = '\0';
        }
        if(b == 0) {
            for(int j = 0; s[j] != '\0'; ++j) {
                if(s[j] >= 65 && s[j] <= 90) {
                    s[j] = s[j] + 32;
                }
            }
        } else {
            for(int j = 0; s[j] != '\0'; ++j) {
                if(s[j] >= 97 && s[j] <= 122) {
                    s[j] = s[j] - 32;
                }
            }
        }
        printf("%s\n", s);
    }
    free(s);
}