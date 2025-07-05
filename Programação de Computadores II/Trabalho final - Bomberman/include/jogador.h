#ifndef JOGADOR_H
#define JOGADOR_H

#include "mapa.h"

#define TEMPO_PASSO 0.1f  // Intervalo entre movimentos 

typedef struct FilaBombas FilaBombas;
typedef enum {
    DIR_CIMA,
    DIR_BAIXO,
    DIR_ESQUERDA,
    DIR_DIREITA
} Direcao;

typedef struct Jogador {
    int linha, coluna;  
    int vidas;
    int pontuacao;
    int bombas;
    int chaves; 
    float tempoMovimento;
    Direcao direcao;
    float invulneravel;
} Jogador;

// Cria jogador e posiciona na posicao do caractere 'J' no mapa
Jogador* criarJogador(Mapa* mapa);
// Atualiza a posicao do jogador com base em input e colisoes
void atualizarJogador(Jogador* jogador, Mapa* mapa, FilaBombas* fila, float dt);

void desenharJogador(Jogador* jogador);

#endif