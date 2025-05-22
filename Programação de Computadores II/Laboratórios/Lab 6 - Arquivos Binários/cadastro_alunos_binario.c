#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[100];
    double nota[3];
    double media;
}Taluno;

int main(){
    Taluno aluno;
    FILE *arq = fopen("alunos.dat", "wb+");
    if(arq == NULL) return 1;

    while(1){
        printf("Digite o nome do aluno: ");
        fgets(aluno.nome, sizeof(aluno.nome), stdin);
        aluno.nome[strcspn(aluno.nome, "\n")] = '\0';
        if (strlen(aluno.nome) == 0) break;

        printf("Digite a nota 1: ");
        scanf("%lf", &aluno.nota[0]);
        printf("Digite a nota 2: ");
        scanf("%lf", &aluno.nota[1]);
        printf("Digite a nota 3: ");
        scanf("%lf", &aluno.nota[2]);

        aluno.media = (aluno.nota[0] + aluno.nota[1] + aluno.nota[2]) / 3;

        if (fwrite(&aluno, sizeof(Taluno), 1, arq) != 1)
        {
            printf("Erro ao escrever no arquivo.\n");
            fclose(arq);
            return 1;
        } 

        while (getchar() != '\n');
    }

    fclose(arq);
    return 0;
}

