#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int P1, P2, T;
    float media;
    char nome[50];
} Aluno;

int contadorAluno(FILE *arq);

int main() {
    char nome_arq_entrada[50];
    char nome_arq_saida[50];

    // Solicitar o nome do arquivo de entrada
    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nome_arq_entrada);

    FILE *arq_entrada = fopen(nome_arq_entrada, "r");
    if (arq_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada\n");
        return -1;
    }

    // Solicitar o nome do arquivo de saída
    printf("Digite o nome do arquivo de saída: ");
    scanf("%s", nome_arq_saida);

    FILE *arq_saida = fopen(nome_arq_saida, "w");
    if (arq_saida == NULL) {
        printf("Erro ao abrir o arquivo de saída\n");
        fclose(arq_entrada);
        return -1;
    }

    // Contar o número de alunos no arquivo de entrada
    int n_alunos = contadorAluno(arq_entrada);

    // Alocar memória para os alunos
    Aluno *alunos = (Aluno *)malloc(n_alunos * sizeof(Aluno));
    if (alunos == NULL) {
        printf("Erro ao alocar memória\n");
        fclose(arq_entrada);
        fclose(arq_saida);
        return -1;
    }

    // Ler os dados dos alunos, calcular a média e gravar no arquivo de saída
    for (int i = 0; i < n_alunos; i++) {
        fscanf(arq_entrada, "%s %d %d %d", alunos[i].nome, &alunos[i].P1, &alunos[i].P2, &alunos[i].T);

        // Calcular a média do aluno
        alunos[i].media = (((alunos[i].P1 + alunos[i].P2) / 2.0) * 0.8) + (alunos[i].T * 0.2);

        // Gravar o nome e a média no arquivo de saída
        fprintf(arq_saida, "%s %.2f\n", alunos[i].nome, alunos[i].media);
    }

    // Liberar recursos
    fclose(arq_entrada);
    fclose(arq_saida);
    free(alunos);

    printf("Dados processados e gravados no arquivo '%s'.\n", nome_arq_saida);
    return 0;
}

// Função para contar o número de linhas no arquivo (número de alunos)
int contadorAluno(FILE *arq) {
    int n_aluno = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), arq) != NULL) {
        n_aluno++;
    }
    rewind(arq); // Reposicionar o ponteiro do arquivo no início
    return n_aluno;
}
