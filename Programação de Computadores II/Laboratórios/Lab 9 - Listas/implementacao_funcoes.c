#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0
typedef int bool;

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;
//----- Lista
typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct{
    PONT inicio;
} LISTA;

int tamanho(LISTA* l) {
    PONT end = l->inicio;
    int tam = 0;

    while (end != NULL) {
        tam++;
        end = end->prox;
    }
    return tam; 
}

void inicializarLista(LISTA* l){
    l->inicio = NULL;
}

int insere(LISTA* l, REGISTRO reg, int pos) {
    if (pos<0 || pos>tamanho(l)) return 0;
    ELEMENTO* novo = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    novo->reg = reg;
    int i;
    ELEMENTO* p;
    if (pos == 0){
        novo->prox = l->inicio;
        l->inicio = novo;
    }else{
        p = l->inicio;
        for (i=0;i<pos-1;i++) p = p->prox;
            novo->prox = p->prox;
            p->prox = novo;
    }
    return 1; 
}

void concatenaListas(LISTA* l1, LISTA* l2){
    PONT p = l2->inicio;
    int pos = tamanho(l1); // calcula uma vez
    while (p != NULL) {
        insere(l1, p->reg, pos);
        pos++; // já que inserimos no final, aumentamos a posição
        p = p->prox;
    }
}

bool iguaisListas(LISTA* l1, LISTA* l2){
    PONT p1 = l1->inicio;
    PONT p2 = l2->inicio;
    while (p1 != NULL && p2 != NULL) {
        if (p1->reg.chave != p2->reg.chave) {
            return false; // Se encontrar uma diferença, retorna falso
        }
        p1 = p1->prox;
        p2 = p2->prox;
    }
}

bool modificaElem(LISTA* l1, REGISTRO reg, int pos){
    if (pos < 0 || pos >= tamanho(l1)) return false; 

    PONT p = l1->inicio;
    for(int i = 0; i < pos;i++){
        p = p->prox;
    }
    p->reg.chave = reg.chave;
    return true; 
}

int main() {
    LISTA l1, l2;
    REGISTRO reg;

    inicializarLista(&l1);
    inicializarLista(&l2);

    for (int i = 1; i <= 3; i++) {
        reg.chave = i;
        insere(&l1, reg, tamanho(&l1));
    }

    for (int i = 4; i <= 6; i++) {
        reg.chave = i;
        insere(&l2, reg, tamanho(&l2));
    }

    concatenaListas(&l1, &l2);

    // Comparação
    if (iguaisListas(&l1, &l2)) {
        printf("Listas são iguais.\n");
    }

    reg.chave = 99;
    if (modificaElem(&l1, reg, 2)) {
        printf("Elemento modificado com sucesso.\n");
    } else {
        printf("Falha ao modificar.\n");
    }

    exibirLista(&l1);

    return 0;
}