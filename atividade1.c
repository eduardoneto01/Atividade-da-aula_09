#include <stdio.h>
#include <stdlib.h>

struct Produto {
    int codigo;
    char nome[50];
    float preco;
};

int main() {
    struct Produto produtos[3];
    struct Produto lido;
    FILE *arq;
    int i;

    for (i = 0; i < 3; i++) {
        printf("Produto %d\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &produtos[i].codigo);
        printf("Nome: ");
        scanf(" %49[^\n]", produtos[i].nome);
        printf("Preco: ");
        scanf("%f", &produtos[i].preco);
        printf("\n");
    }

    arq = fopen("estoque.txt", "w");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    for (i = 0; i < 3; i++) {
        fprintf(arq, "%d;%s;%.2f\n", produtos[i].codigo, produtos[i].nome, produtos[i].preco);
    }
    fclose(arq);

    arq = fopen("estoque.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    printf("========== ESTOQUE ==========\n");
    printf("%-8s %-30s %10s\n", "CODIGO", "NOME", "PRECO");
    printf("-----------------------------------------------------\n");

    while (fscanf(arq, "%d;%49[^;];%f\n", &lido.codigo, lido.nome, &lido.preco) == 3) {
        printf("%-8d %-30s R$ %7.2f\n", lido.codigo, lido.nome, lido.preco);
    }
    fclose(arq);

    return 0;
}
