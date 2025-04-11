/*
Autor: Maria Luiza Pinheiro Ferreira
Data: <8/7/2024>
Descrição: Alteração  da Questão 7, de modo que o vetor de Pessoas seja agora ordenado em ordem crescente de peso.>
Entrada:<Nome, Peso e Idade>
Saída:<Tipo de dados>
Defesa:<Nome deve ser string, idade deve ser inteiro e peso deve ser float>
*/

#include <stdio.h>
#include <string.h>

typedef struct {
    char nome[50];
    float peso;
    int idade;
} Pessoa;

int buscaBinaria(Pessoa pessoas[], int n, float peso);

int main() {
    Pessoa pessoas[50];
    int n;

    printf("Digite a quantidade de pessoas (máximo 50): ");
    scanf("%d", &n);

    // Limpar o buffer de entrada
    while (getchar() != '\n');

    if (n > 50) {
        printf("Número de pessoas excede o máximo permitido!\n");
        return 1;
    }

    // Ler os dados das pessoas
    for (int i = 0; i < n; i++) {
        printf("Pessoa %d:\n", i + 1);

        printf("Digite o nome: ");
        fgets(pessoas[i].nome, 50, stdin);

        pessoas[i].nome[strcspn(pessoas[i].nome, "\n")] = 0;

        printf("Digite o peso: ");
        scanf("%f", &pessoas[i].peso);

        printf("Digite a idade: ");
        scanf("%d", &pessoas[i].idade);

        while (getchar() != '\n');
    }

    // Ordenar as pessoas por idade em ordem decrescente
    Pessoa temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (pessoas[i].peso > pessoas[j].peso) {
                temp = pessoas[i];
                pessoas[i] = pessoas[j];
                pessoas[j] = temp;
            }
        }
    }

    // Imprimir as pessoas ordenadas
    printf("\nPessoas ordenadas por idade (crescente):\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s, Peso: %.2f, Idade: %d\n", pessoas[i].nome, pessoas[i].peso, pessoas[i].idade);
    }

    // Solicitar peso para busca
    float pesoBusca;
    printf("\nDigite a peso para buscar: ");
    scanf("%f", &pesoBusca);

    // Realizar busca binária
    int indice = buscaBinaria(pessoas, n, pesoBusca);

    if (indice != -1) {
        printf("Pessoa encontrada: Nome: %s, Peso: %.2f, Idade: %d\n", pessoas[indice].nome, pessoas[indice].peso, pessoas[indice].idade);
    } else {
        printf("Nenhuma pessoa com peso %.2f foi encontrada.\n", pesoBusca);
    }

    return 0;
}

int buscaBinaria(Pessoa pessoas[], int n, float peso) {
    int esquerda = 0;
    int direita = n - 1;

    while (esquerda <= direita) {
        int meio = esquerda + (direita - esquerda) / 2;
        if (pessoas[meio].peso == peso) {
            return meio;
        } else if (pessoas[meio].peso < peso) {
            direita = meio + 1;
        } else {
            esquerda = meio - 1;
        }
    }

    return -1;
}
