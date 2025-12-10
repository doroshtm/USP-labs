#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>

void bubblesort(int *, unsigned int);
void selectionsort(int *, unsigned int);
void insertionsort(int *, unsigned int);
void shellsort(int *, unsigned int);
void quicksort(int *, unsigned int, unsigned int);
void heapsort(int *, unsigned int);
void rearranjar_heap(int *, unsigned int, unsigned int);
void mergesort(int *, unsigned int);
void contagem_menores(int *, unsigned int);
void radixsort(int *, unsigned int, unsigned int);
void copiarvetores(int *, int *, unsigned int);

unsigned long long nComparacoes, nMovimentacoes;

int main(void) {
    unsigned int n;
    //Recebe o tamanho do vetor
    scanf("%u",&n);
    //Cria um vetor com o tamanhho lido
    int *v = malloc(n*sizeof(int));
    //Tratamento de falha na alocação de v
    if(v == NULL) {
        return 1;
    }
    //Alocação de vetor auxiliar v2
    int *v2 = malloc(n*sizeof(int));
    //Tratamento de falha na alocação de v2
    if(v2 == NULL) {
        free(v);
        return 1;
    }
    unsigned int maior = 0;
    //Os vetores v e v2 são populados e durante a montagem deles
    //É encontrado o maior elemento de entrada.
    for(unsigned int i = 0; i<n; ++i) {
        scanf("%d",&v[i]);
        v2[i] = v[i];
        if(v[i] > v[maior]) {
            maior = i;
        }
    }
    clock_t inicio = clock();

    radixsort(v2, n, 50183);

    clock_t fim = clock();
    double tempo_execucao = (double)(fim - inicio) / CLOCKS_PER_SEC;
    copiarvetores(v, v2, n);
    // selectionsort(v2, n);
    // copiarvetores(v, v2, n);
    // insertionsort(v2, n);
    // copiarvetores(v, v2, n);
    // shellsort(v2, n);
    // copiarvetores(v, v2, n);
    // quicksort(v2, 0, n-1);
    // copiarvetores(v, v2, n);
    // heapsort(v2, n);
    // copiarvetores(v, v2, n);
    // mergesort(v2, n);
    // copiarvetores(v, v2, n);
    // contagem_menores(v2, n);
    // copiarvetores(v, v2, n);
    // radixsort(v2, n);
    for(int i = 0; i < n; ++i) {
        printf("%d\t", v[i]);
    }
    printf("\n\n%llu %llu %lf", nComparacoes, nMovimentacoes, tempo_execucao);
}

//O BubbleSort utilizado foi o Bubblesort aprimorado
void bubblesort(int *v, unsigned int n) {
    //Uso de uma flag para ver se houve trocas de elementos
    bool trocou = 1;
    for(unsigned int i = 0; i<n-1 && trocou; ++i) {
        //Definição da flag como 0, assim se nenhuma troca for feita o for mais
        //externo é encerrado
        trocou = 0;
        for(unsigned int j = 0; j<n-i-1; ++j) {
            ++nComparacoes;
            //Se o elemento atual for maior que o próximo o vetor está desordenado
            //é feita a troca dos elementos
            if(v[j]>v[j+1]) {
                int temp = v[j];
                v[j] = v[j+1];
                v[j+1] = temp;
                nMovimentacoes += 3;
                trocou = 1;
            }
        }
    }
}

void selectionsort(int *v, unsigned int n) {
    for(unsigned int i = 0; i<n-1; ++i) {
        unsigned int min = i;
        //Procura o menor elemento do vetor.
        for(unsigned int j = i+1; j<n; ++j) {
            ++nComparacoes;
            if(v[j]<v[min]) {
                min = j;
            }
        }
        //Se o menor elemento não for igual ao i ele troca as duas posições
        //Assim os menores valores são colocadas nas primeiras posições a cada
        //passada do loop.
        if(i!=min) {
            int temp = v[i];
            v[i] = v[min];
            v[min] = temp;
            nMovimentacoes += 3;
        }
    }
}

void insertionsort(int *v, unsigned int n) {
    for(unsigned int i = 1; i<n; ++i) {
        int temp = v[i];
        unsigned int j = i;
        //Executa o while até que o vetor seja inteiramente percorrido
        //ou ache elementos ordenados. Durante o for ele vai trocando
        //a posição do elemento com o posterior e no fim, o elemento desordenado vai para
        //a posisção correta em relaçaõ aos elementos posteriores.
        while (j > 0) {
            ++nComparacoes;
            if (temp < v[j-1]) {
                v[j] = v[j-1];
                ++nMovimentacoes;
                --j;
            } else {
                break;
            }
        }
        v[j] = temp;
        ++nMovimentacoes;
    }
}

void shellsort(int *v, unsigned int n) {
    //For seguindo a sequência de decrementos 
    //com cada decremento sendo metade do anterior
    for(unsigned int h = n/2; h>0; h /= 2) {
        //Análise dos elementos anteriores a temp
        //com intervalo de h itens entre eles
        for(unsigned int i = h; i<n; ++i) {
            int temp = v[i];
            unsigned int j = i;
            while (j >= h) {
                ++nComparacoes;
                if (v[j-h] > temp) {
                    v[j] = v[j-h];
                    ++nMovimentacoes;
                    j -= h;
                } else {
                    break;
                }
            }
            //Ao final v[j] recebe o elemento de temp
            //Posicionando-o de forma ordenada em relação aos
            //demais itens do vetor que foram comparados na iteração
            v[j] = temp;
            ++nMovimentacoes;
        }
    }
}

void quicksort(int *v, unsigned int esq, unsigned int dir) {
    //Caso base da recursão, aqui é quando os indicadores
    //da direita e daesquerda se invertem ou se igualam
    if (esq >= dir) {
        return;
    }

    unsigned int i = esq, j = dir;
    unsigned int meio = (esq + dir) / 2;

    //Tratamento pré-execução para usar mediana de três elementos
    //do vetor como pivô
    if (v[esq] > v[meio]) {
        int temp = v[esq];
        v[esq] = v[meio];
        v[meio] = temp;
        nMovimentacoes += 3;
    }

    if (v[esq] > v[dir]) {
        int temp = v[esq];
        v[esq] = v[dir];
        v[dir] = temp;
        nMovimentacoes += 3;
    }

    if (v[meio] > v[dir]) {
        int temp = v[meio];
        v[meio] = v[dir];
        v[dir] = temp;
        nMovimentacoes += 3;
    }

    nComparacoes += 3;

    //Definição do pivô como elemento do meio do vetor
    int pivo = v[meio];

    do {
        //procura um elemento maior ou igual ao pivô
        while (v[i] < pivo) {
            ++nComparacoes;
            ++i;
        }
        ++nComparacoes;

        //procura um elemento menor ou igual ao pivô
        while (v[j] > pivo) {
            ++nComparacoes;
            --j;
        }
        ++nComparacoes;

        //Verifica se os índices não se inverteram, pois isso
        //trocaria elementos que já estão em sua ordem correta
        ++nComparacoes;
        if (i <= j) {
            //Caso o i seja menor que o j ele inverte, impede que haja a troca
            //caso ambos tenham o mesmo valor, porque trocaria o mesmo elemento
            //consigo mesmo, apenas gastando tempo de execução
            if (i < j) {
                int temp = v[i];
                v[i] = v[j];
                v[j] = temp;
                nMovimentacoes += 3;
            }
            ++i;
            //Se o j alcançou o primeiro elemento do vetor o do-while termina
            if (j == 0) {
                break;
            }
            --j;
        }
    } while (i < j);

    //Se o j for maior que esq, ainda há subvetores que podem estar desordenados
    //então chama novamente a função agora com dir sendo j.
    if (j > esq) {
        quicksort(v, esq, j);
    }
    //Se o i for menor que dir, ainda há subvetores que podem estar desordenados
    //então chama novamente a função agora com esq sendo i.
    if (i < dir) {
        quicksort(v, i, dir);
    }
}

void copiarvetores(int *destino, int *origem, unsigned int n) {
    for(unsigned int i = 0; i<n; ++i) {
        destino[i] = origem[i];
    }
}

//Objetivo é manter um heap máximo seguindo a estrutura correta
//Onde a raiz é o maior valor e cada pai é maior que seus filhos
void rearranjar_heap(int *v, unsigned int i, unsigned int n) {
    
    //esq e dir seguem as equações para acessar os filhos de um nó
    //esquerdo e direito respectivamente
    unsigned int esq=2*i+1, dir=esq+1, maior = i;
    int temp;

    //Se o filho esquerdo for maior que o pai, ele altera o valor de maior
    //para o índice esq
    if (esq < n && v[esq] > v[maior]) {
        maior = esq;
    }

    //Se o filho direito for maior que o elemento no índice
    //representado por maior, então ele altera o valor de maior
    if (dir < n && v[dir] > v[maior]) {
        maior = dir;
    }

    //Se maior for diferente de i o pai não é maior que seus filhos, então ele troca
    //Com o que estiver no índice da variável maior.
    if (maior != i) {
        temp = v[i];
        v[i] = v[maior];
        v[maior] = temp;
        nMovimentacoes += 3;
        //A função é chamada novamente até que o pai analisado
        //Seja maior que seus filhos, assim a subheap que
        //o algoritmo analisa termina seguindo a estrutura correta
        rearranjar_heap(v, maior, n);
    }

    nComparacoes += 3;
}

void heapsort(int *v, unsigned int n) {
    
    //Como i é decrementado dentro da parte da condição do for
    //ele entra na primeira iteração valendo n/2-1
    //essa posição marca o último nó antes das folhas,
    //assim a heap vai se ordenando de forma ascendente
    //Até que a estrutura de heap máximo esteja completa.
    for (unsigned int i = n/2; i-- > 0;) {
        rearranjar_heap(v, i, n);
    }

    // Troca a raiz da árvore(maior elemento) com o do fim
    //Assim os maiores elementos são posicionados ao final do vetor
    //Ordenando-o do final para o início. A função rearranjar heap
    //garante que os elementos maiores permaneçam na raiz.
    for (unsigned int fim = n - 1; fim > 0; --fim) {
        int temp = v[0];
        v[0] = v[fim];
        v[fim] = temp;
        nMovimentacoes += 3;
        rearranjar_heap(v, 0, fim);
    }
}

//O mergeSort feito foi iterativo.
void mergesort(int *v, unsigned int n) {
    //vetor temporário para auxílio.
    int *temp = malloc(n*sizeof(int));
    //Tratamento em caso de falha na alocação de temp.
    if (temp == NULL) {
        return;
    }

    int *origem = v;
    int *destino = temp;

    // como vamos duplicando e somando a n, de tamanho unsigned int, vamos usar unsigned long long para evitar possíveis overflows
    for (unsigned long long i = 2; (i / 2) < n; i *= 2) {
        
        for (unsigned long long j = 0; j < n; j += i) {
            unsigned long long meio = j + (i / 2);
            unsigned long long final = j + i;

            if (meio > n){
                meio = n;
            }
            if (final > n) {
                final = n;
            }

            unsigned long long k = j, l = meio, m = j;
            //O vetor auxiliar recebe o menor elemento entre origem[k] e origem[l]
            //assim destino vai guardando os subvetores ordenados. Cada vez que i aumenta
            //destino tem os subvetores formados anteriormente comparados entre si, assim quando i
            //chegar em seu valor máximo, todo o vetor será montado ordenadamente

            while (k < meio && l < final) {
                ++nComparacoes;
                if (origem[k] <= origem[l]) {
                    destino[m++] = origem[k++];
                } else {
                    destino[m++] = origem[l++];
                }
                ++nMovimentacoes;
            }
            
            //Aquele while que tiver a condição atendida mostra que não foi passado
            //inteiramnete para destino, pois o loop anterior termina assim que um dos subvetores for
            //passado por inteiro, garantindo que sobrará os maiores valores no outro que não
            //foi passado por completo.
            while (k < meio) {
                ++nComparacoes;
                destino[m++] = origem[k++];
                ++nMovimentacoes;
            }
            while (l < final) {
                ++nComparacoes;
                destino[m++] = origem[l++];
                ++nMovimentacoes;
            }
            nComparacoes += 2;
        }


        //Em cada etapa (tamanho de bloco i), escrevemos os subvetores mesclados em "destino".
        //Ao finalizar a iteração, ao invés de copiar todo "destino" de volta para "origem" (custo O(n)),
        //apenas alternamos os ponteiros: "origem" passa a apontar para o buffer que acabamos de preencher
        //e "destino" para o antigo. Isso elimina cópias desnecessárias a cada iteração e mantém
        //o algoritmo iterativo eficiente.
        int *temp2 = origem;
        origem = destino;
        destino = temp2;
    }

    //Se o vetor ordenado estiver no buffer auxiliar (origem != v), fazemos uma única cópia final para ‘v’.
    if (origem != v) {
        for (unsigned int i = 0; i < n; ++i) {
            v[i] = origem[i];
            ++nMovimentacoes;
        }
    }

    free(temp);
}

void contagem_menores(int *v, unsigned int n) {
    //Definição de um vetor auxiliar para armazenar
    //a quantidade de valores menores que o analisado
    //Uso de calloc para inicializar os valores do vetor
    int *X = calloc(n,sizeof(int));
    //Tratamento para caso haja falha na alocação
    if(X == NULL) {
        return;
    }
    //Definição do segundo vetor auxiliar para
    //armazenar o vetor ordenado
    int *B = malloc(n*sizeof(int));
    //Tratamento para caso haja falha na alocação
    if(B == NULL) {
        free(X);
        return;
    }

    //Aqui o elemento no índice i é comparado com
    //os anteriores. Como a comparação vai do menor subvetor
    //até o último elemento, todos os elementos são comparados entre si
    for(unsigned int i=1; i<n; ++i) {
        for(unsigned int j=i; j>0; --j) {
            //O vetor X armazena o número de elementos menores que v[i]
            //então ele terá ao final o ínidce relativo de cada item no vetor final
            ++nComparacoes;
            if(v[i]<v[j-1]) {
                X[j-1]++;
                ++nMovimentacoes;
            } else {
                X[i]++;
                ++nMovimentacoes;
            }
        }
    }

    //O vetor B posiciona os elementos de acordo com
    //a posição deles indicada pelo vetor X.
    for(int i=0; i<n; ++i) {
        B[X[i]] = v[i];
        ++nMovimentacoes;
    }

    //Os elementos de B são copiados para v, agora
    //o vetor original está ordenado.
    for(int i=0; i<n; ++i) {
        v[i] = B[i];
        ++nMovimentacoes;
    }
    free(X);
    free(B);
}


void radixsort(int *v, unsigned int n, unsigned int maior) {
    int *v2 = malloc(n * sizeof(int));
    if (v2 == NULL) {
        return;
    }

    int *origem = v;
    int *destino = v2;
    int maxVal = v[maior];

    for (unsigned long long i = 1; i <= maxVal; i *= 10) {
        unsigned int indice[10] = {0};
        // contamos a quantidade de vezes que um dígito aparece entre os números do vetor e incrementamos em indice[dígito]
        for (unsigned int j = 0; j < n; ++j) {
            ++nComparacoes;
            ++indice[(origem[j] / i % 10)];
        }
        // fazemos tal que indice[dígito] agora representa a quantidade de vezes que o dígito e todos os dígitos menores que ele aparecem
        // isso significa que estamos guardando o índice a seguir do último índice onde um número com esse dígito deveria entrar no vetor
        for (unsigned int j = 0; j < 9; ++j) {
            ++nComparacoes;
            indice[j + 1] += indice[j];
            ++nMovimentacoes;
        }
        // guardamos em v2 em ordem decrescente para que possamos garantir que a ordenação será estável, um fator necessário para o radix funcionar corretamente
        for (unsigned int j = n; j > 0; --j) {
            ++nComparacoes;
            unsigned int digito = (origem[j - 1] / i % 10);
            destino[--indice[digito]] = origem[j - 1];
            ++nMovimentacoes;
        }

        // trocamos destino e origem entre si 
        int *temp = origem;
        origem = destino;
        destino = temp;
    }

    if (origem != v) {
        for (unsigned int j = 0; j < n; ++j) {
            ++nComparacoes;
            v[j] = origem[j];
            ++nMovimentacoes;
        }
    }

    free(v2);
}