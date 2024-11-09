#include <stdio.h>

int main(int argc, char *argv[]){

  if(argc != 3) return 1;

  FILE *entry = fopen(argv[1], "r");
  if (entry == NULL) return 1;
  
  FILE *exit = fopen(argv[2], "w");
  if (exit == NULL) return 1;

  char c;
  while((c = fgetc(entry)) != EOF){
    
    if(c >= 'a' && c <= 'z'){
      c-=32;
       fputc(c, exit);
      // fputc(toupper(c), exit);
    }else{
      fputc(c, exit);
    }
  }
  
  fclose(entry);
  fclose(exit);
  
  return 0;
}

