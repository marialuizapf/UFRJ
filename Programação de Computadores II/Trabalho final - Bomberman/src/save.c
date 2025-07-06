#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "bomba.h"
#include "inimigo.h"

void salvarJogo(const char* filename, Jogo* jogo) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) return;

    // 1.) Fase atual
    fwrite(&jogo->faseAtual, sizeof(int), 1, fp);

    // 2) Escreve os dados do jogador sua posição e a fase atual
    fwrite(&jogo->player->linha, sizeof(int), 1, fp);
    fwrite(&jogo->player->coluna, sizeof(int), 1, fp);
    fwrite(&jogo->player->vidas, sizeof(int), 1, fp);
    fwrite(&jogo->player->chaves, sizeof(int), 1, fp);
    fwrite(&jogo->player->pontuacao, sizeof(int), 1, fp);
    fwrite(&jogo->player->bombas, sizeof(int), 1, fp);

    // 3) Escreve o mapa com suas alterações
    for (int i = 0; i < LINHAS; i++)
        fwrite(jogo->mapa->tiles[i], sizeof(char), COLUNAS, fp);
    
    // 4) Escreve as bombas
    int countB = 0; for (Bomba* b = jogo->bombas->head; b; b = b->next) countB++;
    fwrite(&countB, sizeof(int), 1, fp);
    for (Bomba* b = jogo->bombas->head; b; b = b->next) {
        fwrite(&b->linha, sizeof(int), 1, fp);
        fwrite(&b->coluna, sizeof(int), 1, fp);
        fwrite(&b->timer, sizeof(float), 1, fp);
    }

    // 5) Escreve os inimigos
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
    // Abre o arquivo para leitura binária
    FILE* fp = fopen(filename, "rb");
    if (!fp) return NULL;

    // Aloca memória para o jogo e o jogador
    Jogo* jogo = malloc(sizeof(Jogo)); 
    if (!jogo) return NULL;
    jogo->player = malloc(sizeof(Jogador)); 
    if (!jogo->player) { free(jogo); fclose(fp); return NULL;}

    // 1) Lê a fase atual
    fread(&jogo->faseAtual, sizeof(int), 1, fp);

    // 1.1) Monta o caminho completo do arquivo de mapa
    char caminho[64];
    snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", jogo->faseAtual);

    // 2) Carrega dados do jogador
    fread(&jogo->player->linha,     sizeof(int),   1, fp);
    fread(&jogo->player->coluna,    sizeof(int),   1, fp);
    fread(&jogo->player->vidas,     sizeof(int),   1, fp);
    fread(&jogo->player->chaves,    sizeof(int),   1, fp);
    fread(&jogo->player->pontuacao, sizeof(int),   1, fp);
    fread(&jogo->player->bombas,    sizeof(int),   1, fp);
    

    // Carrega o mapa
    jogo->mapa = carregarMapa(caminho); // já aloca e preenche tiles

    // 3) Sobrescreve os tiles com as alterações salvas
    for (int i = 0; i < LINHAS; i++) {
        fread(jogo->mapa->tiles[i], sizeof(char), COLUNAS, fp);
    }

    // 4) Carrega bombas
    jogo->bombas = criarFilaBombas();
    int countB;
    fread(&countB, sizeof(int), 1, fp);
    for (int i = 0; i < countB; i++) {
        Bomba* b = malloc(sizeof(Bomba));
        fread(&b->linha, sizeof(int), 1, fp);
        fread(&b->coluna, sizeof(int), 1, fp);
        fread(&b->timer, sizeof(float), 1, fp);
        b->next = NULL;

        if (!jogo->bombas->head) jogo->bombas->head = b;
        else jogo->bombas->tail->next = b;
        jogo->bombas->tail = b;
    }

    // 5) Carrega inimigos
    jogo->inimigos = malloc(sizeof(ListaInimigos));
    jogo->inimigos->head = NULL;
    int countI;
    fread(&countI, sizeof(int), 1, fp);
    Inimigo* last = NULL;
    for (int i = 0; i < countI; i++) {
        Inimigo* in = malloc(sizeof(Inimigo));
        fread(&in->linha, sizeof(int), 1, fp);
        fread(&in->coluna, sizeof(int), 1, fp);
        fread(&in->direcao, sizeof(int), 1, fp);
        fread(&in->tempoTroca, sizeof(float), 1, fp);
        in->next = NULL;

        if (!jogo->inimigos->head) jogo->inimigos->head = in;
        else last->next = in;
        last = in;
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
    //free(jogo);
}