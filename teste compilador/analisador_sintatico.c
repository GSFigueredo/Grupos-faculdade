#include <stdio.h>
#include <stdlib.h>
#include "analisador_sintatico.h"
#include "analisador_lexico.h"

// Variável global para o token atual
extern token tokenAtual;  // Definido em 'compilador.c'

// Função para verificar se o token atual é o esperado
void casaToken(tipoToken tokenEsperado) {
    if (tokenAtual.tipo == tokenEsperado) {
        tokenAtual = obterProximoToken();  // Chama o próximo token
    } else {
        printf("%d: token não esperado [%s].\n", tokenAtual.linha, tokenAtual.palavra);
        exit(1);  // Se não for o esperado, exibe erro e encerra
    }
}

// Função para analisar um programa
void programa() {
    casaToken(tk_program);
    casaToken(tk_id);  // Espera um identificador para o nome do programa
    casaToken(tk_pt_virg);
    bloco();  // Chama a análise do bloco de código
    casaToken(tk_pont);  // Finaliza o programa com o ponto
}

// Função para analisar um bloco de código
void bloco() {
    if (tokenAtual.tipo == tk_var) {
        parte_de_declaracoes_de_variaveis();  // Processa as declarações de variáveis
    }
    comando_composto();  // Processa os comandos compostos
}

// Função para analisar as declarações de variáveis
void parte_de_declaracoes_de_variaveis() {
    casaToken(tk_var);
    declaracao_de_variaveis();
    while (tokenAtual.tipo == tk_pt_virg) {
        casaToken(tk_pt_virg);
        declaracao_de_variaveis();
    }
    casaToken(tk_pt_virg);
}

// Função para analisar uma declaração de variável
void declaracao_de_variaveis() {
    lista_de_identificadores();
    casaToken(tk_dp);  // Espera o símbolo ":"
    tipo();  // Processa o tipo da variável
}

// Função para analisar uma lista de identificadores
void lista_de_identificadores() {
    casaToken(tk_id);  // Espera um identificador
    while (tokenAtual.tipo == tk_virg) {
        casaToken(tk_virg);
        casaToken(tk_id);  // Processa mais identificadores
    }
}

// Função para analisar o tipo da variável
void tipo() {
    if (tokenAtual.tipo == tk_integer) {
        casaToken(tk_integer);
    } else if (tokenAtual.tipo == tk_real) {
        casaToken(tk_real);
    } else {
        printf("%d: tipo não esperado [%s].\n", tokenAtual.linha, tokenAtual.palavra);
        exit(1);
    }
}

// Função para analisar comandos compostos
void comando_composto() {
    casaToken(tk_begin);
    comando();  // Processa o primeiro comando
    while (tokenAtual.tipo == tk_pt_virg) {
        casaToken(tk_pt_virg);
        comando();  // Processa os próximos comandos
    }
    casaToken(tk_end);  // Finaliza o comando composto com "end"
}

// Função para analisar comandos
void comando() {
    // Aqui você pode expandir para lidar com diferentes tipos de comandos
    // como atribuições, comandos condicionais, repetitivos, etc.
}
