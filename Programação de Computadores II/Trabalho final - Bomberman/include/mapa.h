#ifndef MAPA_H
#define MAPA_H

#include "raylib.h"

#define LINHAS 25
#define COLUNAS 60

typedef struct {
    char** tiles;               // Matriz de caracteres do mapa
    char nomeArquivo[64];      // Caminho do arquivo original
} Mapa;

// Aloca e carrega o mapa a partir de um arquivo texto (formato .txt)
Mapa* carregarMapa(const char* caminho);

// Desenha o mapa na tela usando Raylib (cada tile = 20x20 px)
void desenharMapa(Mapa* mapa, Texture2D chave, Texture2D caixa, Texture2D paredeInv, Texture2D paredeFraca);

// Libera toda a memória alocada para o mapa
void liberarMapa(Mapa* mapa);

#endif // MAPA_H