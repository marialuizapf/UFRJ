#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

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

int push(PILHA* p, REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0;
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

int pop(PILHA* p, REGISTRO* reg) {
    if (p->topo == NULL) return 0; // Pilha vazia
    PONT temp = p->topo;
    *reg = temp->reg;
    p->topo = temp->prox;
    free(temp);
    return 1;
}

int main() {
    PILHA pilha;
    int numero;
    REGISTRO reg;

    inicializarPilha(&pilha);

    printf("Digite um número: ");
    scanf("%d", &numero);

    if (numero == 0) {
        reg.chave = 0;
        push(&pilha, reg);
    }

    while (numero > 0) {
        reg.chave = numero % 2;
        push(&pilha, reg);
        numero = numero / 2;
    }

    printf("Binário: ");
    while (pop(&pilha, &reg)) {
        printf("%d", reg.chave);
    }
    printf("\n");

    return 0;
}
