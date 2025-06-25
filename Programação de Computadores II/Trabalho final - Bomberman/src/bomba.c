#include <stdlib.h>
#include "raylib.h"
#include "bomba.h"
#include "jogador.h"

FilaBombas* criarFilaBombas(void) {
    FilaBombas* f = malloc(sizeof(FilaBombas)); f->head=f->tail=NULL; return f;
}

void liberarFilaBombas(FilaBombas* f) {
    Bomba* cur=f->head;
    while(cur) { Bomba* nxt=cur->next; free(cur); cur=nxt; }
    free(f);
}

void plantarBomba(FilaBombas* f, Jogador* j) {
    if (j->bombas<=0) return;
    Bomba* nova = malloc(sizeof(Bomba));
    nova->linha=j->linha; nova->coluna=j->coluna;
    nova->timer=TEMPO_EXPLOSAO; nova->next=NULL;
    if (!f->head) f->head=nova; else f->tail->next=nova;
    f->tail=nova; j->bombas--;
}

void atualizarBombas(FilaBombas* f, Jogador* j, Mapa* m, float dt) {
    Bomba *ant=NULL,*cur=f->head;
    while(cur) {
        cur->timer-=dt;
        // recolhimento
        if(cur==f->head && j->linha==cur->linha && j->coluna==cur->coluna && cur->timer>0) {
            f->head=cur->next; if(!f->head)f->tail=NULL;
            j->bombas++; free(cur); cur=f->head; ant=NULL; continue;
        }
        if(cur->timer<=0) {
            int r=RAIO_EXPLOSAO,li=cur->linha,co=cur->coluna;
            for(int d=-r;d<=r;d++){
                if(li+d>=0&&li+d<LINHAS) {
                    char prev=m->tiles[li+d][co];
                    if(prev=='D'||prev=='B'||prev=='K'){
                        m->tiles[li+d][co]=(prev=='K'?'C':' ');
                        j->pontuacao+=10;
                    }
                }
                if(co+d>=0&&co+d<COLUNAS) {
                    char prev=m->tiles[li][co+d];
                    if(prev=='D'||prev=='B'||prev=='K'){
                        m->tiles[li][co+d]=(prev=='K'?'C':' ');
                        j->pontuacao+=10;
                    }
                }
            }
            j->bombas++;
            if(!ant) f->head=cur->next; else ant->next=cur->next;
            if(cur==f->tail) f->tail=ant;
            Bomba* gone=cur; cur=cur->next; free(gone); continue;
        }
        ant=cur; cur=cur->next;
    }
}

void desenharBombas(FilaBombas* f) {
    for(Bomba* b=f->head;b;b=b->next)
        DrawRectangle(b->coluna*20,b->linha*20,20,20,BLACK);
}