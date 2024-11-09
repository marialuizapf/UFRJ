1- 

altera_curso(CURSO *c, long int egr){
    
    c->egressos += egr;
}

2-

int * dif_ano(int ano_atual, DATA *anterior){
    
    int *dif = (int *)malloc(sizeof(int));
    
    if(dif == NULL){
        return NULL;
    }
    
    *dif = ano_atual - anterior->ano;
    
    return dif;
}

3- 

int recupera_txt(FILE *ft, CURSO *c){
    
    int campos_lidos = fscanf(ft,"%[^-]- %d/%d %ld", c->nome, &c->criacao.mes, &c->criacao.ano, &c->egressos);
    return campos_lidos;
}

4-

int grava_bin_txt(FILE *ft, FILE *fb){
    
    CURSO c;
    int cursos = 0;
    
    rewind(ft);
    
    while(recupera_txt(ft, &c) == 4){
        if(fwrite(&c, sizeof(CURSO),1, fb) == 1){
            cursos++;
        }
    }
    
    return cursos;
}

5-

int grava_curso_alterado(FILE *fb, int pos, long int egr){

    CURSO c;
    
    fseek(fb, pos*sizeof(CURSO), SEEK_SET);
    if(fread(&c, sizeof(CURSO),1, fb)!= 1){
        return 0;
    }
    
    altera_curso(&c, egr);
    
    fseek(fb, pos*sizeof(CURSO), SEEK_SET);
    if(fwrite(&c, sizeof(CURSO), 1, fb) == 1){
        return 1;
    }
    
    return 0;
}

6-

void exibe_bin(FILE *fb, int ano_atual){
    
    CURSO c;
    rewind(fb);
   
    while(fread(&c, sizeof(CURSO),1, fb)== 1){
        
        int *ano_exis = dif_ano(ano_atual, &c.criacao);
            
        if(ano_exis != NULL){
            printf("Curso:%s- Criacao:%d/%d(%d anos de existencia) - Egressos:%ld", c->nome, c->criacao.mes, c->criacao.ano, *ano_exis, c->egressos);
        
            free(ano_exis);
        }
    }
}
