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

    /*
    
    */
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Lógica de jogo
        if (estado == MENU_JOGO) {
            atualizarJogador(player, mapa, fila);
            if (IsKeyPressed(KEY_B)) plantarBomba(fila, player);
            atualizarBombas(fila, player, mapa, dt);
            atualizarInimigos(inimigos, mapa, dt);
        }
<<<<<<< Updated upstream

        if(estado == NOVO_JOGO){

        }

=======
        /*
        Para reinicializar o jogo 
        */
        if(estado == NOVO_JOGO){
            reiniciarJogo(&mapa, &player, &fila, &inimigos);
            estado = MENU_JOGO;
        }
>>>>>>> Stashed changes
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
        .inimigos = inimigos,
        .faseAtual = 1
    };
    liberarJogo(&jogo);

    CloseWindow();
    return 0;
}
