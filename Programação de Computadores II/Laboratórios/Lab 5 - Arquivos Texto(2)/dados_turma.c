#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    double prova[2];
    double trabalho;
}Taluno;

int main(){
    char entrada[100], saida[100];
    int N;
    Taluno aluno;

    printf("Digite o nome do arquivo:");
    scanf("%s", entrada);
    FILE *arq = fopen(entrada,"w");
    if(arq == NULL) return 1;

    printf("Digite quantos alunos terá: ");
    scanf("%d", &N);
    getchar(); 

    for (int i = 0; i< N;i++){
        printf("Digite o nome do aluno");
        fgets(aluno.nome, sizeof(aluno.nome), stdin);
        aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

        printf("Digite as notas das provas e do trabalho:");
        scanf("%lf %lf %lf",&aluno.prova[0], &aluno.prova[1], &aluno.trabalho);
        getchar(); 

        fprintf(arq,"%s %lf %lf %lf \n", aluno.nome, aluno.prova[0], aluno.prova[1],  aluno.trabalho);
    }

    fclose(arq);
    return 0;
}

