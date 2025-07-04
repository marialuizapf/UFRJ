/* -------- Busca sequencial -------- */

// Varrer o vetor inteiro e comparar cada elemento com o valor procurado
// Se encontrar, retorna o índice do elemento
// Complexidade: O(n) - pior / O(1) - melhor caso
int buscaSeq(int arr[], int tam, int el) {
    for (int i = 0; i < tam; i++) {
        if (arr[i] == el)
            return i;
    }
    return -1;
}

/* -------- Busca sequencial (Ordenada) -------- */

// Ordenar o vetor antes de fazer a busca
int buscaSeqOrd(int arr[], int tam, int el) {
    for (int i = 0; i < tam; i++) {
        if (arr[i] >= el) {
            if (arr[i] == el)
                return i;
            else
                return -1;
        }
    }
    return -1;
}
/* -------- Busca Binária -------- */

// Ordenar o vetor antes de fazer a busca
// verifica se o elemento é no meio, se não, verifica se esta 
//na primeira metade ou na segunda metade do vetor
// Complexidade: O(log n) - pior caso / O(1) - melhor caso
int buscaBin(int arr[], int tam, int el) {
    int ini = 0, fim = tam - 1;
    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        if (arr[meio] < el) {
            ini = meio + 1;
        } else if (arr[meio] > el) {
            fim = meio - 1;
        } else {
            return meio;
        }
    }
    return -1;
}
