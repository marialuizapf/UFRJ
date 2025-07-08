#ifndef PONTUACAO_H
#define PONTUACAO_H

#include "jogador.h"

// Adiciona pontos ao eliminar um inimigo
void pontuarInimigo(Jogador* jogador);

// Adiciona pontos ao destruir caixa ou bloco
void pontuarCaixa(Jogador* jogador);

// Penaliza pontos e vidas ao jogador
void penalizarVida(Jogador* jogador);

// Garante que a pontuação não fique negativa
void ajustarPontuacao(Jogador* jogador);

#endif // PONTUACAO_H