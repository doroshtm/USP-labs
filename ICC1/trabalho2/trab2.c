#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Register {
    int id;
    char login[15];
    char password[30];
    char gender;
    double salary;
};

void readRegisters(FILE *, struct Register *, int *);
void insertRegister(struct Register *, int *);
void searchRegister(struct Register *, int, int *);
void removeRegister(struct Register *, int *, int *);
int getInMemoryLeastPosition(struct Register *, int);


int main (void) {
    char arquivoJson[100];

    // estamos lendo o nome do arquivo JSON, garantindo, ainda, que não haja overflow
    if(scanf("%99s", arquivoJson) != 1) {
        return 1; 
    }
    // abrindo o arquivo JSON para leitura
    FILE *jsonFile = fopen(arquivoJson, "r");
    if(jsonFile == NULL) {
        return 1;
    }

    // alocando memória dinâmica para os registros
    struct Register *registers = malloc(1000 * sizeof(struct Register));
    if(registers == NULL) {
        return 1;
    }
    int leastPosition = 0;

    // lendo os registros do arquivo JSON
    int registerAmount = 0;
    readRegisters(jsonFile, registers, &registerAmount);
    fclose(jsonFile);
    leastPosition = registerAmount;
    printf("%d registro(s) lido(s).\n", registerAmount);
    
    
    int removedTotal = 0;
    
    int operator;
    while (scanf(" %d", &operator) == 1) {
        getchar(); // tira o espaço depois do número
        switch (operator) {
            case 1:
                // inserir
                // formato: 1 id "login" "senha" "genero" salario
                if (registerAmount - removedTotal >= 1000) {
                    printf("Sem espaço para inserção.\n");
                    // limpa o buffer de entrada
                    int ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    continue; 
                }
                insertRegister(registers, &registerAmount);
                
                printf("Registro inserido.\n");
                break;
            case 2:
                // buscar
                // formato: 2 "tipo" valor

                int found;

                searchRegister(registers, registerAmount, &found);

                if(!found) {
                    printf("Nada encontrado.\n");
                }
                break;
            case 3: {
                // remover
                // formato: 3 "tipo" valor
                
                int removed;

                removeRegister(registers, &registerAmount, &removed);

                if(!removed) {
                    printf("Remoção inválida.\n");
                } else {
                    removedTotal += removed;
                    printf("%d registro(s) removido(s).\n", removed);
                }
                break;
            }
            
            default:
                break;
        }
    }

    // grava JSON ao final
    jsonFile = fopen(arquivoJson, "w");
    if(jsonFile) {
        fprintf(jsonFile, "[\n");
        int written = 0, validCount = 0;
        for(int i = 0; i < registerAmount; ++i) {
            if(registers[i].id != -1) ++validCount;
        }
        for(int i = 0; i < registerAmount; ++i) {
            if(registers[i].id == -1) continue;
            ++written;
            fprintf(jsonFile, "   {\n");
            fprintf(jsonFile, "       \"id\": %d,\n", registers[i].id);
            fprintf(jsonFile, "       \"login\": \"%s\",\n", registers[i].login);
            fprintf(jsonFile, "       \"password\": \"%s\",\n", registers[i].password);
            if (registers[i].gender == '"') {
                fprintf(jsonFile, "       \"gender\": \"\",\n");
            } else {
                fprintf(jsonFile, "       \"gender\": \"%c\",\n", registers[i].gender);
            }
            fprintf(jsonFile, "       \"salary\": %.2f\n", registers[i].salary);
            fprintf(jsonFile, "   }%s\n", (written < validCount) ? "," : "");
        }
        fprintf(jsonFile, "]\n");
        fclose(jsonFile);
    }
    free(registers);
    registers = NULL;

    
}

void readRegisters(FILE *jsonFile, struct Register *registers, int *registerAmount) {
    char buffer[4096];
    struct Register tmp;
    int insideObject = 0;
    // lendo o arquivo JSON linha por linha
    while(fgets(buffer, sizeof(buffer), jsonFile)) {
        // verificando se a linha contém o início ou o fim de um objeto JSON
        // se a linha contém o início de um objeto JSON, inicializa a variável tmp
        // se a linha contém o fim de um objeto JSON, armazena o registro na lista de registros
        if(strstr(buffer, "{")) {
            insideObject = 1;
            memset(&tmp, 0, sizeof(tmp));
            continue;
        } else if(strstr(buffer, "}")) {
            registers[(*registerAmount)++] = tmp;
            insideObject = 0;
            continue;
        }
        // se a linha contém um campo do objeto JSON, armazena o valor na variável tmp
        if(insideObject) {
            // verificando qual campo do objeto JSON está sendo lido
            // strstr funciona como uma verificação de substring
            if (strstr(buffer, "\"id\"")) {
                sscanf(buffer, "%*[^:]: %d", &tmp.id);
            } else if (strstr(buffer, "\"login\"")) {
                // o %*[^:] ignora tudo até o primeiro ':', e o \"%[^\"]\" lê a string entre aspas
                // "%[^\"]" - lê tudo até a próxima aspa dupla
                sscanf(buffer, "%*[^:]: \"%14[^\"]\"", tmp.login);
            } else if (strstr(buffer, "\"password\"")) {
                sscanf(buffer, "%*[^:]: \"%29[^\"]\"", tmp.password);
            } else if (strstr(buffer, "\"gender\"")) {
                sscanf(buffer, "%*[^:]: \"%c", &tmp.gender);
            } else if (strstr(buffer, "\"salary\"")) {
                sscanf(buffer, "%*[^:]: %lf", &tmp.salary);
            }
        }
    }

}

void insertRegister(struct Register *registers, int *registerAmount) {
    // criando um novo registro auxiliar
    // e lendo os dados do registro
    struct Register newRegister;
    if (scanf("%d \"%14[^\"]\" \"%29[^\"]\" \"%c\" %lf", &newRegister.id, newRegister.login, newRegister.password, &newRegister.gender, &newRegister.salary) != 5) {
        return;
    }

    // pegando a posição do próximo registro a ser inserido
    int leastPosition = getInMemoryLeastPosition(registers, *registerAmount);
    registers[leastPosition] = newRegister;
    if (leastPosition == *registerAmount) { // se inseriu no fim
        (*registerAmount)++;
    }
}

void searchRegister(struct Register *registers, int registerAmount, int *found) {
    *found = 0;
    char buffer[4096];
    char searchType[30];
    char searchValue[30];

    if (!fgets(buffer, sizeof(buffer), stdin))
        return;

    // tentamos ler "<tipo>" "<valor com espaços>"
    if (sscanf(buffer, "\"%29[^\"]\" \"%29[^\"]\"",searchType, searchValue) < 2) {
        // se não houver aspas no valor, lemos sem elas
        sscanf(buffer, "\"%29[^\"]\" %29s",
               searchType, searchValue);
    }
    // removendo aspas do valor de busca
    int len = strlen(searchValue);
    if (len >= 2 && searchValue[0]=='"' && searchValue[len-1]=='"') {
        memmove(searchValue, searchValue+1, len-2);
        searchValue[len-2] = '\0';
    }

    for (int i = 0; i < registerAmount; ++i) {
        if (registers[i].id == -1) continue;
        if ((strcmp(searchType, "id") == 0 && registers[i].id == atoi(searchValue)) || 
            (strcmp(searchType, "login") == 0 && strcmp(registers[i].login, searchValue) == 0) ||
            (strcmp(searchType, "password") == 0 && strcmp(registers[i].password, searchValue) == 0) ||
            (strcmp(searchType, "gender") == 0 && registers[i].gender == searchValue[0]) ||
            (strcmp(searchType, "salary") == 0 && registers[i].salary == atof(searchValue))) {
            *found = 1;
            printf("{\n"
                   "    \"id\": %d,\n"
                   "    \"login\": \"%s\",\n"
                   "    \"password\": \"%s\",\n"
                   "    \"gender\": \"%c\",\n"
                   "    \"salary\": %.2f\n"
                   "}\n",
                   registers[i].id,
                   registers[i].login,
                   registers[i].password,
                   registers[i].gender,
                   registers[i].salary);
        }
    }
}

void removeRegister(struct Register *registers, int *registerAmount, int *removed) {
    char buffer[4096];
    if (!fgets(buffer, sizeof(buffer), stdin)){
        return;
    }
    char searchType[30];
    char searchValue[30];
    
    // lendo o tipo e valor de busca
    // aqui, se não houver aspas no valor, lemos sem elas
    if (sscanf(buffer, "\"%29[^\"]\" \"%29[^\"]\"", searchType, searchValue) < 2) {
        sscanf(buffer, "\"%29[^\"]\" %29s", searchType, searchValue);
    }

    // removendo aspas do valor de busca 
    int len = strlen(searchValue);
    if (len >= 2 && searchValue[0] == '"' && searchValue[len - 1] == '"') {
        memmove(searchValue, searchValue + 1, len - 2);
        searchValue[len - 2] = '\0';
    }
    
    *removed = 0;

    for(int i = 0; i < *registerAmount; ++i) {
        // verificando se o registro corresponde ao tipo e valor de busca
        // se corresponder, marcamos o registro como removido (id = -1)
        if(registers[i].id == -1) continue; // ignora registros removidos
        if((strcmp(searchType, "id") == 0 && registers[i].id == atoi(searchValue)) ||
           (strcmp(searchType, "login") == 0 && strcmp(registers[i].login, searchValue) == 0) ||
           (strcmp(searchType, "password") == 0 && strcmp(registers[i].password, searchValue) == 0) ||
           (strcmp(searchType, "gender") == 0 && registers[i].gender == searchValue[0]) ||
           (strcmp(searchType, "salary") == 0 && registers[i].salary == atof(searchValue))) {
            registers[i].id = -1; // marca como removido
            (*removed)++;
            
        }
    }
}

// retorna a posição do próximo registro a ser inserido
int getInMemoryLeastPosition(struct Register *registers, int registerAmount) {
    for (int i = 0; i < registerAmount; ++i) {
        if (registers[i].id == -1) {
            return i; // reusa slot
        }
    }
    return registerAmount; // se nenhuma posição livre, volta fim
}