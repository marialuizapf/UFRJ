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

// Inicializa sistema de menu (placeholder para futuras expansões)
void iniciarMenu(void);

// Atualiza input do menu e retorna o novo estado
MenuState atualizarMenu(MenuState* estado);

// Desenha o menu conforme o estado atual
void desenharMenu(MenuState estado);

#endif // MENU_H