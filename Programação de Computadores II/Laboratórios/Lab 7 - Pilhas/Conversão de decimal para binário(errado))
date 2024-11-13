#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef struct Lista {
    TIPOCHAVE chave;
    struct Lista *prox;
} Lista;

Lista* cria_lista();
Lista* push(Lista* topo, TIPOCHAVE chave);
void imprime_lista(Lista *topo);

int main(void) {
    Lista* li = cria_lista();
    int dec, elem;
    
    printf("Digite um número inteiro: ");
    scanf("%d", &dec);
    
    while (dec > 0) {
        elem = dec % 2;
        li = push(li, elem);  
        dec = dec / 2;
    }
    
    imprime_lista(li);
    return 0;
}

Lista* cria_lista() {
    return NULL;
}

Lista* push(Lista* topo, TIPOCHAVE chave) {
    Lista *no = (Lista *) malloc(sizeof(Lista));
    if (no == NULL)
        exit(1);
        
    no->chave = chave;
    no->prox = topo;  
    return no;        
}

void imprime_lista(Lista *topo) {
    Lista *atual = topo;
    printf("Binário: ");
    
    while (atual != NULL) {
        printf("%d", atual->chave);
        atual = atual->prox;
    }
    printf("\n");
}


