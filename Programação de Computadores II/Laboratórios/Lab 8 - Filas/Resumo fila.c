//-------------------- Modelagem --------------------
//----- Modicavel
typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;
//----- Fila
typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
} ELEMENTO;

typedef ELEMENTO* PONT;

typedef struct{
    PONT inicio;
    PONT fim;
} FILA;

//-------------------- Inicialização --------------------
void inicializarFila(FILA* f) {
    f->inicio = NULL;
    f->fim = NULL;
}

//-------------------- Tamanho --------------------
int tamanho(FILA* f){
    PONT end = f->inicio;
    int tam = 0;
    while (end != NULL){
        tam++;
        end = end->prox;
    }
    return tam;
}

//-------------------- Exibir --------------------
void exibirFila(FILA* f){
    PONT end = f->inicio;
    printf("Fila: \" ");
    while (end != NULL){
        printf("%i ", end->reg.chave);
        end = end->prox;
    }
    printf("\"\n");
}

//-------------------- Inserção --------------------
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

//-------------------- Exclusão --------------------
int excluirDaFila(FILA* f, REGISTRO* reg) {
    if (f->inicio==NULL) return 0; // Fila vazia
    *reg = f->inicio->reg;
    PONT apagar = f->inicio;
    f->inicio = f->inicio->prox;
    free(apagar);
    if (f->inicio == NULL) f->fim = NULL;
    return 1; 
}

//-------------------- Reinicialização --------------------
void reinicializarFila(FILA* f) {
    PONT end = f->inicio;
    while (end != NULL) {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    f->inicio = NULL;
    f->fim = NULL;
}

// -------------------- Verificar se está vazia --------------------
int estaVazia(FILA* f) {
    return (f->inicio == NULL);
}