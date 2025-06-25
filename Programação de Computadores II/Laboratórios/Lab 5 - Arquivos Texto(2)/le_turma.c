#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nome[50];
    double prova[2];
    double trabalho;
}Taluno;

int main(){
    Taluno aluno;
    double media;

    char entrada[50];
    printf("Digite o nome do arquivo de entrada:");
    scanf("%s", entrada);
    FILE *arq1 = fopen(entrada, "r");
    if(arq1 == NULL) return 1;

    char saida[50];
    printf("Digite o nome do arquivo de saida:");
    scanf("%s", saida);
    FILE *arq2 = fopen(saida, "w");
    if(arq2 == NULL) return 1;

    while(fscanf(arq1,"%s %lf %lf %lf \n", aluno.nome, &aluno.prova[0], &aluno.prova[1], &aluno.trabalho) == 4){
        media = (((aluno.prova[0]+aluno.prova[1])/2) * 0.8) + (aluno.trabalho * (0.2));
        fprintf(arq2,"%s %lf \n", aluno.nome, media);
    }

    fclose(arq1);
    fclose(arq2);
    return 0;
}
