#ifndef ANALISADOR_SINTATICO_H
#define ANALISADOR_SINTATICO_H

#include <stdio.h>
#include "analisador_lexico.h"

void analisadorSintatico(FILE *arquivoLex);
void Programa(FILE *arquivoLex);
void Bloco(FILE *arquivoLex);
void ParteDeDeclaracoesVariaveis(FILE *arquivoLex);
void DeclaracaoVariaveis(FILE *arquivoLex);
void ListaDeIdentificadores(FILE *arquivoLex);
void Tipo(FILE *arquivoLex);
void ComandoComposto(FILE *arquivoLex);
void Comando(FILE *arquivoLex);
void Atribuicao(FILE *arquivoLex);
void ComandoCondicional(FILE *arquivoLex);
void ComandoRepetitivo(FILE *arquivoLex);
void Expressao(FILE *arquivoLex);
void ExpressaoSimples(FILE *arquivoLex);
void Termo(FILE *arquivoLex);
void Fator(FILE *arquivoLex);

extern token token_atual;

#endif
