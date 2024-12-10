#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int P1, P2, T;
    char nome[50];
} Aluno;

int main() {
    char nome_arquivo[100];
    int n_alunos;

    // Solicitar nome do arquivo
    printf("Digite o nome do arquivo: ");
    scanf("%s", nome_arquivo);

    // Abrir o arquivo para escrita
    FILE *fp = fopen(nome_arquivo, "w");
    if (fp == NULL) {
        printf("Erro na abertura do arquivo\n");
        return -1;
    }

    // Solicitar número de alunos
    printf("Digite o número de alunos: ");
    scanf("%d", &n_alunos);

    // Alocar memória para os alunos
    Aluno *alunos = (Aluno*) malloc(n_alunos * sizeof(Aluno));
    if (alunos == NULL) {
        printf("Falha na alocação de memória\n");
        fclose(fp);
        return 1;
    }

    // Ler dados de cada aluno
    for (int i = 0; i < n_alunos; i++) {
        getchar(); // Limpar buffer antes de usar fgets
        printf("Digite o nome do aluno %d: ", i + 1);
        fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0'; // Remover '\n'

        printf("Digite a nota da primeira prova (P1): ");
        scanf("%d", &alunos[i].P1);

        printf("Digite a nota da segunda prova (P2): ");
        scanf("%d", &alunos[i].P2);

        printf("Digite a nota do trabalho (T): ");
        scanf("%d", &alunos[i].T);

        // Escrever dados no arquivo
        fprintf(fp, "%s %d %d %d\n", alunos[i].nome, alunos[i].P1, alunos[i].P2, alunos[i].T);
    }

    // Liberar memória e fechar arquivo
    free(alunos);
    fclose(fp);

    printf("Dados gravados com sucesso no arquivo '%s'\n", nome_arquivo);
    return 0;
}
