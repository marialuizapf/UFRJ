#ifndef JOGADOR_H
#define JOGADOR_H

#include "mapa.h"

#define TEMPO_PASSO 0.1f  // Intervalo entre movimentos 

// Encaminhamento da declaração da estrutura FilaBombas
typedef struct FilaBombas FilaBombas;

// Enum: Direção de movimento do jogador
typedef enum {
    DIR_CIMA,
    DIR_BAIXO,
    DIR_ESQUERDA,
    DIR_DIREITA
} Direcao;

typedef struct Jogador {
    int linha, coluna;           // Posição no mapa
    int vidas;                   // Total de vidas restantes
    int pontuacao;               // Pontuação acumulada
    int bombas;                  // Bombas disponíveis para plantar
    int chaves;                  // Chaves coletadas
    float tempoMovimento;        // Timer para controlar frequência de movimento
    Direcao direcao;             // Direção atual do jogador
    float invulneravel;          // Tempo restante de invulnerabilidade

    Texture2D sprite;
    int frameAtual;
    int frameTotal;
    float frameTime;
    float timer;
} Jogador;

// Cria e posiciona o jogador baseado na posição do caractere 'J' no mapa
Jogador* criarJogador(Mapa* mapa, Texture2D sprite);

// Atualiza a posição do jogador com base nos inputs e colisões
void atualizarJogador(Jogador* jogador, Mapa* mapa, FilaBombas* fila, float dt);

// Desenha o jogador na tela (com efeito de invulnerabilidade, se ativo)
void desenharJogador(Jogador* jogador);

#endif