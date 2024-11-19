#ifndef TOKENS_H
#define TOKENS_H

typedef enum {
    tk_program,   // "program" -------- token: 0
    tk_var,       // "var" -------- token: 1
    tk_begin,     // "begin" -------- token: 2
    tk_end,       // "end" -------- token: 3
    tk_integer,   // "integer" -------- token: 4
    tk_real,      // "real" -------- token: 5
    tk_if,        // "if" -------- token: 6
    tk_then,      // "then" -------- token: 7
    tk_else,      // "else" -------- token: 8
    tk_while,     // "while" -------- token: 9
    tk_do,        // "do" -------- token: 10
// ------------------------------------------------------------ //
    tk_dp_eq,    // ":=" -------- token: 11
    tk_som,      // "+" -------- token: 12
    tk_sub,      // "-" -------- token: 13
    tk_mult,     // "*" -------- token: 14
    tk_div,      // "/" -------- token: 15 
    tk_maior,    // ">" -------- token: 16
    tk_menor,    // "<" -------- token: 17
    tk_maior_eq, // ">=" -------- token: 18
    tk_menor_eq, // "<=" -------- token: 19
    tk_eq,       // "=" -------- token: 20
    tk_dif,      // "<>" -------- token: 21
// ------------------------------------------------------------ //
    tk_pt_virg,  // ";" -------- token: 22
    tk_dp,       // ":" -------- token: 23
    tk_virg,     // "," -------- token: 24
    tk_pont,     // "." -------- token: 25
    tk_eparen,   // "(" -------- token: 26
    tk_dparen,   // ")" -------- token: 27
    tk_id,       // Identificadores (ex: "x", "y", "z") -------- token: 28
    tk_int,      // Números inteiros (ex: 10, 20) -------- token: 29
    tk_real_num, // Números reais (ex: 2.5, 1.5) -------- token: 30
// ------------------------------------------------------------ //
    tk_eof,      // Fim de arquivo -------- token: 31
    tk_desconhecido   // Qualquer outro caractere não reconhecido -------- token: 32
} tipoToken;

#define MAX_TK 100 
typedef struct {
    tipoToken tipo;
    char palavra[MAX_TK];
    int linha;
} token;

#endif