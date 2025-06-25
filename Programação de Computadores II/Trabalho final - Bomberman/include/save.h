#ifndef SAVE_H
#define SAVE_H

#include "jogador.h"
#include "mapa.h"
#include "bomba.h"
#include "inimigo.h"

// Estado completo do jogo para salvar/carregar
typedef struct {
    Jogador* player;
    Mapa* mapa;
    FilaBombas* bombas;
    ListaInimigos* inimigos;
    int faseAtual;
} Jogo;

// Salva estado em arquivo binario
void salvarJogo(const char* filename, Jogo* jogo);
// Carrega estado de arquivo binario
Jogo* carregarJogo(const char* filename);
// Libera toda a memoria de Jogo
void liberarJogo(Jogo* jogo);

#endif // SAVE_H