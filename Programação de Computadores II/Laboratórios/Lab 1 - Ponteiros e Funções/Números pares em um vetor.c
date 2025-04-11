#include <stdio.h>

void pares(int *v, int *n) {
  
    int count = 0;
    for (int i = 0; i < *n; i++) {
        if (v[i] % 2 == 0) {  // Verifica se o número é par
            count++;  // Conta os números pares
        }
    }

    // Atualiza o valor apontado por n com a quantidade de números pares
    *n = count;
}

int main() {
    int vetor[100];
    int n, count, m;

    // Lê o tamanho do vetor (n primeiros elementos)
    printf("Digite o tamanho do vetor:\n");
    scanf("%d", &m);

    // Lê os elementos do vetor
    printf("Escreva uma sequência de números:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &vetor[i]);
    }

    printf("Por quantos números deve percorrer o vetor?\n");
    scanf("%d", &n);
    if(n > m){
      printf("O valor de n não pode ser maior que o tamanho do vetor!");
      return 1;
    }
  
    count = n; 
    pares(vetor, &count);

    printf("Há %d números pares nos primeiros %d números do vetor\n", count, n);

    return 0;
}
