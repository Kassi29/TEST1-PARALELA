#include <stdio.h>
// usando punteros
void suma(float *resultado, float a, float b) {
    *resultado = a + b;
}

void resta(float *resultado, float a, float b) {
    *resultado = a - b;
}

void multiplicacion(float *resultado, float a, float b) {
    *resultado = a * b;
}

void division(float *resultado, float a, float b) {
    if (b != 0) {
        *resultado = a / b;
    } else {
        printf("Error: División por cero.\n");
        *resultado = 0; // Devuelve 0 como valor por defecto
    }
}

int main() {
    float num1, num2, resultado;
    int opcion;

    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);


    printf("Seleccione una operación:\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicación\n");
    printf("4. División\n");
    printf("Opción: ");
    scanf("%d", &opcion);

    switch(opcion) {
        case 1:
            suma(&resultado, num1, num2);
            printf("Resultado: %.2f\n", resultado);
            break;
        case 2:
            resta(&resultado, num1, num2);
            printf("Resultado: %.2f\n", resultado);
            break;
        case 3:
            multiplicacion(&resultado, num1, num2);
            printf("Resultado: %.2f\n", resultado);
            break;
        case 4:
            division(&resultado, num1, num2);
            printf("Resultado: %.2f\n", resultado);
            break;
        default:
            printf("Opción inválida.\n");
            break;
    }

    return 0;
}