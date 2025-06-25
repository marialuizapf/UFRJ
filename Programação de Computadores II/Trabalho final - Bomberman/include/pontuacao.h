#ifndef PONTUACAO_H
#define PONTUACAO_H

#include "jogador.h"

// Atualiza pontuacao ao explodir inimigo
void pontuarInimigo(Jogador* jogador);
// Atualiza pontuacao ao explodir caixa ou obstaculo destrutivel
void pontuarCaixa(Jogador* jogador);
// Penaliza vida perdida
void penalizarVida(Jogador* jogador);
// Garante que pontuacao nao fique negativa
void ajustarPontuacao(Jogador* jogador);

#endif // PONTUACAO_H