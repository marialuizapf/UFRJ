#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[100];
    double nota[3];
    double media;
} Taluno;

int main() {
    char nome_arquivo[100];
    int n_alunos;

    printf("Digite o nome do arquivo binário: ");
    scanf("%s", nome_arquivo);

    FILE *arq = fopen(nome_arquivo, "wb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    printf("Digite o número de alunos: ");
    if (scanf("%d", &n_alunos) != 1 || n_alunos <= 0) {
        printf("Número de alunos inválido!\n");
        fclose(arq);
        return 1;
    }

    Taluno *alunos = (Taluno *)malloc(n_alunos * sizeof(Taluno));
    if (alunos == NULL) {
        printf("Erro ao alocar memória!\n");
        fclose(arq);
        return 1;
    }

    for (int i = 0; i < n_alunos; i++) {
        printf("Digite o nome do aluno %d: ", i + 1);
        getchar();
        fgets(alunos[i].nome, sizeof(alunos[i].nome), stdin);
        alunos[i].nome[strcspn(alunos[i].nome, "\n")] = '\0';

        printf("Digite as 3 notas do aluno %d: ", i + 1);
        if (scanf("%lf %lf %lf", &alunos[i].nota[0], &alunos[i].nota[1], &alunos[i].nota[2]) != 3) {
            printf("Entrada inválida para as notas!\n");
            free(alunos);
            fclose(arq);
            return 1;
        }

        alunos[i].media = (alunos[i].nota[0] + alunos[i].nota[1] + alunos[i].nota[2]) / 3.0;
    }

    if (fwrite(alunos, sizeof(Taluno), n_alunos, arq) != (size_t)n_alunos) {
        printf("Erro ao escrever no arquivo!\n");
        free(alunos);
        fclose(arq);
        return 1;
    }

    printf("Dados gravados com sucesso no arquivo '%s'.\n", nome_arquivo);

    free(alunos);
    fclose(arq);
    return 0;
}
