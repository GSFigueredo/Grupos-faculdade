#include <stdio.h>
#include <stdlib.h>
#include "analisador_lexico.h"
#include "analisador_sintatico.h"

extern token token_atual; 

void lerProximoToken(FILE *arquivoLex) {
    if (fscanf(arquivoLex, "Token: %d | Valor: %s | Linha: %d\n", (int *)&token_atual.tipo, token_atual.palavra, &token_atual.linha) == EOF) {
        token_atual.tipo = tk_eof;
    }
}

void CasaToken(tipoToken esperado, FILE *arquivoLex) {
    if (token_atual.tipo == esperado) {
        lerProximoToken(arquivoLex);
    } else {
        printf("%d: token nao esperado [%s].\n", token_atual.linha, token_atual.palavra);
        exit(1);
    }
}

void Programa(FILE *arquivoLex) {
    CasaToken(tk_program, arquivoLex);
    CasaToken(tk_id, arquivoLex);
    CasaToken(tk_pt_virg, arquivoLex);
    Bloco(arquivoLex);
    CasaToken(tk_pont, arquivoLex);
}

void Bloco(FILE *arquivoLex) {
    ParteDeDeclaracoesVariaveis(arquivoLex);
    ComandoComposto(arquivoLex);
}

void ParteDeDeclaracoesVariaveis(FILE *arquivoLex) {
    if (token_atual.tipo == tk_var) {
        CasaToken(tk_var, arquivoLex);
        DeclaracaoVariaveis(arquivoLex);
        while (token_atual.tipo == tk_pt_virg) {
            CasaToken(tk_pt_virg, arquivoLex);
            DeclaracaoVariaveis(arquivoLex);
        }
        CasaToken(tk_pt_virg, arquivoLex);
    }
}

void DeclaracaoVariaveis(FILE *arquivoLex) {
    ListaDeIdentificadores(arquivoLex);
    CasaToken(tk_dp, arquivoLex);
    Tipo(arquivoLex);
}

void ListaDeIdentificadores(FILE *arquivoLex) {
    CasaToken(tk_id, arquivoLex);
    while (token_atual.tipo == tk_virg) {
        CasaToken(tk_virg, arquivoLex);
        CasaToken(tk_id, arquivoLex);
    }
}

void Tipo(FILE *arquivoLex) {
    if (token_atual.tipo == tk_integer) {
        CasaToken(tk_integer, arquivoLex);
    } else if (token_atual.tipo == tk_real) {
        CasaToken(tk_real, arquivoLex);
    } else {
        printf("%d: token nao esperado [%s].\n", token_atual.linha, token_atual.palavra);
        exit(1);
    }
}

void ComandoComposto(FILE *arquivoLex) {
    CasaToken(tk_begin, arquivoLex);
    Comando(arquivoLex);
    while (token_atual.tipo == tk_pt_virg) {
        CasaToken(tk_pt_virg, arquivoLex);
        Comando(arquivoLex);
    }
    CasaToken(tk_end, arquivoLex);
}

void Comando(FILE *arquivoLex) {
    if (token_atual.tipo == tk_id) {
        Atribuicao(arquivoLex);
    } else if (token_atual.tipo == tk_begin) {
        ComandoComposto(arquivoLex);
    } else if (token_atual.tipo == tk_if) {
        ComandoCondicional(arquivoLex);
    } else if (token_atual.tipo == tk_while) {
        ComandoRepetitivo(arquivoLex);
    } else {
        printf("%d: token nao esperado [%s].\n", token_atual.linha, token_atual.palavra);
        exit(1);
    }
}

void Atribuicao(FILE *arquivoLex) {
    CasaToken(tk_id, arquivoLex);
    CasaToken(tk_dp_eq, arquivoLex);
    Expressao(arquivoLex);
}

void ComandoCondicional(FILE *arquivoLex) {
    CasaToken(tk_if, arquivoLex);
    Expressao(arquivoLex);
    CasaToken(tk_then, arquivoLex);
    Comando(arquivoLex);
    if (token_atual.tipo == tk_else) {
        CasaToken(tk_else, arquivoLex);
        Comando(arquivoLex);
    }
}

void ComandoRepetitivo(FILE *arquivoLex) {
    CasaToken(tk_while, arquivoLex);
    Expressao(arquivoLex);
    CasaToken(tk_do, arquivoLex);
    Comando(arquivoLex);
}

void Expressao(FILE *arquivoLex) {
    ExpressaoSimples(arquivoLex);
    if (token_atual.tipo == tk_maior || token_atual.tipo == tk_menor ||
        token_atual.tipo == tk_maior_eq || token_atual.tipo == tk_menor_eq ||
        token_atual.tipo == tk_eq || token_atual.tipo == tk_dif) {
        CasaToken(token_atual.tipo, arquivoLex);
        ExpressaoSimples(arquivoLex);
    }
}

void ExpressaoSimples(FILE *arquivoLex) {
    Termo(arquivoLex);
    while (token_atual.tipo == tk_som || token_atual.tipo == tk_sub) {
        CasaToken(token_atual.tipo, arquivoLex);
        Termo(arquivoLex);
    }
}

void Termo(FILE *arquivoLex) {
    Fator(arquivoLex);
    while (token_atual.tipo == tk_mult || token_atual.tipo == tk_div) {
        CasaToken(token_atual.tipo, arquivoLex);
        Fator(arquivoLex);
    }
}

void Fator(FILE *arquivoLex) {
    if (token_atual.tipo == tk_id) {
        CasaToken(tk_id, arquivoLex);
    } else if (token_atual.tipo == tk_int) {
        CasaToken(tk_int, arquivoLex);
    } else if (token_atual.tipo == tk_real_num) {
        CasaToken(tk_real_num, arquivoLex);
    } else if (token_atual.tipo == tk_eparen) {
        CasaToken(tk_eparen, arquivoLex);
        Expressao(arquivoLex);
        CasaToken(tk_dparen, arquivoLex);
    } else {
        printf("%d: token nao esperado [%s].\n", token_atual.linha, token_atual.palavra);
        exit(1);
    }
}

void analisadorSintatico(FILE *arquivoLex) {
    lerProximoToken(arquivoLex);
    Programa(arquivoLex);
}
