#include <stdio.h>

float calcularPiRecursivo(int n) {
    if (n == 0) {
        return 1.0; // Caso base: 1/(2*0+1) = 1
    }
    // Llamada recursiva
    return ((n % 2 == 0 ? 1.0 : -1.0) / (2 * n + 1)) + calcularPiRecursivo(n - 1);
}

int main() {
    int n;
    float pi;

    printf("Ingrese el número de términos: ");
    scanf("%d", &n);

    pi = calcularPiRecursivo(n) * 4; // Multiplicamos por 4 para obtener π
    printf("Valor aproximado de pi (recursivo): %.10f\n", pi);

    return 0;
}
