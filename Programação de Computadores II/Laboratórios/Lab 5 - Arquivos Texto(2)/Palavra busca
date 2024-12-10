#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Função para converter uma string para minúsculas
void colocarMinusculo(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Função para comparar strings sem usar strcmp
int comparar_strings(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) {
            return 0;
        }
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}

int main() {
    char nome_arquivo[100];
    char palavra_busca[50];
    char palavra[50];
    int contador = 0;

    // Solicitar o nome do arquivo
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);

    // Solicitar a palavra a ser buscada
    printf("Digite a palavra a ser buscada: ");
    scanf("%s", palavra_busca);

    // Converter a palavra de busca para minúsculas
    colocarMinusculo(palavra_busca);

    // Abrir o arquivo para leitura
    FILE *fp = fopen(nome_arquivo, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 1;
    }

    // Ler cada palavra do arquivo
    while (fscanf(fp, "%s", palavra) != EOF) {
        // Converter a palavra lida para minúsculas
        colocarMinusculo(palavra);

        if (comparar_strings(palavra, palavra_busca)) {
            contador++;
        }
    }

    fclose(fp);

    printf("A palavra '%s' aparece %d vezes no arquivo '%s'.\n", palavra_busca, contador, nome_arquivo);

    return 0;
}
