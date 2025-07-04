#include <stdio.h>
#include <stdlib.h>

typedef char TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} REGISTRO;

typedef struct aux {
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT topo;
} PILHA;


void inicializarPilha(PILHA* p) {
    p->topo = NULL;
}

int pop(PILHA* p, REGISTRO* reg) {
    if (p->topo == NULL) return 0; // Pilha vazia
    PONT temp = p->topo;
    *reg = temp->reg;
    p->topo = temp->prox;
    free(temp);
    return 1;
}

int push(PILHA* p, REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0; // Falha de alocação
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

int tamanho(PILHA* p){
    PONT end = p->topo;
    int tam = 0;
    while(end != NULL){
        tam++;
        end = end->prox;
    }
    return tam;
}

int main(){
    PILHA p;
    REGISTRO r;
    char palavra[100];
    char c;
    int contador = 0;

    inicializarPilha(&p);

    printf("Digite uma palavra:");
    scanf("%s", palavra);
    int  tam = strlen(palavra);

    for (int i =0; i<tam; i++){
        r.chave = palavra[i];
        push(&p, r);
    }

    for(int i = 0; i<tam/2;i++){
        pop(&p, &r);
        if(r.chave == palavra[i]){
            contador++;
        } 
    }

    if (contador == tam/2){
        printf("A palavra eh um palindromo\n");
    } else {
        printf("A palavra nao eh um palindromo\n");
    }

    return 0;
}