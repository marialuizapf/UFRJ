#ifndef BOMBA_H
#define BOMBA_H

#include <stdbool.h>  
#include "mapa.h"
#include "jogador.h"
#include "inimigo.h"
 

#define TEMPO_EXPLOSAO 3.0f  // segundos
#define RAIO_EXPLOSAO 5      // em tiles (5*20px = 100px)

typedef struct Bomba {
    int linha, coluna;
    float timer;            // tempo restante
    struct Bomba* next;     // para fila FIFO
    bool explodindo;
    float tempo_explosao; // tempo restante para mostrar o efeito
} Bomba;

typedef struct FilaBombas{
    Bomba* head;
    Bomba* tail;
} FilaBombas;

// Inicializa uma fila de bombas vazia
FilaBombas* criarFilaBombas(void);
// Libera toda a memoria da fila
void liberarFilaBombas(FilaBombas* fila);
// Planta uma bomba (decrementa estoque do jogador)
void plantarBomba(FilaBombas* fila, Jogador* jogador, Mapa* mapa);
void retirarBomba(FilaBombas* f, Jogador* j, Mapa* m);
// Atualiza timers, trata explosoes e recolhimento via fila FIFO
void atualizarBombas(FilaBombas* f, Jogador* j, Mapa* m, ListaInimigos* inimigos, float dt);
// Desenha todas as bombas na tela
void desenharBombas(FilaBombas* fila);

#endif // BOMBA_H