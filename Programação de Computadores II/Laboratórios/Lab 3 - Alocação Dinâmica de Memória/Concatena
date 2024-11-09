#include <stdio.h>
#include <string.h>

char *concatena(char *s1, char *s2);

int main(){

  char s1[100], s2[100];
  printf("Digite a primeira string:\n");
  fgets(s1, sizeof(s1), stdin);
  s1[strlen(s1) - 1] = '\0';

  printf("Digite a segunda string:\n");
  fgets(s2, sizeof(s2), stdin);
  s2[strlen(s2) - 1] = '\0';

  char *s3 = concatena(s1, s2);
  printf("String concatenada: %s\n", s3);
  
  return 0;
}

char *concatena(char *s1, char *s2){
  char *s3 = (char *)malloc(strlen(s1) + strlen(s2) + 1);
  int i;
  for (i = 0; s1[i] != '\0'; i++) {
      s3[i] = s1[i];
  }

  int j;
  for (j = 0; s2[j] != '\0'; j++, i++) {
      s3[i] = s2[j];
  }

  s3[i] = '\0';
  return s3;
}
