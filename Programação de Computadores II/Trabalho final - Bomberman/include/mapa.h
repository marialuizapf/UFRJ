#ifndef MAPA_H
#define MAPA_H

#define LINHAS 25
#define COLUNAS 60

typedef struct {
    char** tiles;
    char nomeArquivo[64];
} Mapa;

// Aloca e carrega o mapa a partir de um arquivo texto
Mapa* carregarMapa(const char* nomeArquivo);
// Desenha o mapa usando Raylib (cada tile 20x20 px), incluindo HUD no rodapé
void desenharMapa(Mapa* mapa);
// Libera a memoria do mapa
void liberarMapa(Mapa* mapa);

#endif // MAPA_H