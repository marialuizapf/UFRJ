#include <stdio.h>
#include <string.h>

int ocorrencia(char str1[100], char str2[100]){

  int i , j = 0;

  for (int i=0 ; i<strlen(str1) ; i++ ){

    if (str1[i] == str2[j] || str1[i] >= 'A' && str1[i] <= 'Z' && str1[i]+32 == str2[j] || str1[i] >= 'a' && str1[i] <= 'z' && str1[i]-32 == str2[j]){
      j++;
    } else{
      j = 0;
    }
    if (j == strlen(str2)){
      return 1;
    }
  }
  return 0;
}

int main (void){

  char str1[100], str2[100];

  printf("Escreva a primeira string:");
  fgets(str1, sizeof(str1), stdin);

  printf("Escreva a segunda string:");
  fgets(str2, sizeof(str2), stdin);

  str1[strcspn(str1, "\n")] = '\0';
  str2[strcspn(str2, "\n")] = '\0';

  if (ocorrencia(str1, str2)){
      printf("A segunda string é uma substring da primeira");
    }else{
      printf("A segunda string não é uma substring da primeira");
    }
  
  return 0;
}
