#include "analisador_lexico.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TK 100
static token tokens[MAX_TK];
static int indiceTokens = 0;
static int indiceTokenAtual = 0;

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
        if (isspace(caractere)) {
            if (caractere == '\n') linha++;
        } else if (isalpha(caractere)) {
            caractere_id = 0;
            do {
                palavra[caractere_id++] = caractere;
                caractere = fgetc(arquivo);
            } while (isalnum(caractere) && caractere_id < MAX_TK - 1);

            palavra[caractere_id] = '\0';
            tipoToken tipo = checarToken(palavra);
            tokens[indiceTokens++] = criarToken(tipo, palavra, linha);
            salvarToken(arquivoLex, tokens[indiceTokens - 1]);
        } else if (isdigit(caractere)) {
            caractere_id = 0;
            int lerNumeroReal = 0;
            do {
                palavra[caractere_id++] = caractere;
                caractere = fgetc(arquivo);

                if (caractere == '.' && isdigit(palavra[caractere_id - 1])) {
                    palavra[caractere_id++] = caractere;
                    caractere = fgetc(arquivo);

                    while (isdigit(caractere)) {
                        palavra[caractere_id++] = caractere;
                        caractere = fgetc(arquivo);
                    }
                    lerNumeroReal = 1;
                }

            } while (isdigit(caractere) || (caractere == '.' && isdigit(palavra[caractere_id - 1])));

            palavra[caractere_id] = '\0';
            tipoToken tipo = lerNumeroReal ? tk_real_num : tk_int;
            tokens[indiceTokens++] = criarToken(tipo, palavra, linha);
            salvarToken(arquivoLex, tokens[indiceTokens - 1]);
        } else {
            caractere_id = 0;
            do {
                palavra[caractere_id++] = caractere;
                caractere = fgetc(arquivo);
            } while (!isalnum(caractere) && !isspace(caractere));

            palavra[caractere_id++] = '\0';
            tipoToken tipo = checarElemento(palavra);
            tokens[indiceTokens++] = criarToken(tipo, palavra, linha);
            salvarToken(arquivoLex, tokens[indiceTokens - 1]);
        }
    }

    tokens[indiceTokens++] = criarToken(tk_eof, "EOF", linha);
    fclose(arquivoLex);
}

token obterProximoToken() {
    if (indiceTokenAtual >= indiceTokens) {
        return tokens[indiceTokens - 1];
    }
    return tokens[indiceTokenAtual++];
}
