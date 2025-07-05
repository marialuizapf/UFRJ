#include <stdlib.h>
#include "raylib.h"
#include "jogador.h"
#include "bomba.h"

void desenharJogador(Jogador* jogador) {
    int x = jogador->coluna * 20;
    int y = jogador->linha * 20;
    DrawRectangle(x, y, 20, 20, WHITE);  
}

static bool podeMover(Jogador* jogador, Mapa* mapa, FilaBombas* fila, int l, int c) {
    if (l < 0 || l >= LINHAS || c < 0 || c >= COLUNAS) return false;
    char t = mapa->tiles[l][c];
    if (t == 'W' || t == 'D' || t == 'B' || t == 'K') return false;

    for (Bomba* b = fila->head; b; b = b->next) {
        if (b->linha == l && b->coluna == c) {
            // Permite mover para a bomba se o jogador já estiver lá
            if (jogador->linha == l && jogador->coluna == c) return true;
            return false;
        }
    }

    return true;
}


Jogador* criarJogador(Mapa* mapa) {
    Jogador* player = malloc(sizeof(Jogador));
    player->vidas = 3;
    player->pontuacao = 0;
    player->bombas = 3;
    player->direcao = DIR_BAIXO; // ou qualquer padrão

    for (int i=0;i<LINHAS;i++)
        for (int j=0;j<COLUNAS;j++)
            if (mapa->tiles[i][j]=='J') {
                player->linha=i; player->coluna=j;
                mapa->tiles[i][j]=' ';
                return player;
            }
    player->linha = 0; player->coluna = 0;
    return player;
}

void atualizarJogador(Jogador* jogador, Mapa* mapa, FilaBombas* fila) {
    int nx = jogador->coluna;
    int ny = jogador->linha;

    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        nx++;
        jogador->direcao = DIR_DIREITA;
    }
    else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        nx--;
        jogador->direcao = DIR_ESQUERDA;
    }
    else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        ny--;
        jogador->direcao = DIR_CIMA;
    }
    else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        ny++;
        jogador->direcao = DIR_BAIXO;
    }

    if ((nx != jogador->coluna || ny != jogador->linha) &&
    podeMover(jogador, mapa, fila, ny, nx)) {
        jogador->coluna = nx;
        jogador->linha = ny;
    }
}


