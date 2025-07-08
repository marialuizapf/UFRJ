#include <stdlib.h>
#include "raylib.h"
#include "bomba.h"
#include "jogador.h"
#include "pontuacao.h"
#include "inimigo.h"

/*
    ============================================
    FUNÇÃO: criarFilaBombas
    Descrição:
        Inicializa uma nova fila de bombas.
    ============================================
*/
FilaBombas* criarFilaBombas(void) {
    FilaBombas* f = malloc(sizeof(FilaBombas));
    if (!f) return NULL;
    f->head = f->tail = NULL;
    return f;
}

/*
    ============================================
    FUNÇÃO: liberarFilaBombas
    Descrição:
        Libera toda a memória alocada para bombas.
    ============================================
*/
void liberarFilaBombas(FilaBombas* f) {
    Bomba* cur = f->head;
    while (cur) {
        Bomba* nxt = cur->next;
        UnloadTexture(cur->sprite_bomba);
        UnloadTexture(cur->sprite_explosao);
        free(cur);
        cur = nxt;
    }
    free(f);
}

/*
    ============================================
    FUNÇÃO: plantarBomba
    Descrição:
        Planta uma bomba à frente do jogador, se possível.
    ============================================
*/
void plantarBomba(FilaBombas* f, Jogador* j, Mapa* mapa) {
    if (j->bombas <= 0) return;

    int li = j->linha;
    int co = j->coluna;

    // Determina a posição à frente do jogador
    switch (j->direcao) {
        case DIR_CIMA:     li--; break;
        case DIR_BAIXO:    li++; break;
        case DIR_ESQUERDA: co--; break;
        case DIR_DIREITA:  co++; break;
        default: break;
    }

    // Verifica se a posição é válida e está livre
    if (li < 0 || li >= LINHAS || co < 0 || co >= COLUNAS) return;
    if (mapa->tiles[li][co] != ' ') return;

    // Verifica se já existe bomba na posição
    for (Bomba* b = f->head; b; b = b->next)
        if (b->linha == li && b->coluna == co)
            return;

    // Cria e insere nova bomba
    Bomba* nova = malloc(sizeof(Bomba));
    nova->linha = li;
    nova->coluna = co;
    nova->timer = TEMPO_EXPLOSAO;
    nova->explodindo = false;
    nova->tempo_explosao = 0.0f;
    nova->next = NULL;

    nova->sprite_bomba = LoadTexture("assets/bomb_40x20.png");
    nova->sprite_explosao = LoadTexture("assets/explosion_120x20.png");
    nova->frameAtual = 0;
    nova->frameTotal = 2;
    nova->frameTime = 0.25f;
    nova->timer_anima = 0.0f;

    nova->frameExplosaoAtual = 0;
    nova->frameExplosaoTotal = 6;
    nova->frameExplosaoTime = 0.05f;  // tempo por frame de explosão
    nova->timer_explosao_anima = 0.0f;


    if (!f->head) f->head = f->tail = nova;
    else {
        f->tail->next = nova;
        f->tail = nova;
    }

    j->bombas--;
}

/*
    ============================================
    FUNÇÃO: retirarBomba
    Descrição:
        Permite remover uma bomba ainda ativa à frente do jogador.
    ============================================
*/
void retirarBomba(FilaBombas* f, Jogador* j, Mapa* m) {
    if (!f->head) return;

    int li = j->linha;
    int co = j->coluna;

    switch (j->direcao) {
        case DIR_CIMA:     li--; break;
        case DIR_BAIXO:    li++; break;
        case DIR_ESQUERDA: co--; break;
        case DIR_DIREITA:  co++; break;
        default: break;
    }

    if (li < 0 || li >= LINHAS || co < 0 || co >= COLUNAS) return;

    Bomba* b = f->head;
    if (b->linha != li || b->coluna != co || b->explodindo) return;

    f->head = b->next;
    if (!f->head) f->tail = NULL;

    j->bombas++;
    free(b);
}

/*
    ============================================
    FUNÇÃO: atualizarBombas
    Descrição:
        Atualiza o estado das bombas: contagem, explosão, dano, remoção.
    ============================================
*/
void atualizarBombas(FilaBombas* f, Jogador* j, Mapa* m, ListaInimigos* inimigos, float dt) {
    Bomba *ant = NULL, *cur = f->head;

    while (cur) {
        if (!cur->explodindo) cur->timer -= dt;
        else cur->tempo_explosao -= dt;

        if (!cur->explodindo && cur->timer <= 0) {
            int li = cur->linha;
            int co = cur->coluna;

            // Trata explosão central
            char* centro = &m->tiles[li][co];
            char original = *centro;
            if (original == 'K') {*centro = 'C';  pontuarCaixa(j);}
            else if (original == 'D' || original == 'B') {
                *centro = ' ';
                pontuarCaixa(j);
            }

            // Direções da explosão
            int dx[] = { 0,  0, -1, 1};
            int dy[] = {-1,  1,  0, 0};
            for (int dir = 0; dir < 4; dir++) {
                for (int d = 1; d <= RAIO_EXPLOSAO; d++) {
                    int x = co + dx[dir] * d;
                    int y = li + dy[dir] * d;

                    if (x < 0 || x >= COLUNAS || y < 0 || y >= LINHAS) break;

                    char* cel = &m->tiles[y][x];
                    original = *cel;

                    if (original == 'W') break;
                    if (original == 'K') { *cel = 'C';  pontuarCaixa(j); break; }
                    if (original == 'D' || original == 'B') {
                        *cel = ' ';
                        pontuarCaixa(j);
                        break;
                    }
                }
            }

            // Afeta jogador se estiver na cruz da explosão
            for (int d = -RAIO_EXPLOSAO; d <= RAIO_EXPLOSAO; d++) {
                if ((j->linha == li + d && j->coluna == co) ||
                    (j->linha == li && j->coluna == co + d)) {
                    if (j->invulneravel <= 0) {
                        penalizarVida(j);
                        j->invulneravel = 3.0f;
                    }
                }
            }

            // Elimina inimigos atingidos
            eliminarInimigosExplodidos(inimigos, li, co, j);

            // Marca como explodindo
            cur->explodindo = true;
            cur->tempo_explosao = 0.3f;
        }

        // Remove bomba após exibir explosão
        if (cur->explodindo && cur->tempo_explosao <= 0) {
            j->bombas++;
            if (!ant) f->head = cur->next;
            else ant->next = cur->next;
            if (cur == f->tail) f->tail = ant;

            Bomba* temp = cur;
            cur = cur->next;
            free(temp);
            continue;
        }

        ant = cur;
        cur = cur->next;
    }
}

/*
    ============================================
    FUNÇÃO: desenharBombas
    Descrição:
        Desenha bombas ativas e explosões na tela.
    ============================================
*/
void desenharBombas(FilaBombas* f) {
    for (Bomba* b = f->head; b; b = b->next) {
        int x = b->coluna * 20;
        int y = b->linha * 20;

        if (b->explodindo) {
            // Atualiza frame da explosão animada
            b->timer_explosao_anima += GetFrameTime();
            if (b->timer_explosao_anima >= b->frameExplosaoTime) {
                b->frameExplosaoAtual = (b->frameExplosaoAtual + 1) % b->frameExplosaoTotal;
                b->timer_explosao_anima = 0.0f;
            }

            Rectangle sourceRec = {
                b->frameExplosaoAtual  * 20,
                0,
                20,
                20
            };

            // Centro da explosão
            Vector2 pos = { x, y };
            DrawTextureRec(b->sprite_explosao, sourceRec, pos, WHITE);

            // Cruz da explosão animada
            for (int i = 1; i <= RAIO_EXPLOSAO; i++) {
                // Cima
                if (b->linha - i >= 0) {
                    Vector2 p = { x, (b->linha - i) * 20 };
                    DrawTextureRec(b->sprite_explosao, sourceRec, p, WHITE);
                }
                // Baixo
                if (b->linha + i < LINHAS) {
                    Vector2 p = { x, (b->linha + i) * 20 };
                    DrawTextureRec(b->sprite_explosao, sourceRec, p, WHITE);
                }
                // Esquerda
                if (b->coluna - i >= 0) {
                    Vector2 p = { (b->coluna - i) * 20, y };
                    DrawTextureRec(b->sprite_explosao, sourceRec, p, WHITE);
                }
                // Direita
                if (b->coluna + i < COLUNAS) {
                    Vector2 p = { (b->coluna + i) * 20, y };
                    DrawTextureRec(b->sprite_explosao, sourceRec, p, WHITE);
                }
            }

        } else {
            // Animação da bomba antes da explosão
            b->timer_anima += GetFrameTime();
            if (b->timer_anima >= b->frameTime) {
                b->frameAtual = (b->frameAtual + 1) % b->frameTotal;
                b->timer_anima = 0.0f;
            }

            Rectangle sourceRec = {
                b->frameAtual * 20,
                0,
                20,
                20
            };

            Vector2 pos = { x, y };
            DrawTextureRec(b->sprite_bomba, sourceRec, pos, WHITE);
        }
    }
}

