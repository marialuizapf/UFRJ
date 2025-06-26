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

    // Inicialização do jogo
    Mapa*           mapa     = carregarMapa("mapas/mapa1.txt");
    Jogador*        player   = criarJogador(mapa);
    FilaBombas*     fila     = criarFilaBombas();
    ListaInimigos*  inimigos = criarListaInimigos(mapa);
    MenuState       estado   = MENU_JOGO;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Lógica de jogo / menu
        if (estado == MENU_JOGO) {
            atualizarJogador(player, mapa, fila);
            if (IsKeyPressed(KEY_B)) plantarBomba(fila, player);
            atualizarBombas(fila, player, mapa, dt);
            atualizarInimigos(inimigos, mapa, dt);
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
    // Construímos aqui um Jogo temporário para chamar liberarJogo()
    Jogo jogo = {
        .player   = player,
        .mapa     = mapa,
        .bombas   = fila,
        .inimigos = inimigos,
        .faseAtual = 1
    };
    liberarJogo(&jogo);

    CloseWindow();
    return 0;
}
