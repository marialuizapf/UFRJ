#include <stdlib.h>
#include "raylib.h"
#include "bomba.h"
#include "jogador.h"
#include "pontuacao.h"
#include "inimigo.h"

FilaBombas* criarFilaBombas(void) {
    FilaBombas* f = malloc(sizeof(FilaBombas));
    f->head = f->tail = NULL;
    return f;
}

void liberarFilaBombas(FilaBombas* f) {
    Bomba* cur = f->head;
    while (cur) {
        Bomba* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(f);
}

void plantarBomba(FilaBombas* f, Jogador* j, Mapa* mapa) {
    if (j->bombas <= 0) return;

    // Posição à frente do jogador
    int li = j->linha;
    int co = j->coluna;

    switch (j->direcao) {
        case DIR_CIMA:     li--; break;
        case DIR_BAIXO:    li++; break;
        case DIR_ESQUERDA: co--; break;
        case DIR_DIREITA:  co++; break;
        default: break;
    }

    // Verificar limites
    if (li < 0 || li >= LINHAS || co < 0 || co >= COLUNAS) return;

    // Verificar se o tile está livre no mapa
    char cel = mapa->tiles[li][co];
    if (cel != ' ') return;

    // Verificar se já existe bomba na posição
    for (Bomba* b = f->head; b; b = b->next) {
        if (b->linha == li && b->coluna == co) return;
    }

    // Criar nova bomba
    Bomba* nova = malloc(sizeof(Bomba));
    nova->linha = li;
    nova->coluna = co;
    nova->timer = TEMPO_EXPLOSAO;
    nova->explodindo = false;
    nova->tempo_explosao = 0.0f;
    nova->next = NULL;

    // Inserir na fila
    if (!f->head) f->head = f->tail = nova;
    else {
        f->tail->next = nova;
        f->tail = nova;
    }
    
    j->bombas--;
}

void retirarBomba(FilaBombas* f, Jogador* j, Mapa* m) {
    if (!f->head) return;              // fila vazia

    // 1) calcula posição à frente do jogador
    int li = j->linha;
    int co = j->coluna;
    switch (j->direcao) {
        case DIR_CIMA:     li--; break;
        case DIR_BAIXO:    li++; break;
        case DIR_ESQUERDA: co--; break;
        case DIR_DIREITA:  co++; break;
        default: break;
    }
    // 2) limites
    if (li < 0 || li >= LINHAS || co < 0 || co >= COLUNAS) return;

    // 3) verifica se a cabeça da fila está nessa posição e ainda não explodiu
    Bomba* b = f->head;
    if (b->linha != li || b->coluna != co || b->explodindo) return;

    // 4) remove a cabeça (dequeue)
    f->head = b->next;
    if (!f->head) f->tail = NULL;

    // 5) devolve bomba ao jogador
    j->bombas++;
    free(b);
}

void atualizarBombas(FilaBombas* f, Jogador* j, Mapa* m, ListaInimigos* inimigos, float dt) {
    Bomba *ant = NULL, *cur = f->head;

    while (cur) {
        if (!cur->explodindo) {
            cur->timer -= dt;
        } else {
            cur->tempo_explosao -= dt;
        }

        // Explodir
        if (!cur->explodindo && cur->timer <= 0) {
            int li = cur->linha, co = cur->coluna;

            //  Centro da explosão
            char* centro = &m->tiles[li][co];
            char original = *centro;
            if (original == 'D' || original == 'B' || original == 'K') {
                if (original == 'K') {
                    *centro = 'C';  // 1) Caixa com chave vira 'C'
                } else {
                    *centro = ' ';
                    pontuarCaixa(j);
                }
            }

            // ↑ Cima
            for (int d = 1; d <= RAIO_EXPLOSAO; d++) {
                int y = li - d;
                if (y < 0) break;
                char* cel = &m->tiles[y][co];
                original = *cel;
                if (original == 'W') break;
                if (original == 'D' || original == 'B' || original == 'K') {
                    if (original == 'K') {
                        *cel = 'C';
                    } else {
                        *cel = ' ';
                        pontuarCaixa(j);
                    }
                    break;
                }
            }

            // ↓ Baixo
            for (int d = 1; d <= RAIO_EXPLOSAO; d++) {
                int y = li + d;
                if (y >= LINHAS) break;
                char* cel = &m->tiles[y][co];
                original = *cel;
                if (original == 'W') break;
                if (original == 'D' || original == 'B' || original == 'K') {
                    if (original == 'K') {
                        *cel = 'C';
                    } else {
                        *cel = ' ';
                        pontuarCaixa(j);
                    }
                    break;
                }
            }

            // ← Esquerda
            for (int d = 1; d <= RAIO_EXPLOSAO; d++) {
                int x = co - d;
                if (x < 0) break;
                char* cel = &m->tiles[li][x];
                original = *cel;
                if (original == 'W') break;
                if (original == 'D' || original == 'B' || original == 'K') {
                    if (original == 'K') {
                        *cel = 'C';
                    } else {
                        *cel = ' ';
                        pontuarCaixa(j);
                    }
                    break;
                }
            }

            // → Direita
            for (int d = 1; d <= RAIO_EXPLOSAO; d++) {
                int x = co + d;
                if (x >= COLUNAS) break;
                char* cel = &m->tiles[li][x];
                original = *cel;
                if (original == 'W') break;
                if (original == 'D' || original == 'B' || original == 'K') {
                    if (original == 'K') {
                        *cel = 'C';
                    } else {
                        *cel = ' ';
                        pontuarCaixa(j);
                    }
                    break;
                }
            }

            // Penalizar jogador se ele estiver na explosão
            for (int d = -RAIO_EXPLOSAO; d <= RAIO_EXPLOSAO; d++) {
                if ((j->linha == li + d && j->coluna == co) ||
                    (j->linha == li && j->coluna == co + d)) {
            
                    if (j->invulneravel <= 0) {
                        penalizarVida(j);
                        j->invulneravel = 3.0f;  // fica invencível por 3 segundos
                    }
                }
            }
            


            // ☠️ Elimina inimigos atingidos
            eliminarInimigosExplodidos(inimigos, li, co, j);


            // Marca explosão ativa (por 0.3s)
            cur->explodindo = true;
            cur->tempo_explosao = 0.3f;
        }

        // Se terminou de exibir a explosão, remove
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

void desenharBombas(FilaBombas* f) {
    for (Bomba* b = f->head; b; b = b->next) {
        int x = b->coluna * 20;
        int y = b->linha * 20;

        if (b->explodindo) {
            DrawRectangle(x, y, 20, 20, ORANGE);
            for (int i = 1; i <= RAIO_EXPLOSAO; i++) {
                if (b->linha - i >= 0)     DrawRectangle(x, (b->linha - i) * 20, 20, 20, RED);
                if (b->linha + i < LINHAS) DrawRectangle(x, (b->linha + i) * 20, 20, 20, RED);
                if (b->coluna - i >= 0)    DrawRectangle((b->coluna - i) * 20, y, 20, 20, RED);
                if (b->coluna + i < COLUNAS) DrawRectangle((b->coluna + i) * 20, y, 20, 20, RED);
            }
        } else {
            DrawCircle(x + 10, y + 10, 10, BLACK);
            DrawText("B", x + 5, y + 2, 14, WHITE);
        }
    }
}




