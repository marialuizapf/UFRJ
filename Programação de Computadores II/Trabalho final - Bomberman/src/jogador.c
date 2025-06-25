#include <stdlib.h>
#include "raylib.h"
#include "jogador.h"
#include "bomba.h"

void desenharJogador(Jogador* jogador) {
    int x = jogador->coluna * 20;
    int y = jogador->linha * 20;
    DrawRectangle(x, y, 20, 20, WHITE);  // ou outra cor que preferir
}

static bool podeMover(Mapa* mapa, FilaBombas* fila, int l, int c) {
    if (l < 0 || l >= LINHAS || c < 0 || c >= COLUNAS) return false;
    char t = mapa->tiles[l][c];
    if (t=='W'||t=='D'||t=='B'||t=='K') return false;
    for (Bomba* b = fila->head; b; b = b->next) {
        if (b->linha==l && b->coluna==c) return false;
    }
    return true;
}

Jogador* criarJogador(Mapa* mapa) {
    Jogador* player = malloc(sizeof(Jogador));
    player->vidas = 3;
    player->pontuacao = 0;
    player->bombas = 3;
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
    int nx=jogador->coluna, ny=jogador->linha;
    if (IsKeyDown(KEY_RIGHT)||IsKeyDown(KEY_D)) nx++;
    else if (IsKeyDown(KEY_LEFT)||IsKeyDown(KEY_A)) nx--;
    else if (IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)) ny--;
    else if (IsKeyDown(KEY_DOWN)||IsKeyDown(KEY_S)) ny++;
    if ((nx!=jogador->coluna||ny!=jogador->linha) && podeMover(mapa,fila,ny,nx)) {
        jogador->coluna=nx; jogador->linha=ny;
    }
}

