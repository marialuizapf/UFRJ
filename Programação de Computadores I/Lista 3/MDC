#include <stdio.h>

int numDigitos(int x) {
  
    if (x == 0) {
        return 1;
    }
    if (x < 0) {
        x = -x;
    }
    if (x / 10 == 0) {
        return 1;
    } else {
        return 1 + numDigitos(x / 10);
    }
}
