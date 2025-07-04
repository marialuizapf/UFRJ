#include "utils.h"
#include "mapa.h"
#include "jogador.h"
#include "bomba.h"
#include "inimigo.h"
#include "save.h"

bool entre(int val, int min, int max) {
    return (val >= min && val <= max);
}
/*
    * Função para reiniciar o jogo, recarregando o mapa, jogador, fila de bombas e inimigos.
    * Esta função é útil para reiniciar o jogo sem precisar fechar e abrir novamente a janela.
    * Ela libera os recursos do jogo atual e carrega novos recursos para um novo jogo.
    * Ela soluciona o problema de reiniciar o jogo sem precisar fechar a janela e abrir novamente,
    * e o problema de acumulo de recursos do jogo anterior ao só ser reiniciado.
    *
    * @param mapa Ponteiro para o mapa atual do jogo.
    * @param player Ponteiro para o jogador atual do jogo.
    * @param fila Ponteiro para a fila de bombas atual do jogo.
    * @param inimigos Ponteiro para a lista de inimigos atual do jogo.
*/
void reiniciarJogo(Mapa** mapa, Jogador** player, FilaBombas** fila, ListaInimigos** inimigos) {
    Mapa* novoMapa            = carregarMapa("mapas/mapa1.txt");
    Jogador* novoJogador      = criarJogador(novoMapa);
    FilaBombas* novaFila      = criarFilaBombas();
    ListaInimigos* novosInims = criarListaInimigos(novoMapa);

    liberarJogo(&(Jogo){
        .player   = *player,
        .mapa     = *mapa,
        .bombas   = *fila,
        .inimigos = *inimigos
    });

    *mapa     = novoMapa;
    *player   = novoJogador;
    *fila     = novaFila;
    *inimigos = novosInims;
}