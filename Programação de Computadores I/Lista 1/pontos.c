#include <stdio.h>
#include <math.h>

int main() {
  
  float x1,y1,x2,y2,d;
  
  printf("Digite as coordenadas do primeiro ponto (x1, y1):");
  scanf("%f %f", &x1, &y1);
  printf("Digite as coordenadas do segundo ponto (x2, y2):");
  scanf("%f %f", &x2, &y2);
  
  d = sqrt(pow(x2 - x1,2) + pow(y2 - y1,2));
  
  printf("A distancia entre os pontos é %.2f\n", d);
  return 0;
  
}

  printf("A idade é correspondente a: %d ano(s), %d mes(es), %d dia(s)", anos, meses, dias);
  return 0;
}
