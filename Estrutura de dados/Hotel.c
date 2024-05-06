#include<stdio.h>
#include<math.h>
#include<stdlib.h>

typedef struct hospedes{
    char nome[150];
    char cpf[20];
    int quarto;
} hospedes;

void inserirHospede (hospedes hospede[], int *quantHospedes) {

}

int main () {

    hospedes hospede[250];
    int quantHospedes = 0;
    int esc;
    int resp = 0;

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

        switch(esc) {
            case 1:
                inserirHospede(hospede, &quantHospedes);
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

    } while (resp != 1);

    return 0;
}