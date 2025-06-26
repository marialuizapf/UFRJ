#include <stdlib.h>
#include "raylib.h"
#include "inimigo.h"
#include "utils.h"

#define TEMPO_PASSO 0.1f  // Intervalo entre movimentos (em segundos)



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
void atualizarInimigos(ListaInimigos* lista, Mapa* mapa, float dt) {
    for (Inimigo* cur = lista->head; cur; cur = cur->next) {
        // Reduz o tempo até a próxima troca de direção
        cur->tempoTroca -= dt;
        // Reduz o tempo até o próximo movimento
        cur->tempoMovimento -= dt;

        // Troca direção aleatoriamente após tempo expirar
        if (cur->tempoTroca <= 0) {
            cur->direcao = GetRandomValue(0, 3);
            cur->tempoTroca = 5.0f;
        }

        // Move o inimigo se o tempo de passo expirou
        if (cur->tempoMovimento <= 0) {
            int nx = cur->coluna;
            int ny = cur->linha;

            // Calcula a próxima posição com base na direção atual
            switch (cur->direcao) {
                case DIR_CIMA:     ny--; break;
                case DIR_BAIXO:    ny++; break;
                case DIR_ESQUERDA: nx--; break;
                case DIR_DIREITA:  nx++; break;
            }

            // Verifica se o próximo passo é válido (dentro do mapa e espaço livre)
            if (entre(nx, 0, COLUNAS - 1) && entre(ny, 0, LINHAS - 1) && mapa->tiles[ny][nx] == ' ') {
                cur->coluna = nx;
                cur->linha = ny;
            } else {
                // Se não pode andar, escolhe nova direção
                cur->direcao = GetRandomValue(0, 3);
            }

            // Reinicia o tempo até o próximo passo
            cur->tempoMovimento = TEMPO_PASSO;
        }
    }
}


// Desenha todos os inimigos na tela
void desenharInimigos(ListaInimigos* lista) {
    for (Inimigo* cur = lista->head; cur; cur = cur->next) {
        DrawRectangle(cur->coluna * 20, cur->linha * 20, 20, 20, RED); // Cada inimigo é um quadrado vermelho
    }
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
