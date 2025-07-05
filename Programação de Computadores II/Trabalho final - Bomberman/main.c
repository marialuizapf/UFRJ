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
    // Configurações da janela
    const int largura = 1200; // Largura da janela
    const int altura  = 600; // Altura da janela
    InitWindow(largura, altura, "Bomberman - Versão Final"); // Título da janela
    SetTargetFPS(60); // Taxa de quadros por segundo

    // Inicialização do jogo
    Mapa*           mapa     = carregarMapa("mapas/mapa1.txt");
    Jogador*        player   = criarJogador(mapa);
    FilaBombas*     fila     = criarFilaBombas();
    ListaInimigos*  inimigos = criarListaInimigos(mapa);
    MenuState       estado   = MENU_JOGO;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Lógica de jogo
        if (estado == MENU_JOGO) {
            atualizarJogador(player, mapa, fila);
            if (IsKeyPressed(KEY_B)) {
                plantarBomba(fila, player, mapa);
            }
                        
            atualizarBombas(fila, player, mapa, inimigos, dt);
            atualizarInimigos(inimigos, mapa, dt);
        }

        if(estado == NOVO_JOGO){
            liberarJogo(&(Jogo){
                .player   = player,
                .mapa     = mapa,
                .bombas   = fila,
                .inimigos = inimigos
            });

            mapa     = carregarMapa("mapas/mapa1.txt");
            player   = criarJogador(mapa);
            fila     = criarFilaBombas();
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

        estado = atualizarMenu(&estado);

        // Renderização
        BeginDrawing();
            ClearBackground(BLUE);
            desenharMapa(mapa);
            desenharBombas(fila);
            desenharInimigos(inimigos);
            desenharJogador(player);
            desenharMenu(estado);

            DrawRectangle(0, 500, 1200, 100, SKYBLUE);  
            DrawText(TextFormat("Bombas: %d", player->bombas),       20, 520, 20, BLACK);
            DrawText(TextFormat("Vidas: %d", player->vidas),        300, 520, 20, BLACK);
            DrawText(TextFormat("Pontuacao: %d", player->pontuacao), 600, 520, 20, BLACK);
        EndDrawing();
    }

    // Libera todo o estado do jogo
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
