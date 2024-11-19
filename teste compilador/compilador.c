#include "analisador_lexico.h"
#include <stdio.h>

int main() {
    FILE *arquivo = fopen("codigo.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    identificarToken(arquivo);  // Identifica os tokens
    fclose(arquivo);

    // Exemplo de como obter tokens e processá-los
    token tokenAtual;
    tokenAtual = obterProximoToken();
    while (tokenAtual.tipo != tk_eof) {
        printf("Token: %d, Palavra: %s, Linha: %d\n", tokenAtual.tipo, tokenAtual.palavra, tokenAtual.linha);
        tokenAtual = obterProximoToken();
    }

    return 0;
}
