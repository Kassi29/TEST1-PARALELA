#include <stdio.h>

float suma(float a, float b) {
    return a + b;
}

float resta(float a, float b) {
    return a - b;
}

float multiplicacion(float a, float b) {
    return a * b;
}

float division(float a, float b) {
    if (b != 0) {
        return a / b;
    } else {
        printf("Error: División por cero.\n");
        return 0; 
    }
}

int main() {
    float num1, num2;
    int opcion;

    printf("Ingrese el primer número: ");
    scanf("%f", &num1);
    printf("Ingrese el segundo número: ");
    scanf("%f", &num2);

    // Mostrar opciones de operaciones
    printf("Seleccione una operación:\n");
    printf("1. Suma\n");
    printf("2. Resta\n");
    printf("3. Multiplicación\n");
    printf("4. División\n");
    printf("Opción: ");
    scanf("%d", &opcion);


    switch(opcion) {
        case 1:
            printf("Resultado: %.2f\n", suma(num1, num2));
            break;
        case 2:
            printf("Resultado: %.2f\n", resta(num1, num2));
            break;
        case 3:
            printf("Resultado: %.2f\n", multiplicacion(num1, num2));
            break;
        case 4:
            printf("Resultado: %.2f\n", division(num1, num2));
            break;
        default:
            printf("Opción inválida.\n");
            break;
    }

    return 0;
}
