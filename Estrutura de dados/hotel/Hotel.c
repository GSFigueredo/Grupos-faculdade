#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct quartos{
    int numero; 
    char listaHospedes[200][10];
    int quantHospedesQuarto;
} quartos;

void limparCaractere () {
    int limp; 
    while ((limp = getchar()) != '\n' && limp != EOF);
}

void iniciarLista(quartos quarto[], int *posicaoQuarto) {
    FILE *arquivo = fopen("hospedes.txt", "r");

    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(EXIT_FAILURE);
    }

    while(!feof(arquivo)) {
        fscanf(arquivo, "%d", quarto[*posicaoQuarto].numero);

        quarto[*posicaoQuarto].quantHospedesQuarto = 0;
        while(1) {
            fscanf(arquivo, " %[^\n]", quarto[*posicaoQuarto].listaHospedes[quarto[*posicaoQuarto].quantHospedesQuarto]);
            quarto[*posicaoQuarto].quantHospedesQuarto++;
            if (strncmp(quarto[*posicaoQuarto].listaHospedes[quarto[*posicaoQuarto].quantHospedesQuarto - 1], "==========", strlen("==========")) == 0) {
                break;
            }
        }
        quarto[*posicaoQuarto].quantHospedesQuarto -= 1;
        (*posicaoQuarto)++;
    }

    fclose(arquivo);
}

void inserirHospede (quartos quarto[], int *posicaoQuarto) {
    int quantHospedesQuarto = 0;
    int esc = 1;

    FILE *arquivo = fopen("/workspaces/Grupos-faculdade/Estrutura de dados/hotel/hospedes.txt", "a");

    if(arquivo == NULL) {
        printf("Erro ao abrir o arquivo.");
        exit(EXIT_FAILURE);
    }

    fprintf(arquivo, "\n");
    limparCaractere();

    do {
        printf("Digite o nome dos hóspedes, hospede %d: ", quantHospedesQuarto+1);
        fgets(quarto[*posicaoQuarto].listaHospedes[quantHospedesQuarto], sizeof(quarto[*posicaoQuarto].listaHospedes[quantHospedesQuarto]), stdin);
        quarto[*posicaoQuarto].listaHospedes[quantHospedesQuarto][strcspn(quarto[*posicaoQuarto].listaHospedes[quantHospedesQuarto], "\n")] = '\0';
        fprintf(arquivo, "%s\n", quarto[*posicaoQuarto].listaHospedes[quantHospedesQuarto]);

        quantHospedesQuarto++;
        quarto[*posicaoQuarto].quantHospedesQuarto = quantHospedesQuarto;

        printf("\n[0] Digitar novo hospede |");
        printf(" [1] Encerrar: ");
        scanf("\n%d", &esc);
        limparCaractere();
    } while (esc != 1);

    fprintf(arquivo, "%s", "==========");

    fclose(arquivo);
}

int main () {

    quartos quarto[50];
    int posicaoQuarto = 0;
    int esc;
    int resp = 0;

    iniciarLista(quarto, &posicaoQuarto);

    do{
        printf("==================== MENU ====================");
        printf("\n[1] Inserir hóspedes\n");
        printf("[2] Listar hóspedes por ordem alfabética\n");
        printf("[3] Buscar hóspede\n");
        printf("[4] Editar hóspede\n");
        printf("[5] Liberar quarto\n");
        printf("[6] Quartos vazios\n");
        printf("==================== **** ====================");
        printf("\nO que deseja fazer? ");
        scanf("%d", &esc);
        limparCaractere();

        switch(esc) {
            case 1:
                inserirHospede(quarto, &posicaoQuarto);
            break;

            case 2:
                // listar hóspedes por ordem alfabética
            break;

            case 3:
                // buscar hóspede
            break;

            case 4:
                // editar hóspede
            break;

            case 5:
                //liberar quarto
            break;

            case 6:
                // quartos vazios
            break;

            default:
                printf("Obrigado por utilizar nosso programa.");
                break;
        }

        printf("\nDeseja realizar mais uma interação? SIM [0] / NÃO [1] ");
        scanf("%d", &resp);

    } while (resp != 1);

    printf("\nNúmero do quarto: %d", quarto[0].numero);
    printf("\nHospede: %s", quarto[0].listaHospedes[0]);
    printf("\nQuantidade de hospedes no quarto: %d", quarto[0].quantHospedesQuarto);

    return 0;
}