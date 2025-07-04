#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include "mapa.h"
#include "jogador.h"
#include "bomba.h"
#include "inimigo.h"

// Verifica se valor esta entre min e max (inclusive)
bool entre(int val, int min, int max);

// Reinicia o jogo, recarregando o mapa, jogador, fila de bombas e inimigos
void reiniciarJogo(Mapa** mapa, Jogador** player, FilaBombas** fila, ListaInimigos** inimigos);

#endif // UTILS_H