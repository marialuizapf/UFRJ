#include <stdlib.h>
#include "raylib.h"
#include "menu.h"
#include "save.h"
#include "jogador.h"

// ==========================================
// FUNÇÃO: iniciarMenu
// Descrição: Inicializa o menu (placeholder atual)
// ==========================================
void iniciarMenu(void) {
    // Por enquanto, nada a ser inicializado
}

// ==========================================
// FUNÇÃO: atualizarMenu
// Descrição: Atualiza o estado atual do menu com base nas teclas pressionadas.
//            O menu pode alternar entre o jogo, o menu principal e ações como salvar/carregar.
// Parâmetros: ponteiro para o estado atual do menu
// Retorna: novo estado do menu
// ==========================================
MenuState atualizarMenu(MenuState* estado) {
    // Pressionar TAB alterna entre jogo e menu principal
    if (IsKeyPressed(KEY_TAB))
        *estado = MENU_PRINCIPAL;

    switch (*estado) {
        case MENU_PRINCIPAL:
            if (IsKeyPressed(KEY_N)) {
                *estado = NOVO_JOGO; // Novo jogo
            }
            else if (IsKeyPressed(KEY_C)) {
                *estado = CARREGAR_JOGO; // Carregar jogo salvo
            }
            else if (IsKeyPressed(KEY_S)) {
                *estado = SALVAR_JOGO; // Salvar progresso atual
            }
            else if (IsKeyPressed(KEY_Q)) {
                CloseWindow(); // Encerra o jogo
                exit(0);
            }
            else if (IsKeyPressed(KEY_V)) {
                *estado = MENU_JOGO; // Volta ao jogo
            }
            break;

        default:
            break;
    }

    return *estado;
}

// ==========================================
// FUNÇÃO: desenharMenu
// Descrição: Desenha o menu principal na tela se estiver ativo
// Parâmetros: estado atual do menu
// ==========================================
void desenharMenu(MenuState estado) {
    if (estado == MENU_PRINCIPAL) {
        DrawRectangle(0, 0, 1200, 100, GRAY); // Fundo do menu
        DrawText("N: Novo   C: Carregar   S: Salvar   Q: Sair   V: Voltar", 
                 50, 40, 20, BLACK);
    }
}
