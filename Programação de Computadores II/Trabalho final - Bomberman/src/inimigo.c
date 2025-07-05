#include <stdlib.h>
#include "raylib.h"
#include "inimigo.h"
#include "utils.h"
#include "pontuacao.h"

// Cria a lista de inimigos com base no mapa
ListaInimigos* criarListaInimigos(Mapa* mapa) {
    ListaInimigos* lista = malloc(sizeof(ListaInimigos));
    lista->head = NULL;

    Inimigo* last = NULL;

    // Percorre cada célula do mapa
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            // Se encontrar um inimigo ('E')
            if (mapa->tiles[i][j] == 'E') {
                // Aloca e inicializa um novo inimigo
                Inimigo* inim = malloc(sizeof(Inimigo));
                inim->linha = i;
                inim->coluna = j;
                inim->direcao = GetRandomValue(0, 3); // Direção aleatória
                inim->tempoTroca = 5.0f;              // Tempo até trocar direção
                inim->tempoMovimento = 0.0f;          // Pode se mover imediatamente
                inim->next = NULL;

                // Adiciona o inimigo à lista encadeada
                if (!lista->head)
                    lista->head = inim;
                else
                    last->next = inim;
                last = inim;

                // Remove o caractere 'E' do mapa para não redesenhar
                mapa->tiles[i][j] = ' ';
            }
        }
    }

    return lista;
}

// Atualiza posição e direção dos inimigos
void atualizarInimigos(ListaInimigos* lista, Mapa* mapa, FilaBombas* bombas, Jogador* jogador, float dt) {
    for (Inimigo* cur = lista->head; cur; cur = cur->next) {
        cur->tempoTroca -= dt;
        cur->tempoMovimento -= dt;

        if (cur->tempoTroca <= 0) {
            cur->direcao = GetRandomValue(0, 3);
            cur->tempoTroca = 5.0f;
        }

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

            // Parede ou obstáculo no mapa
            if (!entre(nx, 0, COLUNAS - 1) || !entre(ny, 0, LINHAS - 1))
                bloqueado = true;
            else {
                char t = mapa->tiles[ny][nx];
                if (t == 'W' || t == 'D' || t == 'B' || t == 'K')
                    bloqueado = true;
            }

            // Tem bomba?
            for (Bomba* b = bombas->head; b; b = b->next)
                if (b->linha == ny && b->coluna == nx)
                    bloqueado = true;

            // Tem outro inimigo?
            if (temInimigoNaPosicao(lista, ny, nx, cur))
                bloqueado = true;

            // Tem jogador?
            if (jogador->linha == ny && jogador->coluna == nx) {
                if (jogador->invulneravel <= 0) {
                    penalizarVida(jogador);
                    jogador->invulneravel = 3.0f;
                }
                // NÃO bloqueia o inimigo aqui!
            }
            

            if (bloqueado)
                cur->direcao = GetRandomValue(0, 3);
            else {
                cur->coluna = nx;
                cur->linha = ny;
            }

            cur->tempoMovimento = TEMPO_PASSO;
        }

        // Verifica colisão mesmo sem movimento
        if (cur->linha == jogador->linha && cur->coluna == jogador->coluna) {
            if (jogador->invulneravel <= 0) {
                penalizarVida(jogador);
                jogador->invulneravel = 1.0f;
            }
        }
    }
}



// Desenha todos os inimigos na tela
void desenharInimigos(ListaInimigos* lista) {
    for (Inimigo* cur = lista->head; cur; cur = cur->next) {
        DrawRectangle(cur->coluna * 20, cur->linha * 20, 20, 20, RED); // Cada inimigo é um quadrado vermelho
    }
}
void eliminarInimigosExplodidos(ListaInimigos* lista, int linha, int coluna, Jogador* jogador){
    Inimigo* atual = lista->head;
    Inimigo* anterior = NULL;

    while (atual) {
        bool atingido = false;

        // Mesmo linha e coluna (cruz da explosão)
        if (atual->linha == linha || atual->coluna == coluna) {
            int dl = atual->linha - linha;
            int dc = atual->coluna - coluna;

            // Dentro do alcance da explosão?
            if ((dl == 0 && abs(dc) <= RAIO_EXPLOSAO) ||
                (dc == 0 && abs(dl) <= RAIO_EXPLOSAO)) {
                atingido = true;
            }
        }

        if (atingido) {
            Inimigo* morto = atual;
            if (!anterior) lista->head = atual->next;
            else anterior->next = atual->next;
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
bool temInimigoNaPosicao(ListaInimigos* lista, int linha, int coluna, Inimigo* ignorar) {
    for (Inimigo* atual = lista->head; atual; atual = atual->next) {
        if (atual == ignorar) continue;
        if (atual->linha == linha && atual->coluna == coluna) return true;
    }
    return false;
}

// Libera a memória da lista de inimigos
void liberarInimigos(ListaInimigos* lista) {
    Inimigo* cur = lista->head;
    while (cur) {
        Inimigo* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    free(lista);
}
