#include <stdio.h>
#include <stdlib.h>
#include "save.h"
#include "bomba.h"
#include "inimigo.h"

// =======================================
// FUNÇÃO: salvarJogo
// Descrição: Salva o estado atual do jogo em um arquivo binário
// =======================================
void salvarJogo(const char* filename, Jogo* jogo) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) return;

    // 1. Salva a fase atual
    fwrite(&jogo->faseAtual, sizeof(int), 1, fp);

    // 2. Salva os dados do jogador
    fwrite(&jogo->player->linha,     sizeof(int), 1, fp);
    fwrite(&jogo->player->coluna,    sizeof(int), 1, fp);
    fwrite(&jogo->player->vidas,     sizeof(int), 1, fp);
    fwrite(&jogo->player->chaves,    sizeof(int), 1, fp);
    fwrite(&jogo->player->pontuacao, sizeof(int), 1, fp);
    fwrite(&jogo->player->bombas,    sizeof(int), 1, fp);
    fwrite(&jogo->player->direcao, sizeof(int), 1, fp);

    // 3. Salva os tiles do mapa (com possíveis alterações em tempo de jogo)
    for (int i = 0; i < LINHAS; i++)
        fwrite(jogo->mapa->tiles[i], sizeof(char), COLUNAS, fp);

    // 4. Salva as bombas
    int countB = 0;
    for (Bomba* b = jogo->bombas->head; b; b = b->next) countB++;
    fwrite(&countB, sizeof(int), 1, fp);
    for (Bomba* b = jogo->bombas->head; b; b = b->next) {
        fwrite(&b->linha, sizeof(int), 1, fp);
        fwrite(&b->coluna, sizeof(int), 1, fp);
        fwrite(&b->timer, sizeof(float), 1, fp);
    }

    // 5. Salva os inimigos
    int countI = 0;
    for (Inimigo* in = jogo->inimigos->head; in; in = in->next) countI++;
    fwrite(&countI, sizeof(int), 1, fp);
    for (Inimigo* in = jogo->inimigos->head; in; in = in->next) {
        fwrite(&in->linha, sizeof(int), 1, fp);
        fwrite(&in->coluna, sizeof(int), 1, fp);
        fwrite(&in->direcao, sizeof(int), 1, fp);
        fwrite(&in->tempoTroca, sizeof(float), 1, fp);
    }

    fclose(fp);
}

// =======================================
// FUNÇÃO: carregarJogo
// Descrição: Carrega o estado salvo do jogo a partir de um arquivo binário
// =======================================
Jogo* carregarJogo(const char* filename, Texture2D texJogador, Texture2D texInimigo, Texture2D texBomba, Texture2D texExplosao) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) return NULL;

    // Aloca o struct principal do jogo
    Jogo* jogo = malloc(sizeof(Jogo));
    if (!jogo) { fclose(fp); return NULL; }

    // Aloca o jogador
    jogo->player = malloc(sizeof(Jogador));
    if (!jogo->player) {
        free(jogo);
        fclose(fp);
        return NULL;
    }

    jogo->player->sprite = texJogador;
    jogo->player->frameAtual = 0;
    jogo->player->frameTotal = 2;
    jogo->player->frameTime = 0.25f;
    jogo->player->timer = 0.0f;
    jogo->player->invulneravel = 0.0f;

    // 1. Lê a fase salva
    fread(&jogo->faseAtual, sizeof(int), 1, fp);

    // Monta o caminho para o mapa da fase
    char caminho[64];
    snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", jogo->faseAtual);

    // 2. Lê os dados do jogador
    fread(&jogo->player->linha,     sizeof(int), 1, fp);
    fread(&jogo->player->coluna,    sizeof(int), 1, fp);
    fread(&jogo->player->vidas,     sizeof(int), 1, fp);
    fread(&jogo->player->chaves,    sizeof(int), 1, fp);
    fread(&jogo->player->pontuacao, sizeof(int), 1, fp);
    fread(&jogo->player->bombas,    sizeof(int), 1, fp);
    fread(&jogo->player->direcao, sizeof(int), 1, fp);
    jogo->player->tempoMovimento = 0.0f;

    // 3. Carrega o mapa da fase e sobrescreve com os tiles salvos
    jogo->mapa = carregarMapa(caminho);
    for (int i = 0; i < LINHAS; i++)
        fread(jogo->mapa->tiles[i], sizeof(char), COLUNAS, fp);

    // 4. Carrega as bombas
    jogo->bombas = criarFilaBombas();
    int countB;
    fread(&countB, sizeof(int), 1, fp);
    for (int i = 0; i < countB; i++) {
        Bomba* b = malloc(sizeof(Bomba));
        fread(&b->linha, sizeof(int), 1, fp);
        fread(&b->coluna, sizeof(int), 1, fp);
        fread(&b->timer, sizeof(float), 1, fp);
        b->next = NULL;

        // Dentro do loop das bombas:
        b->sprite_bomba = texBomba;
        b->sprite_explosao = texExplosao;
        b->frameAtual = 0;
        b->frameTotal = 2;
        b->frameTime = 0.25f;
        b->timer_anima = 0.0f;
        b->frameExplosaoAtual = 0;
        b->frameExplosaoTotal = 6;
        b->frameExplosaoTime = 0.05f;
        b->timer_explosao_anima = 0.0f;
        b->explodindo = false;
        b->tempo_explosao = 0.0f;


        // Adiciona à fila
        if (!jogo->bombas->head)
            jogo->bombas->head = b;
        else
            jogo->bombas->tail->next = b;

        jogo->bombas->tail = b;
    }

    // 5. Carrega os inimigos
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

        in->tempoMovimento = 0.0f;
        in->next = NULL;
        in->sprite = texInimigo;
        in->frameAtual = 0;
        in->frameTotal = 2;
        in->frameTime = 0.25f;
        in->timer = 0.0f;

        // Adiciona à lista
        if (!jogo->inimigos->head)
            jogo->inimigos->head = in;
        else
            last->next = in;

        last = in;
    }

    fclose(fp);
    return jogo;
}

// =======================================
// FUNÇÃO: liberarJogo
// Descrição: Libera toda a memória alocada dinamicamente pelo jogo
// =======================================
void liberarJogo(Jogo* jogo) {
    if (!jogo) return;

    // Libera jogador
    free(jogo->player);

    // Libera tiles do mapa
    for (int i = 0; i < LINHAS; i++)
        free(jogo->mapa->tiles[i]);

    free(jogo->mapa->tiles);
    free(jogo->mapa);

    // Libera bombas
    liberarFilaBombas(jogo->bombas);

    // Libera inimigos
    liberarInimigos(jogo->inimigos);
}

void salvarPontuacao(const char* filename, int pontuacao) {
    //se nao exitir arquivo, criar um novo
    
}