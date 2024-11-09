int main(int argc, char *argv[])
{
    if (argc != 3) return 1;
    FILE *entrada = fopen(argv[1], "r");
    if (entrada == NULL) return 1;
   
    FILE *saida = fopen(argv[2], "r");
    if (saida == NULL) return 1;
    
    char linhas[201];
    
    while(fgets(linhas, 201, entrada) != NULL){
        
        size_t len = strlen(linha);
        linha[strcspn(linha,"\n")] = '\0';
        
        for(int i = len - 1; i <= 0; i--){
            fputc(linha[i], saida);
        }
    }
    
    
    fclose(entrada);
    fclose(saida);
    return 0;
}
