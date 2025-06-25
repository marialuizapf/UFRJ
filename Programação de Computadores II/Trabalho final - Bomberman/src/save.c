#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "bomba.h"
#include "inimigo.h"

void salvarJogo(const char* filename, Jogo* jogo) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) return;
    fwrite(&jogo->faseAtual, sizeof(int), 1, fp);
    fwrite(&jogo->player->linha, sizeof(int), 1, fp);
    fwrite(&jogo->player->coluna, sizeof(int), 1, fp);
    fwrite(&jogo->player->vidas, sizeof(int), 1, fp);
    fwrite(&jogo->player->pontuacao, sizeof(int), 1, fp);
    fwrite(&jogo->player->bombas, sizeof(int), 1, fp);
    for (int i = 0; i < LINHAS; i++)
        fwrite(jogo->mapa->tiles[i], sizeof(char), COLUNAS, fp);
    int countB = 0; for (Bomba* b = jogo->bombas->head; b; b = b->next) countB++;
    fwrite(&countB, sizeof(int), 1, fp);
    for (Bomba* b = jogo->bombas->head; b; b = b->next) {
        fwrite(&b->linha, sizeof(int), 1, fp);
        fwrite(&b->coluna, sizeof(int), 1, fp);
        fwrite(&b->timer, sizeof(float), 1, fp);
    }
    int countI = 0; for (Inimigo* in = jogo->inimigos->head; in; in = in->next) countI++;
    fwrite(&countI, sizeof(int), 1, fp);
    for (Inimigo* in = jogo->inimigos->head; in; in = in->next) {
        fwrite(&in->linha, sizeof(int), 1, fp);
        fwrite(&in->coluna, sizeof(int), 1, fp);
        fwrite(&in->direcao, sizeof(int), 1, fp);
        fwrite(&in->tempoTroca, sizeof(float), 1, fp);
    }
    fclose(fp);
}

Jogo* carregarJogo(const char* filename) {
    FILE* fp = fopen(filename, "rb"); if (!fp) return NULL;
    Jogo* jogo = malloc(sizeof(Jogo));
    jogo->player = malloc(sizeof(Jogador));
    jogo->mapa = malloc(sizeof(Mapa));
    jogo->mapa->tiles = malloc(sizeof(char*) * LINHAS);
    jogo->bombas = criarFilaBombas();
    jogo->inimigos = malloc(sizeof(ListaInimigos)); jogo->inimigos->head = NULL;
    fread(&jogo->faseAtual, sizeof(int), 1, fp);
    fread(&jogo->player->linha, sizeof(int), 1, fp);
    fread(&jogo->player->coluna, sizeof(int), 1, fp);
    fread(&jogo->player->vidas, sizeof(int), 1, fp);
    fread(&jogo->player->pontuacao, sizeof(int), 1, fp);
    fread(&jogo->player->bombas, sizeof(int), 1, fp);
    for (int i = 0; i < LINHAS; i++) {
        jogo->mapa->tiles[i] = malloc(sizeof(char) * COLUNAS);
        fread(jogo->mapa->tiles[i], sizeof(char), COLUNAS, fp);
    }
    int countB; fread(&countB, sizeof(int), 1, fp);
    for (int k=0; k<countB; k++) {
        Bomba* b = malloc(sizeof(Bomba));
        fread(&b->linha, sizeof(int), 1, fp);
        fread(&b->coluna, sizeof(int), 1, fp);
        fread(&b->timer, sizeof(float), 1, fp);
        b->next = NULL;
        if (!jogo->bombas->head) jogo->bombas->head = b;
        else jogo->bombas->tail->next = b;
        jogo->bombas->tail = b;
    }
    int countI; fread(&countI, sizeof(int), 1, fp);
    Inimigo* lastI = NULL;
    for (int k=0; k<countI; k++) {
        Inimigo* in = malloc(sizeof(Inimigo));
        fread(&in->linha, sizeof(int), 1, fp);
        fread(&in->coluna, sizeof(int), 1, fp);
        fread(&in->direcao, sizeof(int), 1, fp);
        fread(&in->tempoTroca, sizeof(float), 1, fp);
        in->next = NULL;
        if (!jogo->inimigos->head) jogo->inimigos->head = in;
        else lastI->next = in;
        lastI = in;
    }
    fclose(fp);
    return jogo;
}

void liberarJogo(Jogo* jogo) {
    free(jogo->player);
    for (int i=0; i<LINHAS; i++) free(jogo->mapa->tiles[i]);
    free(jogo->mapa->tiles);
    free(jogo->mapa);
    liberarFilaBombas(jogo->bombas);
    liberarInimigos(jogo->inimigos);
    free(jogo);
}