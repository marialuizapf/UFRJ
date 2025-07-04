#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct{
    PONT inicio;
    PONT fim;
} FILA;

void inicializarFila(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int inserir(FILA* f, REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0; // Falha de alocação
    novo->reg = reg;
    novo->prox = NULL;

    if (f->fim == NULL) { f->inicio = novo;
    } else { f->fim->prox = novo;
    }
    f->fim = novo;
    return 1;
}

int excluirDaFila(FILA* f, REGISTRO* reg) {
    if (f->inicio==NULL) return 0; // Fila vazia
    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if (f->inicio == NULL) f->fim = NULL;
    return 1; 
}

int estaVazia(FILA* f) {
    return (f->inicio == NULL);
}

int main(){
    FILA par, impar;
    REGISTRO reg;
    int num;

    inicializarFila(&par);
    inicializarFila(&impar);

    while(scanf("%d", &num) && num != 0){
        reg.chave = num;
        if(num % 2 == 0){
            inserir(&par, reg);
        }else if (num % 2 == 1){
            inserir(&impar, reg);
        }
    }

    while(!estaVazia(&par) || !estaVazia(&impar)){
    if (!estaVazia(&impar)){
        excluirDaFila(&impar, &reg);
        printf("Impar: %d\n", reg.chave);
    } 
    if (!estaVazia(&par)){
        excluirDaFila(&par, &reg);
        printf("Par: %d\n", reg.chave);
    }
    }
    return 0;
}