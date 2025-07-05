#include "pontuacao.h"

void pontuarInimigo(Jogador* jogador) {
    jogador->pontuacao += 20;
    if (jogador->pontuacao < 0) jogador->pontuacao = 0;
}

void pontuarCaixa(Jogador* jogador) {
    jogador->pontuacao += 10;
    TraceLog(LOG_INFO, "+10 pontos por caixa destruída");
}


void penalizarVida(Jogador* jogador) {
    jogador->vidas--;
    jogador->pontuacao -= 100;
    if (jogador->pontuacao < 0) jogador->pontuacao = 0;
    TraceLog(LOG_INFO, "-100 pontos por vida perdida");
}


void ajustarPontuacao(Jogador* jogador) {
    if (jogador->pontuacao < 0)
        jogador->pontuacao = 0;
}