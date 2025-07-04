#ifndef MENU_H
#define MENU_H

#include "save.h"

// Estados possiveis do menu
typedef enum {
    MENU_PRINCIPAL,
    NOVO_JOGO,
    CARREGAR_JOGO,
    SALVAR_JOGO,
    MENU_JOGO
} MenuState;

// Inicializa sistema de menu
void iniciarMenu(void);
// Atualiza input e retorna novo estado
MenuState atualizarMenu(MenuState* estado);
// Desenha o menu conforme estado atual
void desenharMenu(MenuState estado);

#endif // MENU_H