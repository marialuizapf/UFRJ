#include <stdio.h>
#include <ctype.h>
#include <string.h>

void count_vowel(FILE *fp, int *vowel);

int main(){
  char nome_arquivo[100];

  printf("Digite o nome do arquivo: ");
  scanf("%s", nome_arquivo);
  
  FILE *fp = fopen(nome_arquivo, "r");
  if(fp == NULL){
    printf("Arquivo não pôde ser aberto\n");
    return -1;
  }

  int vowel[5] = {0, 0, 0, 0, 0};
  count_vowel(fp, vowel);
  char letters[] = {'a', 'e', 'i', 'o', 'u'};
  
  for(int i = 0; i < 5; i++){
    printf("A vogal '%c' aparece %d vezes\n", letters[i], vowel[i]);
  }
  
  fclose(fp);
  return 0;
}

void count_vowel(FILE *fp, int *vowel){
  char c;

  while((c = getc(fp)) != EOF){
    c = tolower(c);
    switch(c){
      case 'a':
        vowel[0]++;
        break;
      case 'e':
        vowel[1]++;
        break;
      case 'i':
        vowel[2]++;
        break;
      case 'o':
        vowel[3]++;
        break;
      case 'u':
        vowel[4]++;
        break;
    }
  }
}
