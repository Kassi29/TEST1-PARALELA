#include <stdio.h>

void calcularPiIterativo(float *pi, int n) {
    *pi = 0.0;
    for (int i = 0; i < n; i++) {
        *pi += ((i % 2 == 0) ? 1.0 : -1.0) / (2 * i + 1);
    }
    *pi *= 4; // Multiplicamos por 4 para obtener π
}

int main() {
    float pi;
    int n;

    printf("Ingrese el número de términos: ");
    scanf("%d", &n);

    calcularPiIterativo(&pi, n);
    printf("Valor aproximado de pi (iterativo): %.10f\n", pi);

    return 0;
}
