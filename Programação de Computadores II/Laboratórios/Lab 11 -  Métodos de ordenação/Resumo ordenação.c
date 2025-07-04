/* -------- Bubble Sort -------- */
// Ordenação por pares do maior para o menor
// Complexidade: O(n^2) - pior caso / O(n) - melhor caso
void bolha(int v[], int tam) {
    int ult, i, aux;
    for (ult = tam - 1; ult > 0; ult--) {
        for (i = 0; i < ult; i++) {
            if (v[i] > v[i + 1]) {
                aux = v[i];
                v[i] = v[i + 1];
                v[i + 1] = aux;
            }
        }
    }
}

/* -------- Insertion Sort -------- */
// Igual a carta de baralho, onde você pega uma carta e coloca na posição correta
// Complexidade: O(n^2) - pior caso / O(n) - melhor caso
void insercao(int v[], int tam) {
    int i, aux, j;
    for (i = 1; i < tam; i++) {
        aux = v[i];
        j = i;
        while (j > 0 && aux < v[j - 1]) {
            v[j] = v[j - 1];
            j--;
        }
        v[j] = aux;
    }
}

/* -------- Selection Sort -------- */
// Seleciona o menor elemento e coloca na primeira posição, 
// depois seleciona o segundo menor e coloca na segunda posição, e assim por diante
// Complexidade: O(n^2) - pior caso / O(n^2) - melhor caso
void selecao(int v[], int tam) {
    int i, p, aux, posMenor;
    for (i = 0; i < tam - 1; i++) {
        posMenor = i;
        for (p = i + 1; p < tam; p++) {
            if (v[p] < v[posMenor])
                posMenor = p;
        }
        aux = v[i];
        v[i] = v[posMenor];
        v[posMenor] = aux;
    }
}

/* -------- Merge Sort -------- */
// Divide o vetor em duas metades, ordena cada metade e depois junta as duas metades ordenadas
// Complexidade: O(n log n) - pior caso / O(n log n) - melhor caso
void merge(int A[], int p, int q, int r) {
    int i, j, k;
    int tamseq1 = q - p + 1;
    int tamseq2 = r - q;

    int seq1[tamseq1], seq2[tamseq2];

    for(i = 0; i < tamseq1; i++)
        seq1[i] = A[p + i];

    for(j = 0; j < tamseq2; j++)
        seq2[j] = A[q + 1 + j];

    i = 0;
    j = 0;
    k = p;

    while (i < tamseq1 && j < tamseq2) {
        if (seq2[j] <= seq1[i]) {
            A[k] = seq2[j];
            j++;
        } else {
            A[k] = seq1[i];
            i++;
        }
        k++;
    }

    while (i < tamseq1) {
        A[k] = seq1[i];
        k++;
        i++;
    }

    while (j < tamseq2) {
        A[k] = seq2[j];
        k++;
        j++;
    }
}
