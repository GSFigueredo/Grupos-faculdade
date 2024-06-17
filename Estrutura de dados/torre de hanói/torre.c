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

int removerPilha(Pilha* pilha) {
    if (pilha->topo >= 0) {
        return pilha->discos[pilha->topo--];
    }
    return -1;
}
void mostrarPilhas(Pilha* torres, int numeroDiscos) {
    for (int nivel = numeroDiscos - 1; nivel >= 0; nivel--) {
        for (int torre = 0; torre < 3; torre++) {
            if (torres[torre].topo >= nivel) {
                int tamanho = torres[torre].discos[nivel];
                for (int s = 0; s < 10 - tamanho; s++) {
                    printf(" ");
                }
                for (int s = 0; s < tamanho; s++) {
                    printf("=");
                }
                printf("|");
                for (int s = 0; s < tamanho; s++) {
                    printf("=");
                }
                for (int s = 0; s < 10 - tamanho; s++) {
                    printf(" ");
                }
            } else {
                for (int s = 0; s < 2 * 10 + 1; s++) {
                    printf(" ");
                }
            }
            printf("   ");
        }
        printf("\n");
    }

    for (int i = 0; i < 3; i++) {
        for (int s = 0; s < 10; s++) {
            printf(" ");
        }
        printf(" %d ", i + 1);
        for (int s = 0; s < 10; s++) {
            printf(" ");
        }
        printf("   ");
    }
    printf("\n");
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
