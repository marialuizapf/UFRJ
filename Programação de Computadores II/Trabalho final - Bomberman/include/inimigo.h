#ifndef INIMIGO_H
#define INIMIGO_H

#include "mapa.h"
#include "jogador.h"

typedef struct Inimigo {
    int linha, coluna;             // Posição no mapa
    int direcao;                   // Direção atual de movimento
    float tempoTroca;              // Tempo até trocar de direção
    float tempoMovimento;          // Tempo até próximo movimento
    struct Inimigo* next;          // Ponteiro para próximo inimigo (lista encadeada)

    Texture2D sprite;
    int frameAtual;
    int frameTotal;
    float frameTime;
    float timer;
} Inimigo;

// Lista encadeada de inimigos
typedef struct {
    Inimigo* head;                
} ListaInimigos;

// Cria e retorna lista de inimigos com base nas posições 'E' do mapa
ListaInimigos* criarListaInimigos(Mapa* mapa, Texture2D sprite);

// Atualiza movimento e interação dos inimigos com o mapa, jogador e bombas
void atualizarInimigos(ListaInimigos* lista, Mapa* mapa, FilaBombas* bombas, Jogador* jogador, float dt);

// Desenha todos os inimigos na tela (20x20px, cor fixa)
void desenharInimigos(ListaInimigos* lista);

// Elimina inimigos atingidos por uma explosão
void eliminarInimigosExplodidos(ListaInimigos* lista, int linha, int coluna, Jogador* jogador);

// Verifica se há um inimigo na posição (linha, coluna), ignorando um específico
bool temInimigoNaPosicao(ListaInimigos* lista, int linha, int coluna, Inimigo* ignorar);

// Libera toda a memória associada à lista de inimigos
void liberarInimigos(ListaInimigos* lista);

#endif // INIMIGO_H