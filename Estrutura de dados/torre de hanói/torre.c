#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
typedef struct {
    int discos[10];
    int topo;
} Pilha;

void iniciarPilhaVazia(Pilha* pilha) {
    pilha->topo = -1;
}

void adicionarPilha(Pilha* pilha, int tamanho) {
    if (pilha->topo < 10 - 1) {
        pilha->discos[++pilha->topo] = tamanho;
    }
}

void iniciarJogo(Pilha* torres, int numeroDiscos) {
    for (int i = 0; i < 3; i++) {
        iniciarPilhaVazia(&torres[i]);
    }
    for (int i = numeroDiscos; i > 0; i--) {
        adicionarPilha(&torres[0], i);
    }
}

int main() {
    int numeroDiscos;
    Pilha torres[3];

    printf("Digite o número de discos (1-%d): ", 10);
    scanf("%d", &numeroDiscos);
    if (numeroDiscos < 1 || numeroDiscos > 10) {
        printf("Número de discos inválido. Deve estar entre 1 e %d.\n", 10);
        return 1;
    }

    iniciarJogo(torres, numeroDiscos);

    return 0;
}