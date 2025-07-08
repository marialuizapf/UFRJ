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

// Salva o estado do jogo em arquivo binário
void salvarJogo(const char* filename, Jogo* jogo);

// Carrega o estado do jogo de um arquivo binário
Jogo* carregarJogo(const char* filename, Texture2D texJogador, Texture2D texInimigo, Texture2D texBomba, Texture2D texExplosao);

// Libera toda a memória associada ao jogo
void liberarJogo(Jogo* jogo);

#endif // SAVE_H