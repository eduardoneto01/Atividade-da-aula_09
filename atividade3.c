#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente {
    int conta_corrente;
    char nome[50];
    float saldo;
};

void criarArquivoExemplo() {
    struct Cliente c[3] = {
        {101, "Maria Silva", 1500.00},
        {102, "Joao Souza", 800.50},
        {103, "Ana Costa", 250.00}
    };
    FILE *arq = fopen("clientes.bin", "wb");
    if (arq != NULL) {
        fwrite(c, sizeof(struct Cliente), 3, arq);
        fclose(arq);
    }
}

int main() {
    struct Cliente cliente;
    FILE *arq;
    int conta, achou = 0;
    float valor;

    printf("Numero da conta corrente: ");
    scanf("%d", &conta);
    printf("Valor (positivo para deposito, negativo para saque): ");
    scanf("%f", &valor);

    arq = fopen("clientes.bin", "rb+");
    if (arq == NULL) {
        criarArquivoExemplo();
        arq = fopen("clientes.bin", "rb+");
        if (arq == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 1;
        }
    }

    while (fread(&cliente, sizeof(struct Cliente), 1, arq) == 1) {
        if (cliente.conta_corrente == conta) {
            achou = 1;
            if (cliente.saldo + valor < 0) {
                printf("Saldo insuficiente! Saldo atual: R$ %.2f\n", cliente.saldo);
                break;
            }
            cliente.saldo = cliente.saldo + valor;

            fseek(arq, -(long) sizeof(struct Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(struct Cliente), 1, arq);

            printf("Operacao realizada! %s, novo saldo: R$ %.2f\n", cliente.nome, cliente.saldo);
            break;
        }
    }

    if (achou == 0) {
        printf("Conta nao encontrada!\n");
    }

    fclose(arq);

    return 0;
}
