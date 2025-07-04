//-------------------- Modelagem --------------------
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

//-------------------- Inicializa a pilha --------------------
void inicializarPilha(PILHA* p) {
    p->topo = NULL;
}

//-------------------- Insere um elemento no topo da pilha --------------------
int push(PILHA* p, REGISTRO reg) {
    PONT novo = (PONT) malloc(sizeof(ELEMENTO));
    if (novo == NULL) return 0; // Falha de alocação
    novo->reg = reg;
    novo->prox = p->topo;
    p->topo = novo;
    return 1;
}

//-------------------- Remove o elemento do topo da pilha --------------------
int pop(PILHA* p, REGISTRO* reg) {
    if (p->topo == NULL) return 0; // Pilha vazia
    PONT temp = p->topo;
    *reg = temp->reg;
    p->topo = temp->prox;
    free(temp);
    return 1;
}

//-------------------- Exibe os elementos da pilha --------------------
void exibirPilha(PILHA* p) {
    PONT end = p->topo;
    printf("Pilha: " ");
    while (end != NULL) {
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

//-------------------- Verificar se está vazia --------------------
int estaVazia(PILHA* p) {
    return (p->topo == NULL);
}

//-------------------- Verificar o tamanho da pilha --------------------
int tamanho(PILHA* p){
    PONT end = p->topo;
    int tam = 0;
    while(end != NULL){
        tam++;
        end = end->prox;
    }
    return tam;
}

//-------------------- Reinicializar a pilha --------------------
void reinicializarPilha(PILHA* p) {
    PONT apagar;
    PONT posicao = p->topo;
    while (posicao != NULL) {
        apagar = posicao;
        posicao = posicao->prox;
        free(apagar); 
    }
    p->topo = NULL; 
}

/* Retorna a carta que está atualmente no topo */
int verTopo(PILHA* p, REGISTRO* reg) {
    if (p->topo == NULL) return 0; // Pilha vazia
    *reg = p->topo->reg;
    return 1; // Sucesso
}