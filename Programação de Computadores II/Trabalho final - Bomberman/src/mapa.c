#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "mapa.h"

Mapa* carregarMapa(const char* nomeArquivo) {
    FILE* fp = fopen(nomeArquivo, "r");
    if (!fp) {
        perror("Erro ao abrir mapa");
        exit(EXIT_FAILURE);
    }
    Mapa* mapa = malloc(sizeof(Mapa));
    mapa->tiles = malloc(sizeof(char*) * LINHAS);
    for (int i = 0; i < LINHAS; i++) {
        mapa->tiles[i] = malloc(sizeof(char) * (COLUNAS + 1));
        if (fgets(mapa->tiles[i], COLUNAS + 2, fp) == NULL) {
            fprintf(stderr, "Formato de mapa inválido na linha %d\n", i);
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
    return mapa;
}

void desenharMapa(Mapa* mapa) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            char tile = mapa->tiles[i][j];
            int x = j * 20;
            int y = i * 20;
            switch (tile) {
                case 'W': DrawRectangle(x, y, 20, 20, GRAY); break; // Parede indestrutível
                case 'D': DrawRectangle(x, y, 20, 20, BROWN); break; // Bloco destrutível
                case 'B': DrawRectangle(x, y, 20, 20, YELLOW); break; // Bomba
                case 'K': DrawRectangle(x, y, 20, 20, YELLOW); break; // Chave
                default:  DrawRectangle(x, y, 20, 20, BLUE); break; // Espaço vazio
            }
        }
    }
}

void liberarMapa(Mapa* mapa) {
    for (int i = 0; i < LINHAS; i++) free(mapa->tiles[i]);
    free(mapa->tiles);
    free(mapa);
}