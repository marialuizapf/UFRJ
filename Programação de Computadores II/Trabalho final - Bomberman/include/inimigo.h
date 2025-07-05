#ifndef INIMIGO_H
#define INIMIGO_H

#include "mapa.h"
#include "jogador.h"

typedef struct Inimigo {
    int linha, coluna;
    int direcao;
    float tempoTroca;        
    float tempoMovimento;    
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
#define RAIO_EXPLOSAO 5
void eliminarInimigosExplodidos(ListaInimigos* lista, int linha, int coluna);

#endif // INIMIGO_H