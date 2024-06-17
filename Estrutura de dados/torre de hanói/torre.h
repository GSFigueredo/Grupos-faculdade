#ifndef TORRE_H
#define TORRE_H

typedef struct {
    int discos[10];
    int topo;
} Pilha;

void iniciarPilhaVazia(Pilha* pilha);
void adicionarPilha(Pilha* pilha, int tamanho);
int removerPilha(Pilha* pilha);
void mostrarPilhas(Pilha* torres, int numeroDiscos);
int mudarDisco(Pilha* torres, int origem, int destino);
void iniciarJogo(Pilha* torres, int numeroDiscos);
int checarFim(Pilha* torres, int numeroDiscos);
int main ();

#endif