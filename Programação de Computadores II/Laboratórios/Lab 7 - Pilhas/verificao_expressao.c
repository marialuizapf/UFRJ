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

int push(PILHA* p, REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0; // Falha de alocação
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
} 

int ehPar(char abre, char fecha) {
    return (abre == '(' && fecha == ')') ||
           (abre == '[' && fecha == ']') ||
           (abre == '{' && fecha == '}');
}

int main(){
    PILHA p;
    REGISTRO r;
    char expressao[100];
    char c;

    printf("Digite uma expressão: ");
    scanf("%s", expressao);

    int tam = strlen(expressao);
    
    inicializarPilha(&p);

    for (int i =0; i< tam; i++){
        c = expressao[i];
        if (c == '(' || c == '{' || c == '['){
            r.chave = c;
            push(&p, r);

        } else if (c == ')' || c == ']' || c == '}') {
            if (p.topo == NULL) return 0; // Pilha vazia, expressão inválida
            pop(&p, &r);
            if (!ehPar(r.chave, c)) return 0;
        }
    }

    
    if (p.topo == NULL) {
        printf("Expressão válida!\n");
    } else {
        printf("Expressão inválida!\n");
    }
    
    return 0;
}

