#include <stdlib.h> 
#include <stdio.h>
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
    // Configurações da janela
    const int largura = 1200;                                 // Largura da janela
    const int altura  = 600;                                  // Altura da janela
    InitWindow(largura, altura, "Bomberman - Versão Final");  // Título da janela
    SetTargetFPS(60);                                         // Taxa de quadros por segundo

    // Carrega os recursos necessários
    Texture2D chave = LoadTexture("assets/key.png");

    // Inicialização do jogo
    int faseAtual = 1;
    char caminho[64];
    snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", faseAtual);

    Mapa* mapa = carregarMapa(caminho);
    Jogador*        player   = criarJogador(mapa);
    FilaBombas*     fila     = criarFilaBombas();
    ListaInimigos*  inimigos = criarListaInimigos(mapa);
    MenuState       estado   = MENU_JOGO;

    bool gameVenceu      = false;
    bool faseConcluida   = false;
    bool checouProximo   = false;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        // Lógica de jogo
        if (estado == MENU_JOGO && !faseConcluida && !gameVenceu) {
            // Atualiza jogador e entidades somente se a fase não tiver sido concluída
            atualizarJogador(player, mapa, fila, dt);
            if (IsKeyPressed(KEY_B)) plantarBomba(fila, player, mapa);
            atualizarBombas(fila, player, mapa, inimigos, dt);
            atualizarInimigos(inimigos, mapa, dt);

            if (player->chaves >= 1 && !checouProximo) {
                char proximo[64];
                snprintf(proximo, sizeof(proximo), "mapas/mapa%d.txt", faseAtual + 1);
                FILE* fp = fopen(proximo, "r");
                bool temProximo = (fp != NULL);
                if (fp) fclose(fp);

                if (temProximo) faseConcluida = true;
                else            gameVenceu    = true;

                checouProximo = true; 
            }
        }

        if(estado == NOVO_JOGO){
            liberarJogo(&(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos,
                .faseAtual = faseAtual
            });

            faseAtual = 1;
            snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", faseAtual);
            mapa     = carregarMapa(caminho);
            player   = criarJogador(mapa);
            fila     = criarFilaBombas();
            inimigos = criarListaInimigos(mapa);
            player->chaves = 0;
            faseConcluida = false;
            checouProximo  = false; 
            gameVenceu     = false;
            estado = MENU_JOGO;
        }

        if (estado == SALVAR_JOGO) {
            salvarJogo("save.dat", &(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos,
                .faseAtual = faseAtual
            });

            DrawText("Jogo salvo com sucesso!", 400, 550, 20, GREEN);
            estado = MENU_JOGO;
        }

        if (estado == CARREGAR_JOGO) {
            liberarJogo(&(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos,
                .faseAtual = faseAtual
            });

            Jogo* jogo = carregarJogo("save.dat");
            if (jogo) {
                player   = jogo->player;
                mapa     = jogo->mapa;
                fila     = jogo->bombas;
                inimigos = jogo->inimigos;
                faseAtual = jogo->faseAtual;
                free(jogo); 
            }

            DrawText("Jogo carregado com sucesso!", 400, 550, 20, GREEN);
            estado = MENU_JOGO;
        }

        if (faseConcluida && IsKeyPressed(KEY_ENTER)) {
            int vidas_salvas      = player->vidas;
            int pontuacao_salva   = player->pontuacao;

            liberarJogo(&(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos,
                .faseAtual= faseAtual
            });

            faseAtual++;

            snprintf(caminho, sizeof(caminho), "mapas/mapa%d.txt", faseAtual);
            mapa     = carregarMapa(caminho);
            player   = criarJogador(mapa);
            fila     = criarFilaBombas();
            inimigos = criarListaInimigos(mapa);

            player->vidas = vidas_salvas;      // Mantém vidas da fase anterior
            player->pontuacao = pontuacao_salva; // Mantém pontuação da

            faseConcluida = false;
            checouProximo = false;
        }

        if(player->vidas <= 0){
            if(IsKeyPressed(KEY_ENTER)) {
                estado = NOVO_JOGO;
            } else if(IsKeyPressed(KEY_Q)) {
                CloseWindow();
                return 0; 
            }
        }

        if(gameVenceu && IsKeyPressed(KEY_ENTER)) {
            estado = NOVO_JOGO;
            gameVenceu = false;
            checouProximo = false;
        } else if(gameVenceu && IsKeyPressed(KEY_Q)) {
            CloseWindow();
            return 0; 
        }

        estado = atualizarMenu(&estado);

        // Renderização
        BeginDrawing();
            if(player->vidas <= 0) {

                ClearBackground(RED);
                const char* msg1 = "Game Over!";
                const char* msg2 = "Pressione ENTER para reiniciar";
                const char* msg3 = "Pressione Q para sair";
                int fw1 = MeasureText(msg1, 40);
                int fw2 = MeasureText(msg2, 20);
                int fw3 = MeasureText(msg3, 20);
                DrawText(msg1, largura/2 - fw1/2, altura/2 - 40, 40, WHITE);
                DrawText(msg2, largura/2 - fw2/2, altura/2 + 20, 20, WHITE);
                DrawText(msg3, largura/2 - fw3/2, altura/2 + 40, 20, WHITE);

            }else if (faseConcluida) {

                ClearBackground(BLACK);
                const char* msg1 = "Parabéns!";
                const char* msg2 = "Você coletou 5 chaves e passou de fase!";
                const char* msg3 = "Pressione ENTER para voltar ao jogo";
                int fw1 = MeasureText(msg1, 40);
                int fw2 = MeasureText(msg2, 20);
                int fw3 = MeasureText(msg3, 20);
                DrawText(msg1,  largura/2 - fw1/2, altura/2 - 40, 40, WHITE);
                DrawText(msg2,  largura/2 - fw2/2, altura/2 + 20, 20, WHITE);
                DrawText(msg3, largura/2 - fw3/2, altura/2 +  40, 20, WHITE);

            }else if (gameVenceu) {

                ClearBackground(GREEN);
                const char* msg1 = "Você venceu!";
                const char* msg2 = "Pressione ENTER para reiniciar";
                const char* msg3 = "Pressione Q para sair";
                int fw1 = MeasureText(msg1, 40);
                int fw2 = MeasureText(msg2, 20);
                int fw3 = MeasureText(msg3, 20);
                DrawText(msg1, largura/2 - fw1/2, altura/2 - 40, 40, WHITE);
                DrawText(msg2, largura/2 - fw2/2, altura/2 + 20, 20, WHITE);
                DrawText(msg3, largura/2 - fw3/2, altura/2 + 40, 20, WHITE);

            }else {
                
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

    // Libera todo o estado do jogo
    Jogo jogo = {
        .player   = player,
        .mapa     = mapa,
        .bombas   = fila,
        .inimigos = inimigos,
        .faseAtual = faseAtual
    };
    
    liberarJogo(&jogo);

    CloseWindow();
    return 0; 
}
