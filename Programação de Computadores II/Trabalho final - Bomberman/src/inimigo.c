#include <stdlib.h>
#include "raylib.h"
#include "inimigo.h"
#include "utils.h"
#include "pontuacao.h"

/*
    ============================================
    FUNÇÃO: criarListaInimigos
    Descrição:
        Varre o mapa procurando 'E' para posicionar inimigos.
        Cada inimigo é adicionado a uma lista encadeada.
    ============================================
*/
ListaInimigos* criarListaInimigos(Mapa* mapa, Texture2D sprite) {
    ListaInimigos* lista = malloc(sizeof(ListaInimigos));
    if (!lista) return NULL;

    lista->head = NULL;
    Inimigo* last = NULL;

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa->tiles[i][j] == 'E') {
                Inimigo* inim = malloc(sizeof(Inimigo));
                if (!inim) continue;

                inim->linha = i;
                inim->coluna = j;
                inim->direcao = GetRandomValue(0, 3);
                inim->tempoTroca = 5.0f;
                inim->tempoMovimento = 0.0f;
                inim->next = NULL;

                inim->sprite = sprite;
                inim->frameAtual = 0;
                inim->frameTotal = 2;    
                inim->frameTime = 0.2f;
                inim->timer = 0.0f;

                if (!lista->head)
                    lista->head = inim;
                else
                    last->next = inim;

                last = inim;

                mapa->tiles[i][j] = ' ';
            }
        }
    }

    return lista;
}

/*
    ============================================
    FUNÇÃO: atualizarInimigos
    Descrição:
        Move inimigos no mapa, evita obstáculos, e lida com colisão com o jogador.
    ============================================
*/
void atualizarInimigos(ListaInimigos* lista, Mapa* mapa, FilaBombas* bombas, Jogador* jogador, float dt) {
    for (Inimigo* cur = lista->head; cur; cur = cur->next) {
        cur->tempoTroca -= dt;
        cur->tempoMovimento -= dt;

        // Troca de direção aleatória
        if (cur->tempoTroca <= 0) {
            cur->direcao = GetRandomValue(0, 3);
            cur->tempoTroca = 5.0f;
        }

        // Tentativa de movimento
        if (cur->tempoMovimento <= 0) {
            int nx = cur->coluna;
            int ny = cur->linha;

            switch (cur->direcao) {
                case DIR_CIMA:     ny--; break;
                case DIR_BAIXO:    ny++; break;
                case DIR_ESQUERDA: nx--; break;
                case DIR_DIREITA:  nx++; break;
            }

            bool bloqueado = false;

            // Verificações de bloqueio
            if (!entre(nx, 0, COLUNAS - 1) || !entre(ny, 0, LINHAS - 1)) {
                bloqueado = true;
            } else {
                char t = mapa->tiles[ny][nx];
                if (t == 'W' || t == 'D' || t == 'B' || t == 'K')
                    bloqueado = true;
            }

            // Colisão com bomba
            for (Bomba* b = bombas->head; b; b = b->next)
                if (b->linha == ny && b->coluna == nx)
                    bloqueado = true;

            // Outro inimigo
            if (temInimigoNaPosicao(lista, ny, nx, cur))
                bloqueado = true;

            // Colisão com jogador
            if (jogador->linha == ny && jogador->coluna == nx && jogador->invulneravel <= 0) {
                penalizarVida(jogador);
                jogador->invulneravel = 3.0f;
            }

            if (bloqueado)
                cur->direcao = GetRandomValue(0, 3);
            else {
                cur->coluna = nx;
                cur->linha = ny;
            }

            cur->tempoMovimento = TEMPO_PASSO;
        }

        // Colisão direta (sem movimento)
        if (cur->linha == jogador->linha && cur->coluna == jogador->coluna && jogador->invulneravel <= 0) {
            penalizarVida(jogador);
            jogador->invulneravel = 1.0f;
        }
    }
}

/*
    ============================================
    FUNÇÃO: desenharInimigos
    Descrição:
        Renderiza todos os inimigos da lista na tela.
    ============================================
*/
void desenharInimigos(ListaInimigos* lista) {
    for (Inimigo* cur = lista->head; cur; cur = cur->next) {
        cur->timer += GetFrameTime();
        if (cur->timer >= cur->frameTime) {
            cur->frameAtual = (cur->frameAtual + 1) % cur->frameTotal;
            cur->timer = 0.0f;
        }

        int x = cur->coluna * 20;
        int y = cur->linha * 20;

        // 👇 Considera 1 pixel de espaçamento entre os frames
        Rectangle sourceRec = {
            cur->frameAtual * 20, 
            0,
            20,
            20
        };

        Vector2 pos = { x, y };
        DrawTextureRec(cur->sprite, sourceRec, pos, WHITE);
    }
}

/*
    ============================================
    FUNÇÃO: eliminarInimigosExplodidos
    Descrição:
        Remove inimigos que estão dentro do alcance da explosão
        em cruz (linha ou coluna).
    ============================================
*/
void eliminarInimigosExplodidos(ListaInimigos* lista, int linha, int coluna, Jogador* jogador) {
    Inimigo* atual = lista->head;
    Inimigo* anterior = NULL;

    while (atual) {
        bool atingido = false;

        if (atual->linha == linha || atual->coluna == coluna) {
            int dl = atual->linha - linha;
            int dc = atual->coluna - coluna;

            if ((dl == 0 && abs(dc) <= RAIO_EXPLOSAO) ||
                (dc == 0 && abs(dl) <= RAIO_EXPLOSAO)) {
                atingido = true;
            }
        }

        if (atingido) {
            Inimigo* morto = atual;
            if (!anterior)
                lista->head = atual->next;
            else
                anterior->next = atual->next;

            atual = atual->next;
            free(morto);

            jogador->pontuacao += 20;
            TraceLog(LOG_INFO, "+20 pontos por inimigo explodido");
        } else {
            anterior = atual;
            atual = atual->next;
        }
    }
}

/*
    ============================================
    FUNÇÃO: temInimigoNaPosicao
    Descrição:
        Verifica se há um inimigo na posição (linha, coluna),
        ignorando um inimigo específico.
    ============================================
*/
bool temInimigoNaPosicao(ListaInimigos* lista, int linha, int coluna, Inimigo* ignorar) {
    for (Inimigo* atual = lista->head; atual; atual = atual->next) {
        if (atual == ignorar) continue;
        if (atual->linha == linha && atual->coluna == coluna)
            return true;
    }
    return false;
}

/*
    ============================================
    FUNÇÃO: liberarInimigos
    Descrição:
        Libera toda a memória da lista de inimigos.
    ============================================
*/
void liberarInimigos(ListaInimigos* lista) {
    Inimigo* cur = lista->head;
    while (cur) {
        Inimigo* prox = cur->next; 
        free(cur);
        cur = prox;
    }
    free(lista);
}
