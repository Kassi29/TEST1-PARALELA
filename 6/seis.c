#include <stdio.h>

#define MAX_TERMS 80  

void calcular_fibonacci(int n, long long fibonacci[]) {
    fibonacci[0] = 0;  
    fibonacci[1] = 1;  

    for (int i = 2; i < n; i++) {
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];  // Cálculo convencional
    }
}

int main() {
    int n;
    long long fibonacci[MAX_TERMS]; 

    printf("Ingrese el número de términos de Fibonacci a calcular (máx. %d): ", MAX_TERMS);
    scanf("%d", &n);

    if (n > 0 && n <= MAX_TERMS) {
        calcular_fibonacci(n, fibonacci);

        printf("Serie de Fibonacci:\n");
        for (int i = 0; i < n; i++) {
            printf("%lld ", fibonacci[i]);
        }
        printf("\n");
    } else {
        printf("Número de términos inválido. Debe estar entre 1 y %d.\n", MAX_TERMS);
    }

    return 0;
}
