#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura que representa uma peça
typedef struct {
    char tipo;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca pecas[TAM_FILA];
    int frente;
    int tras;
    int quantidade;
} Fila;

// Estrutura da pilha
typedef struct {
    Peca pecas[TAM_PILHA];
    int topo;
} Pilha;

// ----------------- FUNÇÕES DA FILA -----------------

void inicializarFila(Fila *fila) {
    fila->frente = 0;
    fila->tras = -1;
    fila->quantidade = 0;
}

int filaVazia(Fila *fila) {
    return fila->quantidade == 0;
}

int filaCheia(Fila *fila) {
    return fila->quantidade == TAM_FILA;
}

void enfileirar(Fila *fila, Peca nova) {
    if (filaCheia(fila)) return;
    fila->tras = (fila->tras + 1) % TAM_FILA;
    fila->pecas[fila->tras] = nova;
    fila->quantidade++;
}

Peca desenfileirar(Fila *fila) {
    Peca removida = {'-', -1};
    if (filaVazia(fila)) return removida;
    removida = fila->pecas[fila->frente];
    fila->frente = (fila->frente + 1) % TAM_FILA;
    fila->quantidade--;
    return removida;
}

// ----------------- FUNÇÕES DA PILHA -----------------

void inicializarPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAM_PILHA - 1;
}

void empilhar(Pilha *pilha, Peca p) {
    if (pilhaCheia(pilha)) {
        printf("\nA pilha está cheia! Não é possível reservar mais peças.\n");
        return;
    }
    pilha->topo++;
    pilha->pecas[pilha->topo] = p;
}

Peca desempilhar(Pilha *pilha) {
    Peca removida = {'-', -1};
    if (pilhaVazia(pilha)) {
        printf("\nA pilha está vazia! Nenhuma peça reservada para usar.\n");
        return removida;
    }
    removida = pilha->pecas[pilha->topo];
    pilha->topo--;
    return removida;
}

// ----------------- OUTRAS FUNÇÕES -----------------

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

void mostrarEstado(Fila *fila, Pilha *pilha) {
    printf("\n======================================\n");
    printf("Estado atual:\n\n");

    printf("Fila de peças:\n");
    if (filaVazia(fila))
        printf("(vazia)\n");
    else {
        for (int i = 0; i < fila->quantidade; i++) {
            int indice = (fila->frente + i) % TAM_FILA;
            printf("[%c %d] ", fila->pecas[indice].tipo, fila->pecas[indice].id);
        }
        printf("\n");
    }

    printf("\nPilha de reserva (Topo -> Base):\n");
    if (pilhaVazia(pilha))
        printf("(vazia)\n");
    else {
        for (int i = pilha->topo; i >= 0; i--) {
            printf("[%c %d] ", pilha->pecas[i].tipo, pilha->pecas[i].id);
        }
        printf("\n");
    }
    printf("======================================\n");
}

// ----------------- FUNÇÃO PRINCIPAL -----------------

int main() {
    Fila fila;
    Pilha pilha;
    int opcao;
    int contadorId = 0;

    srand(time(NULL));

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(contadorId++));
    }

    do {
        mostrarEstado(&fila, &pilha);

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (!filaVazia(&fila)) {
                Peca jogada = desenfileirar(&fila);
                printf("\nPeça jogada: [%c %d]\n", jogada.tipo, jogada.id);
                enfileirar(&fila, gerarPeca(contadorId++));
            } else {
                printf("\nFila vazia.\n");
            }
        } 
        else if (opcao == 2) {
            if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                Peca reservada = desenfileirar(&fila);
                printf("\nPeça reservada: [%c %d]\n", reservada.tipo, reservada.id);
                empilhar(&pilha, reservada);
                enfileirar(&fila, gerarPeca(contadorId++));
            } else if (pilhaCheia(&pilha)) {
                printf("\nA pilha está cheia! Não é possível reservar mais peças.\n");
            } else {
                printf("\nA fila está vazia.\n");
            }
        } 
        else if (opcao == 3) {
            Peca usada = desempilhar(&pilha);
            if (usada.id != -1)
                printf("\nPeça usada da reserva: [%c %d]\n", usada.tipo, usada.id);
        } 
        else if (opcao == 0) {
            printf("\nSaindo do jogo...\n");
        } 
        else {
            printf("\nOpção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
