#include <stdlib.h> 
#include "raylib.h"
#include "mapa.h"
#include "jogador.h"
#include "bomba.h"
#include "inimigo.h"
#include "pontuacao.h"
#include "save.h"
#include "menu.h"
#include "utils.h"

int main(void) {
    const int largura = 1200;
    const int altura  = 600;
    InitWindow(largura, altura, "Bomberman - Versão Final");
    SetTargetFPS(60);

    Texture2D chave = LoadTexture("assets/key.png");

    Mapa* mapa = carregarMapa("mapas/mapa1.txt");
    Jogador* player = criarJogador(mapa);
    FilaBombas* fila = criarFilaBombas();
    ListaInimigos* inimigos = criarListaInimigos(mapa);
    MenuState estado = MENU_JOGO;

    bool faseConcluida = false;
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        if (player->invulneravel > 0) player->invulneravel -= dt;

        if (estado == MENU_JOGO && !faseConcluida) {
            atualizarJogador(player, mapa, fila, dt);
            if (IsKeyPressed(KEY_B)) {
                plantarBomba(fila, player, mapa);
            }
            atualizarBombas(fila, player, mapa, inimigos, dt);
            atualizarInimigos(inimigos, mapa, fila, player, dt);

            if (player->chaves >= 5) {
                faseConcluida = true;
            }
        }

        if (estado == NOVO_JOGO) {
            liberarJogo(&(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos
            });

            mapa = carregarMapa("mapas/mapa1.txt");
            player = criarJogador(mapa);
            fila = criarFilaBombas();
            inimigos = criarListaInimigos(mapa);

            estado = MENU_JOGO;
        }

        if (estado == SALVAR_JOGO) {
            salvarJogo("save.dat", &(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos
            });

            DrawText("Jogo salvo com sucesso!", 400, 550, 20, GREEN);
            estado = MENU_JOGO;
        }

        if (estado == CARREGAR_JOGO) {
            liberarJogo(&(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos
            });

            Jogo* jogo = carregarJogo("save.dat");
            if (jogo) {
                player   = jogo->player;
                mapa     = jogo->mapa;
                fila     = jogo->bombas;
                inimigos = jogo->inimigos;
                free(jogo); 
            }

            DrawText("Jogo carregado com sucesso!", 400, 550, 20, GREEN);
            estado = MENU_JOGO;
        }

        if (faseConcluida && IsKeyPressed(KEY_ENTER)) {
            faseConcluida = false;
            estado = NOVO_JOGO;
        }

        estado = atualizarMenu(&estado);

        BeginDrawing();
            if (faseConcluida) {
                ClearBackground(BLACK);
                const char* msg1 = "Parabéns!";
                const char* msg2 = "Você coletou 5 chaves e passou de fase!";
                const char* msg3 = "Pressione ENTER para voltar ao jogo";
                int fw1 = MeasureText(msg1, 40);
                int fw2 = MeasureText(msg2, 20);
                int fw3 = MeasureText(msg3, 20);
                DrawText(msg1,  largura/2 - fw1/2, altura/2 - 40, 40, WHITE);
                DrawText(msg2,  largura/2 - fw2/2, altura/2 +  0, 20, WHITE);
                DrawText(msg3, largura/2 - fw3/2, altura/2 + 40, 20, WHITE);
            } else {
                ClearBackground(SKYBLUE);
                desenharMapa(mapa, chave);
                desenharBombas(fila);
                desenharInimigos(inimigos);
                desenharJogador(player);
                desenharMenu(estado);

                DrawRectangle(0, 500, 1200, 100, SKYBLUE);  
                DrawText(TextFormat("Bombas: %d", player->bombas),        20, 520, 20, BLACK);
                DrawText(TextFormat("Vidas: %d", player->vidas),         300, 520, 20, BLACK);
                DrawText(TextFormat("Pontuacao: %d", player->pontuacao), 600, 520, 20, BLACK);
            }
        EndDrawing();
    }

    Jogo jogo = {
        .player   = player,
        .mapa     = mapa,
        .bombas   = fila,
        .inimigos = inimigos
    };

    liberarJogo(&jogo);
    CloseWindow();
    return 0; 
}
