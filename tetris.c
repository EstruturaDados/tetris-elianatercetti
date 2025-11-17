#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

struct Peca {
    char tipo;
    int id;
};

struct Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    struct Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

void mostrarFila(struct Peca fila[], int quantidade) {
    int i;
    printf("\nFila de peças:\n");
    if (quantidade == 0) {
        printf("(vazia)\n");
        return;
    }
    for (i = 0; i < quantidade; i++) {
        printf("[%c %d] ", fila[i].tipo, fila[i].id);
    }
    printf("\n");
}

void jogarPeca(struct Peca fila[], int *quantidade) {
    int i;
    if (*quantidade == 0) {
        printf("\nA fila está vazia!\n");
        return;
    }
    printf("\nPeça jogada: [%c %d]\n", fila[0].tipo, fila[0].id);
    for (i = 0; i < *quantidade - 1; i++) {
        fila[i] = fila[i + 1];
    }
    (*quantidade)--;
}

void adicionarPeca(struct Peca fila[], int *quantidade, int *proximoId) {
    if (*quantidade == TAMANHO_FILA) {
        printf("\nA fila está cheia!\n");
        return;
    }
    fila[*quantidade] = gerarPeca(*proximoId);
    printf("\nPeça adicionada: [%c %d]\n", fila[*quantidade].tipo, fila[*quantidade].id);
    (*quantidade)++;
    (*proximoId)++;
}

int main() {
    struct Peca fila[TAMANHO_FILA];
    int quantidade = 0;
    int proximoId = 0;
    int opcao;
    int i;

    srand(time(NULL));

    for (i = 0; i < TAMANHO_FILA; i++) {
        fila[i] = gerarPeca(proximoId);
        quantidade++;
        proximoId++;
    }

    do {
        mostrarFila(fila, quantidade);
        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Inserir nova peça\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            jogarPeca(fila, &quantidade);
        } else if (opcao == 2) {
            adicionarPeca(fila, &quantidade, &proximoId);
        } else if (opcao == 0) {
            printf("\nSaindo...\n");
        } else {
            printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}

