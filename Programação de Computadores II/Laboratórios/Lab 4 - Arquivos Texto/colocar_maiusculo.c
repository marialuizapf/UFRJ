#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc != 3) return 1;

    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) return 1;

    FILE *saida = fopen(argv[2] ,"w");
    if (saida == NULL) return 1;

    char letra;
    while((letra = fgetc(entrada)) != EOF){
        letra = toupper(letra);
        fputc(letra, saida);    
    }

    fclose(entrada);
    fclose(saida);
    return 0;
} 
 