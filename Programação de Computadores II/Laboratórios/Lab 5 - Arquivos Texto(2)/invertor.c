#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if(argc != 3) return 1;

    FILE *arq1 = fopen(argv[1], "r");
    if(arq1 == NULL) return 1;

    FILE *arq2 = fopen(argv[2], "w");
    if(arq2 == NULL) return 1;

    char linha[200];
    char invertida[200];
    while(fgets(linha, 200, arq1) != NULL){
        linha[strcspn(linha,"\n")] = '\0';
        int N = strlen(linha);
        for(int i=0;i<N;i++){
            invertida[i] = linha[N-i-1];
        }
        invertida[N] = '\0';
        fprintf(arq2,"%s\n", invertida);
    }

    fclose(arq1);
    fclose(arq2);
    return 0;
}