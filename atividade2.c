#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Funcionario {
    int id;
    char cargo[30];
    float salario;
};

int main() {
    struct Funcionario *func, *backup;
    FILE *arq;

    func = (struct Funcionario*) malloc(sizeof(struct Funcionario));
    backup = (struct Funcionario*) malloc(sizeof(struct Funcionario));

    if (func == NULL || backup == NULL) {
        printf("Erro de alocacao!\n");
        return 1;
    }

    printf("ID: ");
    scanf("%d", &func->id);
    printf("Cargo: ");
    scanf(" %29[^\n]", func->cargo);
    printf("Salario: ");
    scanf("%f", &func->salario);

    memcpy(backup, func, sizeof(struct Funcionario));

    arq = fopen("backup_rh.bin", "wb");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }
    fwrite(backup, sizeof(struct Funcionario), 1, arq);
    fclose(arq);

    printf("\nBackup salvo em backup_rh.bin\n");
    printf("ID: %d | Cargo: %s | Salario: R$ %.2f\n", backup->id, backup->cargo, backup->salario);

    free(func);
    free(backup);

    return 0;
}
