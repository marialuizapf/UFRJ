#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"

// Inclusão dos módulos do jogo
#include "mapa.h"
#include "jogador.h"
#include "bomba.h"
#include "inimigo.h"
#include "pontuacao.h"
#include "save.h"
#include "menu.h"

int main(void) {
    // Configurações da janela
    const int largura = 1200;
    const int altura  = 600;
    InitWindow(largura, altura, "Bomberman - Versão Final");
    SetTargetFPS(60); // Limita a 60 FPS

    // Carregamento de texturas
    Texture2D chave = LoadTexture("assets/key.png");
    Texture2D caixa = LoadTexture("assets/box_20x20.png");
    Texture2D paredeInv = LoadTexture("assets/wall_inv.png");
    Texture2D paredeFraca = LoadTexture("assets/wall_weak.png");
    Texture2D texJogador = LoadTexture("assets/player-80x20.png");
    Texture2D texInimigo = LoadTexture("assets/inimigo_41x20.png");
    Texture2D texBomba = LoadTexture("assets/bomb_40x20.png");
    Texture2D texExplosao = LoadTexture("assets/explosion_120x20.png");

    // Variáveis do jogo
    int faseAtual = 1;
    char caminho[64];
    snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", faseAtual);

    // Inicialização de estruturas do jogo
    Mapa* mapa = carregarMapa(caminho);
    Jogador* player = criarJogador(mapa, texJogador);
    FilaBombas* fila = criarFilaBombas();
    ListaInimigos* inimigos = criarListaInimigos(mapa, texInimigo);
    MenuState estado = MENU_JOGO;

    bool gameVenceu = false;
    bool faseConcluida = false;
    bool checouProximo = false;

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        float dt = GetFrameTime(); // Tempo entre frames

        // Diminui o tempo de invulnerabilidade se estiver ativo
        if (player->invulneravel > 0)
            player->invulneravel -= dt;

        // ====================== Lógica do jogo ======================
        if (estado == MENU_JOGO && !faseConcluida && !gameVenceu) {
            atualizarJogador(player, mapa, fila, dt);

            if (IsKeyPressed(KEY_B))
                plantarBomba(fila, player, mapa, texBomba, texExplosao);
            if (IsKeyPressed(KEY_R))
                retirarBomba(fila, player, mapa);

            atualizarBombas(fila, player, mapa, inimigos, dt);
            atualizarInimigos(inimigos, mapa, fila, player, dt);

            // Verifica se jogador pode passar de fase
            if (player->chaves >= 1 && !checouProximo) {
                char proximo[64];
                snprintf(proximo, sizeof(proximo), "mapas/mapa%d.txt", faseAtual + 1);
                FILE* fp = fopen(proximo, "r");

                bool temProximo = (fp != NULL);
                if (fp) fclose(fp);

                faseConcluida = temProximo;
                gameVenceu = !temProximo;
                checouProximo = true;
            }
        }

        // ====================== Estados do menu ======================
        if (estado == NOVO_JOGO) {
            // Libera dados do jogo anterior
            liberarJogo(&(Jogo){
                .player = player, .mapa = mapa, .bombas = fila,
                .inimigos = inimigos, .faseAtual = faseAtual
            });

            // Recomeça jogo do início
            faseAtual = 1;
            snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", faseAtual);
            mapa = carregarMapa(caminho);
            player = criarJogador(mapa, texJogador);
            player->invulneravel = 0.0f; 
            fila = criarFilaBombas();
            inimigos = criarListaInimigos(mapa, texInimigo);
            player->chaves = 0;


            faseConcluida = false;
            checouProximo = false;
            gameVenceu = false;
            estado = MENU_JOGO;
        }

        if (estado == SALVAR_JOGO) {
            salvarJogo("save.dat", &(Jogo){
                .player = player, .mapa = mapa, .bombas = fila,
                .inimigos = inimigos, .faseAtual = faseAtual
            });

            DrawText("Jogo salvo com sucesso!", 400, 550, 20, GREEN);
            estado = MENU_JOGO;
        }

        if (estado == CARREGAR_JOGO) {
            liberarJogo(&(Jogo){
                .player = player, .mapa = mapa, .bombas = fila,
                .inimigos = inimigos, .faseAtual = faseAtual
            });

            Jogo* jogo = carregarJogo("save.dat", texJogador, texInimigo, texBomba, texExplosao);
            if (jogo) {
                player = jogo->player;
                mapa = jogo->mapa;
                fila = jogo->bombas;
                inimigos = jogo->inimigos;
                faseAtual = jogo->faseAtual;
                player->invulneravel = 0.0f;
                free(jogo);
            }

            DrawText("Jogo carregado com sucesso!", 400, 550, 20, GREEN);
            estado = MENU_JOGO;
        }

        // Avança de fase após ENTER
        if (faseConcluida && IsKeyPressed(KEY_ENTER)) {
            int vidas_salvas = player->vidas;
            int pontuacao_salva = player->pontuacao;

            liberarJogo(&(Jogo){
                .player = player, .mapa = mapa, .bombas = fila,
                .inimigos = inimigos, .faseAtual = faseAtual
            });

            faseAtual++;
            snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", faseAtual);

            mapa = carregarMapa(caminho);
            player = criarJogador(mapa, texJogador);
            fila = criarFilaBombas();
            inimigos = criarListaInimigos(mapa, texInimigo);

            // Mantém dados do jogador
            player->vidas = vidas_salvas;
            player->pontuacao = pontuacao_salva;
            player->invulneravel = 0.0f;

            faseConcluida = false;
            checouProximo = false;
        }

        // Game over
        if (player->vidas <= 0) {
            if (IsKeyPressed(KEY_ENTER)) {
                estado = NOVO_JOGO;
            } else if (IsKeyPressed(KEY_Q)) {
                CloseWindow();
                return 0;
            }
        }

        // Venceu o jogo
        if (gameVenceu) {
            if (IsKeyPressed(KEY_ENTER)) {
                estado = NOVO_JOGO;
                gameVenceu = false;
                checouProximo = false;
            } else if (IsKeyPressed(KEY_Q)) {
                CloseWindow();
                return 0;
            }
        }

        // Atualiza menu
        estado = atualizarMenu(&estado);

        // ====================== Renderização ======================
        BeginDrawing();

        if (player->vidas <= 0) {
            ClearBackground(RED);
            DrawText("Game Over!", largura/2 - MeasureText("Game Over!", 40)/2, altura/2 - 40, 40, WHITE);
            DrawText("Pressione ENTER para reiniciar", largura/2 - MeasureText("Pressione ENTER para reiniciar", 20)/2, altura/2 + 20, 20, WHITE);
            DrawText("Pressione Q para sair", largura/2 - MeasureText("Pressione Q para sair", 20)/2, altura/2 + 40, 20, WHITE);

        } else if (faseConcluida) {
            ClearBackground(BLACK);
            DrawText("Parabéns!", largura/2 - MeasureText("Parabéns!", 40)/2, altura/2 - 40, 40, WHITE);
            DrawText("Você coletou 5 chaves e passou de fase!", largura/2 - MeasureText("Você coletou 5 chaves e passou de fase!", 20)/2, altura/2 + 20, 20, WHITE);
            DrawText("Pressione ENTER para voltar ao jogo", largura/2 - MeasureText("Pressione ENTER para voltar ao jogo", 20)/2, altura/2 + 40, 20, WHITE);

        } else if (gameVenceu) {
            ClearBackground(GREEN);
            DrawText("Você venceu!", largura/2 - MeasureText("Você venceu!", 40)/2, altura/2 - 40, 40, WHITE);
            DrawText("Pressione ENTER para reiniciar", largura/2 - MeasureText("Pressione ENTER para reiniciar", 20)/2, altura/2 + 20, 20, WHITE);
            DrawText("Pressione Q para sair", largura/2 - MeasureText("Pressione Q para sair", 20)/2, altura/2 + 40, 20, WHITE);

        } else {
            ClearBackground(DARKGREEN);

            // Desenha elementos do jogo
            desenharMapa(mapa, chave, caixa, paredeInv, paredeFraca);
            desenharBombas(fila);
            desenharInimigos(inimigos);
            desenharJogador(player);
            desenharMenu(estado);

            // HUD do jogador
            DrawRectangle(0, 500, 1200, 100, LIME);
            DrawText(TextFormat("Bombas: %d", player->bombas), 20, 520, 20, BLACK);
            DrawText(TextFormat("Vidas: %d", player->vidas), 300, 520, 20, BLACK);
            DrawText(TextFormat("Pontuacao: %d", player->pontuacao), 600, 520, 20, BLACK);
        }

        EndDrawing();
    }

    // Finaliza e libera os recursos do jogo
    Jogo jogo = {
        .player = player,
        .mapa = mapa,
        .bombas = fila,
        .inimigos = inimigos,
        .faseAtual = faseAtual
    };

    UnloadTexture(chave);
    UnloadTexture(caixa);
    UnloadTexture(paredeInv);
    UnloadTexture(paredeFraca);


    liberarJogo(&jogo);
    CloseWindow();
    return 0;
}
