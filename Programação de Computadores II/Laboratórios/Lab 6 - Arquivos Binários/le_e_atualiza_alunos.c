#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nome[100];
    double nota[3];
    double media;
} Taluno;

void exibe_struct(Taluno *aluno, int N);
void modifica_aluno(Taluno *aluno, int N, FILE *arq);

int main(){
    Taluno *aluno;
    int N;

    FILE *arq = fopen("alunos.dat", "rb+");
    if (arq == NULL) return 1;

    // Verifica o tamanho do arquivo
    fseek(arq, 0, SEEK_END);
    N = ftell(arq) / sizeof(Taluno);
    rewind(arq);

    // Aloca memória para os alunos
    aluno = (Taluno *) malloc(N * sizeof(Taluno));
    if (aluno == NULL) {
        fclose(arq);
        printf("Erro de alocação.\n");
        return 1;
    }

    // Lê os alunos do arquivo
    if (fread(aluno, sizeof(Taluno), N, arq) != N) {
        printf("Erro na leitura.\n");
        free(aluno);
        fclose(arq);
        return 1;
    }

    // Exibe os dados dos alunos de forma inicial
    printf("Dados iniciais:\n");
    exibe_struct(aluno, N);

    // Modifica os alunos
    modifica_aluno(aluno, N, arq);

    // Calcula percentual de launos com nota modificada
    double count = 0;
    double media_anterior;
    for(int i = 0; i < N; i++){
        media_anterior = (aluno[i].nota[0] + aluno[i].nota[1] + aluno[i].nota[2])/3.0;
        if (aluno[i].media != media_anterior){
            count++;
        }
    }
    double percentual = ((double)count / N) * 100;
    printf("Percentual de alunos com nota modificada: %.2lf%%\n", percentual);                          

    // Exibe os dados dos alunos
    printf("Dados atualizados:\n");
    exibe_struct(aluno, N);

    // Libera e fecha
    free(aluno);
    fclose(arq);
    return 0;
}

void exibe_struct(Taluno *aluno,int N){

    for(int i = 0;i < N;i++){
        printf("Nome: %s\n", aluno[i].nome);
        printf("Nota 1: %.2lf\n", aluno[i].nota[0]);
        printf("Nota 2: %.2lf\n", aluno[i].nota[1]);
        printf("Nota 3: %.2lf\n", aluno[i].nota[2]);
        printf("Media: %.2lf\n", aluno[i].media);
    }
}

void modifica_aluno(Taluno *aluno, int N, FILE *arq){
    rewind(arq);
    for (int i = 0;i<N;i++){
        aluno[i].media = ((25 * aluno[i].nota[0])/100) + ((35 * aluno[i].nota[1])/100) + ((40 * aluno[i].nota[2])/100);
    } 

    if(fwrite(aluno, sizeof(Taluno), N,arq) != N){
        printf("Erro na escrita.\n");
    } 
    rewind(arq);
}
