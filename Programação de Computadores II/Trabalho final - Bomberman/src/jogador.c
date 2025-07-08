#include <stdlib.h>
#include "raylib.h"
#include "jogador.h"
#include "bomba.h"

/*
    ============================================
    FUNÇÃO: desenharJogador
    Descrição:
        Desenha o jogador na tela com efeito visual de "piscada"
        caso esteja invulnerável.
    ============================================
*/
void desenharJogador(Jogador* jogador) {
    int x = jogador->coluna * 20;
    int y = jogador->linha * 20;

    jogador->timer += GetFrameTime();
    if (jogador->timer >= jogador->frameTime) {
        jogador->frameAtual = (jogador->frameAtual + 1) % jogador->frameTotal;
        jogador->timer = 0.0f;
    }

    Rectangle sourceRec = { jogador->frameAtual * 20, 0,20,20};

    Vector2 position = { x, y };

    Color cor = WHITE;
    if (jogador->invulneravel > 0 && ((int)(GetTime() * 10) % 2 == 0)) {
        cor = RED;
    }

    DrawTextureRec(jogador->sprite, sourceRec, position, cor);
}

/*
    ============================================
    FUNÇÃO: podeMover (estática)
    Descrição:
        Verifica se o jogador pode se mover para a posição (l, c).
        Considera colisão com obstáculos e bombas.
    ============================================
*/
static bool podeMover(Jogador* jogador, Mapa* mapa, FilaBombas* fila, int l, int c) {
    // Fora dos limites do mapa
    if (l < 0 || l >= LINHAS || c < 0 || c >= COLUNAS)
        return false;

    char t = mapa->tiles[l][c];

    // Obstáculos que bloqueiam movimento
    if (t == 'W' || t == 'D' || t == 'B' || t == 'K')
        return false;

    // Verifica colisão com bombas
    for (Bomba* b = fila->head; b; b = b->next) {
        if (b->linha == l && b->coluna == c) {
            // Pode passar se já estiver sobre a bomba
            if (jogador->linha == l && jogador->coluna == c)
                return true;
            return false;
        }
    }

    return true;
}

/*
    ============================================
    FUNÇÃO: criarJogador
    Descrição:
        Inicializa a estrutura do jogador e define sua posição
        com base no caractere 'J' no mapa.
    ============================================
*/
Jogador* criarJogador(Mapa* mapa, Texture2D sprite) {
    Jogador* player = malloc(sizeof(Jogador));
    if (!player) return NULL;

    // Atributos padrão do jogador
    player->vidas = 3;
    player->pontuacao = 0;
    player->bombas = 3;
    player->chaves = 0;
    player->direcao = DIR_BAIXO;
    player->tempoMovimento = 0.0f;

    // Inicializa animação do jogador
    player->sprite = sprite;
    player->frameAtual = 0;
    player->frameTotal = 4;
    player->frameTime = 0.15f; // velocidade da animação
    player->timer = 0.0f;

    // Procura a posição inicial do jogador no mapa
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa->tiles[i][j] == 'J') {
                player->linha = i;
                player->coluna = j;
                mapa->tiles[i][j] = ' '; // Limpa o mapa
                return player;
            }
        }
    }

    // Caso não encontre 'J', define posição padrão
    player->linha = 0;
    player->coluna = 0;
    return player;
}

/*
    ============================================
    FUNÇÃO: atualizarJogador
    Descrição:
        Atualiza a posição do jogador com base nas teclas pressionadas
        e interage com os elementos do mapa (coleta de chaves).
    ============================================
*/
void atualizarJogador(Jogador* jogador, Mapa* mapa, FilaBombas* fila, float dt) {
    jogador->tempoMovimento -= dt;
    if (jogador->tempoMovimento > 0)
        return;

    // Posição alvo
    int nx = jogador->coluna;
    int ny = jogador->linha;

    // Direção de movimento baseada nas teclas pressionadas
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        nx++;
        jogador->direcao = DIR_DIREITA;
    } else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        nx--;
        jogador->direcao = DIR_ESQUERDA;
    } else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        ny--;
        jogador->direcao = DIR_CIMA;
    } else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        ny++;
        jogador->direcao = DIR_BAIXO;
    }

    // Se houve tentativa de movimentação e ela é válida
    if ((nx != jogador->coluna || ny != jogador->linha)
        && podeMover(jogador, mapa, fila, ny, nx)) {
        
        jogador->coluna = nx;
        jogador->linha = ny;
        jogador->tempoMovimento = TEMPO_PASSO;

        // Coleta chave
        if (mapa->tiles[ny][nx] == 'C') {
            jogador->chaves++;
            mapa->tiles[ny][nx] = ' ';
        }
    }
}
