#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

typedef struct {
    char nome;
    int id;
} Peca;

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int qtd;
} Fila;

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

int contador = 0;

char gerarNome() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    return tipos[rand() % 4];
}

Peca gerarPeca() {
    Peca p;
    p.nome = gerarNome();
    p.id = contador++;
    return p;
}

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        f->itens[f->fim] = gerarPeca();
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtd++;
    }
}

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int filaVazia(Fila *f) {
    return f->qtd == 0;
}

int filaCheia(Fila *f) {
    return f->qtd == TAM_FILA;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

Peca removerFila(Fila *f) {
    Peca p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->qtd--;
    return p;
}

void adicionarFila(Fila *f, Peca p) {
    if (!filaCheia(f)) {
        f->itens[f->fim] = p;
        f->fim = (f->fim + 1) % TAM_FILA;
        f->qtd++;
    }
}

void empilhar(Pilha *p, Peca x) {
    if (!pilhaCheia(p)) {
        p->topo++;
        p->itens[p->topo] = x;
    }
}

Peca desempilhar(Pilha *p) {
    Peca x = p->itens[p->topo];
    p->topo--;
    return x;
}

void mostrarEstado(Fila *f, Pilha *p) {
    printf("\nFila de pecas\t");
    int i = f->inicio;
    for (int j = 0; j < f->qtd; j++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
        i = (i + 1) % TAM_FILA;
    }

    printf("\nPilha de reserva\t(Topo -> base): ");
    for (int j = p->topo; j >= 0; j--) {
        printf("[%c %d] ", p->itens[j].nome, p->itens[j].id);
    }
    printf("\n");
}

int main() {
    Fila fila;
    Pilha pilha;
    srand(time(NULL));
    inicializarFila(&fila);
    inicializarPilha(&pilha);
    int opcao;

    do {
        mostrarEstado(&fila, &pilha);
        printf("\n1 Jogar peca da frente da fila\n");
        printf("2 Enviar peca da fila para a pilha de reserva\n");
        printf("3 Usar peca da pilha de reserva\n");
        printf("4 Trocar peca da frente da fila com o topo da pilha\n");
        printf("5 Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
        printf("0 Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (!filaVazia(&fila)) {
                Peca usada = removerFila(&fila);
                Peca nova = gerarPeca();
                adicionarFila(&fila, nova);
            }
        } else if (opcao == 2) {
            if (!filaVazia(&fila) && !pilhaCheia(&pilha)) {
                Peca movida = removerFila(&fila);
                empilhar(&pilha, movida);
                Peca nova = gerarPeca();
                adicionarFila(&fila, nova);
            }
        } else if (opcao == 3) {
            if (!pilhaVazia(&pilha)) {
                Peca usada = desempilhar(&pilha);
            }
        } else if (opcao == 4) {
            if (!pilhaVazia(&pilha) && !filaVazia(&fila)) {
                Peca temp = pilha.itens[pilha.topo];
                pilha.itens[pilha.topo] = fila.itens[fila.inicio];
                fila.itens[fila.inicio] = temp;
            }
        } else if (opcao == 5) {
            if (fila.qtd >= 3 && pilha.topo >= 2) {
                for (int i = 0; i < 3; i++) {
                    int index = (fila.inicio + i) % TAM_FILA;
                    Peca temp = fila.itens[index];
                    fila.itens[index] = pilha.itens[pilha.topo - i];
                    pilha.itens[pilha.topo - i] = temp;
                }
            }
        }
    } while (opcao != 0);

    return 0;
}

