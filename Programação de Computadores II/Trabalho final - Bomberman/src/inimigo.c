#include <stdlib.h>
#include "raylib.h"
#include "inimigo.h"
#include "utils.h"

ListaInimigos* criarListaInimigos(Mapa* mapa) {
    ListaInimigos* lista = malloc(sizeof(ListaInimigos)); lista->head=NULL;
    Inimigo* last = NULL;
    for(int i=0;i<LINHAS;i++) for(int j=0;j<COLUNAS;j++) if(mapa->tiles[i][j]=='E'){
        Inimigo* inim = malloc(sizeof(Inimigo));
        inim->linha=i; inim->coluna=j;
        inim->direcao = GetRandomValue(0,3);
        inim->tempoTroca = 1.0f;
        inim->next = NULL;
        if(!lista->head) lista->head=inim;
        else last->next=inim;
        last=inim;
        mapa->tiles[i][j]=' ';
    }
    return lista;
}

void atualizarInimigos(ListaInimigos* lista, Mapa* mapa, float dt) {
    for(Inimigo* cur=lista->head;cur;cur=cur->next) {
        cur->tempoTroca -= dt;
        if(cur->tempoTroca<=0) { cur->direcao=GetRandomValue(0,3); cur->tempoTroca=1.0f; }
        int nx=cur->coluna,ny=cur->linha;
        switch(cur->direcao) {
            case DIR_CIMA: ny--; break;
            case DIR_BAIXO: ny++; break;
            case DIR_ESQUERDA: nx--; break;
            case DIR_DIREITA: nx++; break;
        }
        if(entre(nx,0,COLUNAS-1) && entre(ny,0,LINHAS-1) && mapa->tiles[ny][nx]==' ') {
            cur->coluna=nx; cur->linha=ny;
        } else { cur->direcao=GetRandomValue(0,3); }
    }
}

void desenharInimigos(ListaInimigos* lista) {
    for(Inimigo* cur=lista->head;cur;cur=cur->next)
        DrawRectangle(cur->coluna*20,cur->linha*20,20,20,RED);
}

void liberarInimigos(ListaInimigos* lista) {
    Inimigo* cur=lista->head;
    while(cur){ Inimigo* nxt=cur->next; free(cur); cur=nxt; }
    free(lista);
}

