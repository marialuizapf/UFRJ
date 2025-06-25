#ifndef JOGADOR_H
#define JOGADOR_H

#include "mapa.h"

#define VELOCIDADE 1  // tiles por frame

typedef struct FilaBombas FilaBombas;

typedef struct Jogador {
    int linha, coluna;  // Posicao em tiles
    int vidas;
    int pontuacao;
    int bombas;
} Jogador;

// Cria jogador e posiciona na posicao do caractere 'J' no mapa
Jogador* criarJogador(Mapa* mapa);
// Atualiza a posicao do jogador com base em input e colisoes
void atualizarJogador(Jogador* jogador, Mapa* mapa, FilaBombas* fila);

void desenharJogador(Jogador* jogador);

#endif