#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h> 
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

int mudarDisco(Pilha* torres, int origem, int destino){
    if(origem < 0 || origem >= 3 || destino < 0 || destino >= 3 || origem == destino){
        printf("Movimento inválido!\n");
        return 0;
    }
    
    int disco = removerPilha(&torres[origem]);

    if(disco == -1)
    {
        printf("Não há discos na torre %d para mover!\n", origem + 1);
        return 0;
    }
    
    if(torres[destino].topo >= 0 && torres[destino].discos[torres[destino].topo] < disco)
    {
        printf("Movimento inválido! Não é possível colocar um disco maior sobre um menor.\n");
        adicionarPilha(&torres[origem], disco);
        return 0;
    }

    adicionarPilha(&torres[destino], disco);
    return 1;
}

void iniciarJogo(Pilha* torres, int numeroDiscos) {
    for (int i = 0; i < 3; i++) {
        iniciarPilhaVazia(&torres[i]);
    }
    for (int i = numeroDiscos; i > 0; i--) {
        adicionarPilha(&torres[0], i);
    }
}

int checarFim(Pilha* torres, int numeroDiscos) {
    return (torres[1].topo == numeroDiscos - 1 || torres[2].topo == numeroDiscos - 1);
}

int main() {
    int numeroDiscos;
    Pilha torres[3];
    int origem, destino, resp;
    int reiniciarJogo;

    printf("=============== TORRE DE HANÓI ===============");
    printf("\n\nO objetivo é passar todos os discos para a última torre com a ajuda da torre central, de modo que no momento da \ntransferência o disco de maior diâmetro nunca fique sobre o de menor diâmetro.");

    printf("\n\n=============== REGRAS ===============");
    printf("\n\n1. Movimentar uma só peça (disco) de cada vez.");
    printf("\n2. Uma peça maior não pode ficar acima de uma menor.");
    printf("\n3. Não é permitido movimentar uma peça que esteja abaixo de outra.");
    printf("\n4. A qualquer momento, digite ""1000"" para reiniciar o jogo.");
    printf("\n\n==============================================");
    printf("\n\nPronto para jogar [1] Sim / [0] Não, encerrar: ");
    scanf("%d", &resp); 

    if(resp == 1) {
    reiniciar_jogo:
    system("clear");
    printf("Digite o número de discos (1-%d): ", 10);
    scanf("%d", &numeroDiscos);

    if (numeroDiscos < 1 || numeroDiscos > 10) {
        printf("Número de discos inválido. Deve estar entre 1 e %d.\n", 10);
        return 1;
    }

    iniciarJogo(torres, numeroDiscos);

    while (1) {
        system("clear");
        mostrarPilhas(torres, numeroDiscos);

        if (checarFim(torres, numeroDiscos)) {
            printf("Parabéns! Você venceu o jogo!\n");
            printf("Deseja jogar novamente? [1] Sim / [0] Não: ");
            int reiniciar;
            scanf("%d", &reiniciar);

            if (reiniciar == 1) {
                system("clear");
                printf("Reiniciando o jogo...\n");
                sleep(2);
                goto reiniciar_jogo;
            } else {
                break;
            }
        }

        printf("Digite a torre de origem: ");
        scanf("%d", &origem);

        reiniciarJogo = origem; 

        if(reiniciarJogo == 1000) { 
            system("clear");
            printf("Reiniciando o jogo...\n");
            sleep(2);
            goto reiniciar_jogo;
        }

        printf("Digite a torre de destino: ");
        scanf("%d", &destino);

        reiniciarJogo = destino; 

        if(reiniciarJogo == 1000) { 
            system("clear");
            printf("Reiniciando o jogo...\n");
            sleep(2);
            goto reiniciar_jogo;
        }

        mostrarPilhas(torres, numeroDiscos);

        if (mudarDisco(torres, origem - 1, destino - 1)) {
            mostrarPilhas(torres, numeroDiscos);
        }
    }

    } else { 
        printf("\nObrigado por utilizar nosso programa.");
    }

    return 0;
}