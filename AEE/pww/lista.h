#ifndef LISTA_H
    #define LISTA_H

    typedef struct no_ NO;

    typedef struct lista_ LISTA;

    LISTA* lista_criar();
    void lista_inserir(LISTA* lista, int valor);
    void lista_imprimir(LISTA* lista);
    void lista_liberar(LISTA* lista);

#endif
