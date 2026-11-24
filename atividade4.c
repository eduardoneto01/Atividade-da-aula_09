#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int registro;
    int horas_aula;
} Professor;

Professor* lerFolha(const char *nomeArq, int *qtd) {
    FILE *arq;
    Professor *lista;
    long tamanho;

    arq = fopen(nomeArq, "rb");
    if (arq == NULL) {
        *qtd = 0;
        return NULL;
    }

    fseek(arq, 0, SEEK_END);
    tamanho = ftell(arq);
    rewind(arq);

    *qtd = tamanho / sizeof(Professor);
    lista = (Professor*) malloc(*qtd * sizeof(Professor));
    fread(lista, sizeof(Professor), *qtd, arq);

    fclose(arq);
    return lista;
}

int main() {
    Professor *profs, *carregados;
    void *buffer;
    FILE *arq;
    int n, i, qtdLida;

    printf("Quantos professores deseja cadastrar? ");
    scanf("%d", &n);

    profs = (Professor*) malloc(n * sizeof(Professor));
    if (profs == NULL) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nProfessor %d\n", i + 1);
        printf("Registro: ");
        scanf("%d", &profs[i].registro);
        printf("Horas-aula: ");
        scanf("%d", &profs[i].horas_aula);
    }

    buffer = malloc(n * sizeof(Professor));
    memcpy(buffer, profs, n * sizeof(Professor));

    arq = fopen("folha.dat", "wb");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }
    fwrite(buffer, n * sizeof(Professor), 1, arq);
    fclose(arq);

    printf("\nDados gravados em folha.dat\n");

    carregados = lerFolha("folha.dat", &qtdLida);

    printf("\nProfessores lidos do arquivo (%d):\n", qtdLida);
    for (i = 0; i < qtdLida; i++) {
        printf("Registro: %d | Horas-aula: %d\n", carregados[i].registro, carregados[i].horas_aula);
    }

    free(profs);
    free(buffer);
    free(carregados);

    return 0;
}
