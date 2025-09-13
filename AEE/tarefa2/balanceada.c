#include<stdio.h>
#include"Pilha.h"

bool balanceada(const char *sequencia) {
    PILHA *p = pilha_criar();
    if (p == NULL) {
        return false;
    }

    int j = 0;

    while (sequencia[j] != '\0' && sequencia[j] != '\n') {
        int c = sequencia[j];
        ITEM *item = item_criar(c);
        if (item == NULL) {
            pilha_apagar(&p);
            return false;
        }

        if (c == '(' || c == '{' || c == '[') {
            item_set_chave(item, c);
            pilha_empilhar(p, item);
        } else if (c == ')' || c == '}' || c == ']') {
            if (pilha_vazia(p)) {
                return false;
            }

            ITEM *ultimo = pilha_desempilhar(p);

            if ((item_get_chave(ultimo) == '(' && c != ')') || (item_get_chave(ultimo) == '{' && c != '}') || (item_get_chave(ultimo) == '[' && c != ']')) {
                return false;
            }
        }
        // item_apagar(&item);
        ++j;
    }

    bool final = pilha_vazia(p);
    pilha_apagar(&p);
    return final;
}
