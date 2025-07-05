#include <stdlib.h>
#include "raylib.h"
#include "menu.h"
#include "save.h"
#include "jogador.h"

void iniciarMenu(void) {
    // nada para inicializar no momento
}

/*
    *Função que atualiza o estado do menu do jogo passando de MENU_PRINCIPAL para MENU_JOGO
    *e vice-versa, dependendo das teclas pressionadas. O MENU_JOGO é o estado onde o jogo
    *está rodando, enquanto o MENU_PRINCIPAL é o estado onde o usuário pode escolher
    *opções como novo jogo, carregar jogo, salvar jogo ou sair do jogo. 
*/
MenuState atualizarMenu(MenuState* estado) {
    if (IsKeyPressed(KEY_TAB)) *estado = MENU_PRINCIPAL;
    switch (*estado) {
        case MENU_PRINCIPAL:
            if (IsKeyPressed(KEY_N)) *estado = NOVO_JOGO; // Inicia novo jogo
            else if (IsKeyPressed(KEY_C)) *estado = CARREGAR_JOGO; // Carrega jogo salvo
            else if (IsKeyPressed(KEY_S)) *estado = SALVAR_JOGO; // Salva jogo atual
            else if (IsKeyPressed(KEY_Q)) { CloseWindow(); exit(0); } // Sai do jogo
            else if (IsKeyPressed(KEY_V)) *estado = MENU_JOGO; // Volta para o jogo
            break;
        default: break;
    }
    return *estado;
}

// Função que desenha o menu na tela de acordo com o estado atual do menu.
void desenharMenu(MenuState estado) {
    switch (estado) {
        case MENU_PRINCIPAL:
            DrawRectangle(0, 0, 1200, 100, GRAY);
            DrawText("N: Novo   C: Carregar   S: Salvar   Q: Sair   V: Voltar", 50, 40, 20, BLACK);
            break;
        default:
            break;
    }
}
