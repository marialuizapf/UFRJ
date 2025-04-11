#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[100];
    double nota[3];
    double media;
} Taluno;

void exibirDados(Taluno aluno);

int main() {
    FILE *arq = fopen("alunos.dat", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    fseek(arq, 0, SEEK_END);
    int n_alunos = ftell(arq) / sizeof(Taluno);
    rewind(arq);

    Taluno *alunos = (Taluno *)malloc(n_alunos * sizeof(Taluno));
    if (alunos == NULL) {
        printf("Erro ao alocar memoria!\n");
        fclose(arq);
        return 1;
    }

    if (fread(alunos, sizeof(Taluno), n_alunos, arq) != n_alunos) {
        printf("Erro ao ler o arquivo!\n");
        free(alunos);
        fclose(arq);
        return 1;
    }

    int count_atualizados = 0;

    for (int i = 0; i < n_alunos; i++) {
        double media_antiga = alunos[i].media;
        alunos[i].media = (0.25 * alunos[i].nota[0]) + (0.35 * alunos[i].nota[1]) + (0.40 * alunos[i].nota[2]);
        if (media_antiga != alunos[i].media) {
            count_atualizados++;
        }

        printf("Aluno %d:\n", i + 1);
        exibirDados(alunos[i]);
    }

    rewind(arq);
    if (fwrite(alunos, sizeof(Taluno), n_alunos, arq) != n_alunos) {
        printf("Erro ao gravar no arquivo!\n");
        free(alunos);
        fclose(arq);
        return 1;
    }

    printf("Porcentagem de alunos com a média atualizada: %.2f%%\n", (count_atualizados * 100.0) / n_alunos);

    free(alunos);
    fclose(arq);
    return 0;
}

void exibirDados(Taluno aluno) {
    printf("Nome: %s\n", aluno.nome);
    printf("Nota 1: %.2lf\n", aluno.nota[0]);
    printf("Nota 2: %.2lf\n", aluno.nota[1]);
    printf("Nota 3: %.2lf\n", aluno.nota[2]);
    printf("Media: %.2lf\n", aluno.media);
}
