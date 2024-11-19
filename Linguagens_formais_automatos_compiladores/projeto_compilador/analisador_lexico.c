#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "analisador_lexico.h" 

#define MAX_TK 100 
typedef struct {
    tipoToken tipo;
    char palavra[MAX_TK]; 
    int linha;
} token;

token criarToken(tipoToken tipo, const char* palavra, int linha) {
    token t;
    t.tipo = tipo;
    strcpy(t.palavra, palavra);
    t.linha = linha;
    return t;
}

void salvarToken(FILE *arquivoLex, token t) {
    fprintf(arquivoLex, "Token: %d | Valor: %s | Linha: %d\n", t.tipo, t.palavra, t.linha);
}

tipoToken checarToken(const char* palavra) {
    if (strcmp(palavra, "program") == 0) return tk_program;
    if (strcmp(palavra, "var") == 0) return tk_var;
    if (strcmp(palavra, "begin") == 0) return tk_begin;
    if (strcmp(palavra, "end") == 0) return tk_end;
    if (strcmp(palavra, "integer") == 0) return tk_integer;
    if (strcmp(palavra, "real") == 0) return tk_real;
    if (strcmp(palavra, "if") == 0) return tk_if;
    if (strcmp(palavra, "then") == 0) return tk_then;
    if (strcmp(palavra, "else") == 0) return tk_else;
    if (strcmp(palavra, "while") == 0) return tk_while;
    if (strcmp(palavra, "do") == 0) return tk_do;
    return tk_id;  // Se não for palavra-chave, é identificador
}

tipoToken checarElemento(const char* operador) {
    if (strcmp(operador, "+") == 0) return tk_som;
    if (strcmp(operador, "-") == 0) return tk_sub;
    if (strcmp(operador, "*") == 0) return tk_mult;
    if (strcmp(operador, "/") == 0) return tk_div;
    if (strcmp(operador, ">") == 0) return tk_maior;
    if (strcmp(operador, "<") == 0) return tk_menor;
    if (strcmp(operador, "<=") == 0) return tk_menor_eq;
    if (strcmp(operador, ">=") == 0) return tk_maior_eq;
    if (strcmp(operador, ":=") == 0) return tk_dp_eq;
    if (strcmp(operador, "=") == 0) return tk_eq;
    if (strcmp(operador, ";") == 0) return tk_pt_virg;
    if (strcmp(operador, ":") == 0) return tk_dp;
    if (strcmp(operador, ",") == 0) return tk_virg;
    if (strcmp(operador, ".") == 0) return tk_pont;
    if (strcmp(operador, "(") == 0) return tk_eparen;
    if (strcmp(operador, ")") == 0) return tk_dparen;
    if (isalnum(operador[0])) {
        if (strchr(operador, '.')) {
            return tk_real_num;
        } else {
            return tk_int;
        }
    }
    return tk_desconhecido;
}

void identificarToken(FILE* arquivo) {
    int linha = 1;
    int caractere;
    char palavra[MAX_TK];
    int caractere_id;

    FILE *arquivoLex = fopen("saida.lex", "w");
    if (!arquivoLex) {
        perror("Erro ao criar o arquivo .lex");
        return;
    }

    while ((caractere = fgetc(arquivo)) != EOF) {
        if (isspace(caractere)) {  // identifica caractere em branco
            if (caractere == '\n') linha++;  // se identificar quebra de linha, pula para a próxima
        } else if (isalpha(caractere)) {  // se não, vem para esse bloco de comandos, aqui ele vai verificar se é uma letra
            caractere_id = 0;
            do {
                palavra[caractere_id++] = caractere;  // Armazena a palavra no vetor palavra
                caractere = fgetc(arquivo); // ler o proximo caractere, pois o fgetc, lê o caractere e já manda para o próximo, e neste caso foi feito na linha 51
            } while (isalnum(caractere) && caractere_id < MAX_TK - 1);  // Continua enquanto for letra ou número

            palavra[caractere_id] = '\0';  // encerra a string

            tipoToken tipo = checarToken(palavra);  // Verifica se é palavra-chave
            token t = criarToken(tipo, palavra, linha); 
            salvarToken(arquivoLex, t); 
        } else if (isdigit(caractere)) {  // verifica números
            caractere_id = 0;
            int lerNumeroReal = 0;
            do {
                palavra[caractere_id++] = caractere;
                caractere = fgetc(arquivo);

                if (caractere == '.' && isdigit(palavra[caractere_id - 1])) { // verifica se o caractere atual é ponto, e o anterior um número
                    palavra[caractere_id++] = caractere; 
                    caractere = fgetc(arquivo);
                    
                    while (isdigit(caractere)) {
                        palavra[caractere_id++] = caractere; 
                        caractere = fgetc(arquivo); 
                    }
                    lerNumeroReal = 1;  // Identifica que leu um número real
                }

            } while (isdigit(caractere) || (caractere == '.' && isdigit(palavra[caractere_id - 1]))); 

            palavra[caractere_id] = '\0';
            tipoToken tipo = lerNumeroReal ? tk_real_num : tk_int;  // Define se é número inteiro ou real
            token t = criarToken(tipo, palavra, linha); 
            salvarToken(arquivoLex, t); 
        } else {
            caractere_id = 0;

             // Identificar operadores (., /, *, :=, :, etc)
            do { 
                palavra[caractere_id++] = caractere;
                caractere = fgetc(arquivo);
            } while (!isalnum(caractere) && !isspace(caractere)); 

            palavra[caractere_id++] = '\0';

            tipoToken tipo = checarElemento(palavra);
            token t = criarToken(tipo, palavra, linha); 
            salvarToken(arquivoLex, t);
        }
    }

    token t = criarToken(tk_eof, "EOF", linha);
    salvarToken(arquivoLex, t);

    fclose(arquivoLex);
}

int main() {
    FILE* arquivo = fopen("codigo.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    identificarToken(arquivo);
    fclose(arquivo);
    return 0;
}