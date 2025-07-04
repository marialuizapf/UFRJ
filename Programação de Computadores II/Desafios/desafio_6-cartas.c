#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int numero;
    char naipe;
} tCarta;

typedef struct aux {
    tCarta reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct {
    PONT topo;
} PILHA;

void exibeCarta(tCarta carta){
    if(carta.numero >=2 && carta.numero <= 10)
    printf("%d", carta.numero);
    else{
    switch(carta.numero){
    case 11:

    printf("Valete");
    break;

    case 12:

    printf("Dama");
    break;

    case 13:

    printf("Rei");
    break;

    case 1:

    printf("As");
    break;
    default: // 14

    printf("Invalida");
    }
    printf(" de ");
switch(carta.naipe){
case 'o':

printf("Ouros\n");
break;
case 'c':

printf("Copas\n");
break;

case 'p':printf("Paus\n");

break;
case 'e':
printf("Espadas\n");
}
}
}

int push(PILHA* p, tCarta reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0; // Falha de alocação
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

int pop(PILHA* p, tCarta* reg) {
    if (p->topo == NULL) return 0; // Pilha vazia
    PONT temp = p->topo;
    *reg = temp->reg;
    p->topo = temp->prox;
    free(temp);
    return 1;
}

int estaVazia(PILHA* p) {
    return (p->topo == NULL);
}

void empilhaBaralho(PILHA* p, tCarta reg) {
    char naipes[] = {'o', 'c', 'p', 'e'};
    for(int i=0; i<4;i++){
        for (int j = 1; j <= 13; j++){
            reg.numero =j;
            reg.naipe = naipes[i];
            push(p, reg);
        }
    }
}

void inicializarPilha(PILHA* p) {
    p->topo = NULL;
}

int buscaCarta(PILHA* p, tCarta carta) {
    int descarte = 0;
    tCarta atual;

    while (!estaVazia(p)) {
        atual = p->topo->reg;
        if (atual.numero == carta.numero && atual.naipe == carta.naipe) {
            break;
        }
        pop(p, &atual);
        descarte++;
    }
    return descarte;
}

int main(){
    PILHA p;
    tCarta carta;

    inicializarPilha(&p);
    empilhaBaralho(&p, carta);

    printf("Digite o numero da carta (1-13) e o naipe (o, c, p, e):\n");
    scanf("%d %c", &carta.numero, &carta.naipe);

    int descartadas = buscaCarta(&p,carta);

    exibeCarta(carta);         
    printf("%d\n", descartadas); 

    return 0;
}