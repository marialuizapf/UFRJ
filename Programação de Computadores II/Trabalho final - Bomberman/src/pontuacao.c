#include "pontuacao.h"

void pontuarInimigo(Jogador* jogador) {
    jogador->pontuacao += 20;
    if (jogador->pontuacao < 0) jogador->pontuacao = 0;
}

void pontuarCaixa(Jogador* jogador) {
    jogador->pontuacao += 10;
    if (jogador->pontuacao < 0) jogador->pontuacao = 0;
}

void penalizarVida(Jogador* jogador) {
    jogador->pontuacao -= 100;
    jogador->vidas--;
    if (jogador->pontuacao < 0) jogador->pontuacao = 0;
}

void ajustarPontuacao(Jogador* jogador) {
    if (jogador->pontuacao < 0)
        jogador->pontuacao = 0;
}