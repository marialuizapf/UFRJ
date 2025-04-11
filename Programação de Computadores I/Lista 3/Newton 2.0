#include <stdio.h>
#include <math.h>

double newton_recursivo(double n, double x, double precisao) {
    double xi = x - ((pow(x, 2) - n) / (2 * x));
    if (fabs(xi - x) < precisao) {
        return xi;
    } else {
        return newton_recursivo(n, xi, precisao);
    }
}

int main(void) {
    double resultado;
    double n;

    printf("Digite um número racional positivo:\n");
    scanf("%lf", &n);

    if (n < 0) {
        printf("O número digitado não é positivo!\n");
        return 0;
    }

    resultado = sqrt(n);
    printf("A raiz quadrada de %lf calculada com a função sqrt é %lf\n", n, resultado);

    double x_inicial = n / 2;
    double precisao = 0.000001;

    double resultado_newton = newton_recursivo(n, x_inicial, precisao);
    printf("A raiz quadrada de %lf calculada com o método de Newton (recursivo) é %lf\n", n, resultado_newton);

    return 0;
}
