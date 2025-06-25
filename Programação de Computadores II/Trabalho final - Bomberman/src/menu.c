#include <stdlib.h>
#include "raylib.h"
#include "menu.h"

void iniciarMenu(void) {
    // nada para inicializar no momento
}

MenuState atualizarMenu(MenuState* estado) {
    if (IsKeyPressed(KEY_TAB)) *estado = MENU_PRINCIPAL;
    switch (*estado) {
        case MENU_PRINCIPAL:
            if (IsKeyPressed(KEY_N)) *estado = MENU_JOGO;
            else if (IsKeyPressed(KEY_C)) *estado = MENU_JOGO;
            else if (IsKeyPressed(KEY_S)) *estado = MENU_JOGO;
            else if (IsKeyPressed(KEY_Q)) { CloseWindow(); exit(0); }
            else if (IsKeyPressed(KEY_V)) *estado = MENU_JOGO;
            else if (IsKeyPressed(KEY_DOWN)) *estado = MENU_CONFIGURACOES;
            break;
        case MENU_CONFIGURACOES:
            if (IsKeyPressed(KEY_DOWN)) *estado = MENU_AUDIO;
            else if (IsKeyPressed(KEY_V)) *estado = MENU_PRINCIPAL;
            break;
        case MENU_AUDIO:
            if (IsKeyPressed(KEY_V)) *estado = MENU_CONFIGURACOES;
            break;
        default: break;
    }
    return *estado;
}

void desenharMenu(MenuState estado) {
    DrawRectangle(0, 0, 1200, 100, GRAY);
    switch (estado) {
        case MENU_PRINCIPAL:
            DrawText("N: Novo   C: Carregar   S: Salvar   Q: Sair   V: Voltar", 50, 40, 20, BLACK);
            break;
        case MENU_CONFIGURACOES:
            DrawText("Configuracoes: Audio (Down) e V: Voltar", 50, 40, 20, BLACK);
            break;
        case MENU_AUDIO:
            DrawText("Audio: ajustes -> V: Voltar", 50, 40, 20, BLACK);
            break;
        default:
            break;
    }
}
