#ifndef BOMBA_H
#define BOMBA_H

#include <stdbool.h>  
#include "mapa.h"
#include "jogador.h"
#include "inimigo.h"
 

#define TEMPO_EXPLOSAO 3.0f  
#define RAIO_EXPLOSAO 5      

typedef struct Bomba {
    int linha, coluna;           // Posição da bomba no mapa
    float timer;                 // Tempo restante para explosão
    float tempo_explosao;        // Tempo para exibir a explosão
    bool explodindo;             // Estado da bomba
    struct Bomba* next;          // Ponteiro para próxima bomba (fila encadeada)

    
    Texture2D sprite_bomba; 
    Texture2D sprite_explosao;  

    int frameAtual;
    int frameTotal;
    float frameTime;
    float timer_anima;

    int frameExplosaoAtual;
    int frameExplosaoTotal;
    float frameExplosaoTime;
    float timer_explosao_anima;
} Bomba;


typedef struct FilaBombas {
    Bomba* head;                 // Início da fila (bomba mais antiga)
    Bomba* tail;                 // Fim da fila (bomba mais recente)
} FilaBombas;

// Inicializa uma fila de bombas vazia
FilaBombas* criarFilaBombas(void);

// Libera toda a memória da fila de bombas
void liberarFilaBombas(FilaBombas* fila);

// Planta uma bomba na frente do jogador, se possível
void plantarBomba(FilaBombas* fila, Jogador* jogador, Mapa* mapa, Texture2D sprite_bomba, Texture2D sprite_explosao);

// Retira uma bomba (caso esteja ativa e próxima ao jogador)
void retirarBomba(FilaBombas* fila, Jogador* jogador, Mapa* mapa);

// Atualiza todas as bombas da fila (timers, explosões, interações)
void atualizarBombas(FilaBombas* fila, Jogador* jogador, Mapa* mapa, ListaInimigos* inimigos, float dt);

// Desenha todas as bombas na tela
void desenharBombas(FilaBombas* fila);

#endif // BOMBA_H