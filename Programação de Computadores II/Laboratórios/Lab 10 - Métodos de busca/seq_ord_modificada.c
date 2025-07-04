
void buscaSeqOrdRep(int arr[], int tam, int el, int *pos, int *quant) {
    *pos = -1;
    *quant = 0;

    for (int i = 0; i < tam; i++) {
        if (arr[i] > el) {
            break;
        }
        if (arr[i] == el) {
            if (*pos == -1) {
                *pos = i;  
            }
            (*quant)++;
        }
    }
}

int main(){
    int arr[100], tam, el, pos, quant;
    printf("Digite a quantidade de elementos do vetor: ");
    scanf("%d", &tam);
    printf("Digite os elementos do vetor:");
    for (int i = 0; i < tam; i++) {
        scanf("%d", &arr[i]);
    }
    printf("Digite o elemento procurado: ");
    scanf("%d", &el);

    buscaSeqOrdRep(arr, tam, el, &pos, &quant);

   
    if (pos != -1) {
        printf("Valor encontrado pela primeira vez na posição %d\n", pos+1);
        printf("Número de ocorrências: %d\n", quant);
    } else {
        printf("Valor não encontrado.\n");
    }

    return 0;
}