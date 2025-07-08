#include "pontuacao.h"

// ============================================
// FUNÇÃO: pontuarInimigo
// Descrição: Adiciona 20 pontos ao eliminar um inimigo
// ============================================
void pontuarInimigo(Jogador* jogador) {
    jogador->pontuacao += 20;

    // Garante que a pontuação nunca fique negativa
    if (jogador->pontuacao < 0)
        jogador->pontuacao = 0;
}

// ============================================
// FUNÇÃO: pontuarCaixa
// Descrição: Adiciona 10 pontos ao destruir uma caixa
// ============================================
void pontuarCaixa(Jogador* jogador) {
    jogador->pontuacao += 10;

    // Log de feedback (aparece no console se LOG_INFO estiver ativado)
    TraceLog(LOG_INFO, "+10 pontos por caixa destruída");
}

// ============================================
// FUNÇÃO: penalizarVida
// Descrição: Penaliza o jogador ao perder uma vida:
//            -1 vida e -100 pontos
// ============================================
void penalizarVida(Jogador* jogador) {
    jogador->vidas--;
    jogador->pontuacao -= 100;

    if (jogador->pontuacao < 0)
        jogador->pontuacao = 0;

    TraceLog(LOG_INFO, "-100 pontos por vida perdida");
}

// ============================================
// FUNÇÃO: ajustarPontuacao
// Descrição: Corrige pontuação negativa, se houver
// ============================================
void ajustarPontuacao(Jogador* jogador) {
    if (jogador->pontuacao < 0)
        jogador->pontuacao = 0;
}
