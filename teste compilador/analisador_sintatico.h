#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H
#include "analisador_lexico.h"

// Declarações das funções para análise sintática
void programa();
void bloco();
void parte_de_declaracoes_de_variaveis();
void declaracao_de_variaveis();
void lista_de_identificadores();
void tipo();
void comando_composto();
void comando();
void casaToken(tipoToken tokenEsperado);

#endif
