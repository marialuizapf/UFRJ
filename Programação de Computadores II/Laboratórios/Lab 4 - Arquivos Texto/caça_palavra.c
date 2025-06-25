#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
    if (argc != 3) return 1;
    char *palavra = argv[1];
    FILE *entrada = fopen(argv[2], "r");
    if (entrada == NULL) return 1;

    int tamanho = strlen(palavra);
    char linha[81];
    int i = 1;

    while (fgets(linha, 80, entrada) != NULL) {
        if(strstr(linha, palavra) != NULL){
           printf("%d %s", i, palavra);
        }
        i++;
    }

    fclose(entrada);
    return 0;   
}