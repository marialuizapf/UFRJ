#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[50];
    int segundo_chegada;
    int n_produto;
    int tempo_saida;
}CLIENTE;

typedef struct aux{
    CLIENTE cliente;
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

int inserir(FILA* f, CLIENTE reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0; // Falha de alocação
    novo->cliente = reg;
    novo->prox = NULL;

    if (f->fim == NULL) { f->inicio = novo;
    } else { f->fim->prox = novo;
    }
    f->fim = novo;
    return 1;
}

void exibirFila(FILA* f){
    PONT end = f->inicio;
    printf("Fila: \" ");
    while (end != NULL){
        printf("%s %d %d ", end->cliente.nome, end->cliente.segundo_chegada, end->cliente.tempo_saida);
        end = end->prox;
        printf("\n");
    }
    printf("\"\n");
}

int main(){
    FILA f;
    CLIENTE c;
    int K, C, tempo_atual = 0;
    printf("Digite o número a rapidez dos clientes (K): ");
    scanf("%d", &K);
    printf("Digite o número de clientes (C): ");
    scanf("%d", &C);

    inicializarFila(&f);

    for(int i=0;i<C;i++){
        printf("Digite o número do cliente %d: ", i+1);
        scanf("%s %d %d", c.nome, &c.segundo_chegada, &c.n_produto);

        int inicio_atendimento = (tempo_atual > c.segundo_chegada) ? tempo_atual : c.segundo_chegada;
        c.tempo_saida = inicio_atendimento + 10 + (c.n_produto * K);
        tempo_atual = c.tempo_saida;

        inserir(&f, c);
    }

    printf("Fila de clientes:\n");
    exibirFila(&f);

    return 0;
}