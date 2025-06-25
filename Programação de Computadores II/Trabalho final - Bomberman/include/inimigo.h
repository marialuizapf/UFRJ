#ifndef INIMIGO_H
#define INIMIGO_H

#include "mapa.h"

// Direcoes de movimento
#define DIR_CIMA    0
#define DIR_BAIXO   1
#define DIR_ESQUERDA 2
#define DIR_DIREITA 3

typedef struct Inimigo {
    int linha, coluna;
    int direcao;        // 0=Cima,1=Baixo,2=Esq,3=Dir
    float tempoTroca;   // tempo para sortear nova direcao
    struct Inimigo* next;
} Inimigo;

// Lista encadeada de inimigos
typedef struct {
    Inimigo* head;
} ListaInimigos;

// Cria lista de inimigos baseado em 'E' no mapa
ListaInimigos* criarListaInimigos(Mapa* mapa);
// Atualiza movimento aleatorio de cada inimigo
void atualizarInimigos(ListaInimigos* lista, Mapa* mapa, float dt);
// Desenha inimigos na tela (20x20px cada)
void desenharInimigos(ListaInimigos* lista);
// Libera memoria da lista de inimigos
void liberarInimigos(ListaInimigos* lista);

#endif // INIMIGO_H