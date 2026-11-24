#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Eleitor {
    char titulo[12];
    int zona;
};

struct Cedula {
    struct Eleitor eleitor;
    int numero_voto;
};

struct Cedula* adicionarVoto(struct Cedula *lista, int *qtd, struct Cedula nova) {
    struct Cedula *temp;

    temp = (struct Cedula*) realloc(lista, (*qtd + 1) * sizeof(struct Cedula));
    if (temp == NULL) {
        printf("Erro de alocacao!\n");
        return lista;
    }

    lista = temp;
    lista[*qtd] = nova;
    (*qtd)++;

    return lista;
}

void salvarUrna(struct Cedula *lista, int qtd) {
    FILE *arq = fopen("urnas.bin", "wb");
    if (arq == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return;
    }
    fwrite(lista, sizeof(struct Cedula), qtd, arq);
    fclose(arq);
}

struct Cedula* recuperarUrna(int *qtd) {
    FILE *arq;
    struct Cedula *lista;
    long tamanho;

    arq = fopen("urnas.bin", "rb");
    if (arq == NULL) {
        *qtd = 0;
        return NULL;
    }

    fseek(arq, 0, SEEK_END);
    tamanho = ftell(arq);
    rewind(arq);

    lista = (struct Cedula*) malloc(tamanho);
    *qtd = tamanho / sizeof(struct Cedula);
    fread(lista, tamanho, 1, arq);

    fclose(arq);
    return lista;
}

int main() {
    struct Cedula *votos = NULL;
    struct Cedula *recuperados;
    struct Cedula nova;
    int qtd = 0, qtdRec, i;
    char continuar;

    do {
        printf("Titulo do eleitor (ate 11 caracteres): ");
        scanf("%11s", nova.eleitor.titulo);
        printf("Zona: ");
        scanf("%d", &nova.eleitor.zona);
        printf("Numero do voto: ");
        scanf("%d", &nova.numero_voto);

        votos = adicionarVoto(votos, &qtd, nova);

        printf("Registrar outro voto? (s/n): ");
        scanf(" %c", &continuar);
    } while (continuar == 's' || continuar == 'S');

    salvarUrna(votos, qtd);
    printf("\n%d voto(s) salvo(s) em urnas.bin\n", qtd);

    recuperados = recuperarUrna(&qtdRec);

    printf("\nVotos recuperados do arquivo:\n");
    for (i = 0; i < qtdRec; i++) {
        printf("Titulo: %s | Zona: %d | Voto: %d\n",
               recuperados[i].eleitor.titulo,
               recuperados[i].eleitor.zona,
               recuperados[i].numero_voto);
    }

    free(votos);
    free(recuperados);

    return 0;
}
