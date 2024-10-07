#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    const int VECTOR_SIZE = 10;
    int vector1[VECTOR_SIZE], vector2[VECTOR_SIZE], result[VECTOR_SIZE];
    int local_sum = 0;

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // El procesador 0 inicializa los vectores
    if (rank == 0) {
        for (int i = 0; i < VECTOR_SIZE; i++) {
            vector1[i] = i + 1;  // Llenamos el primer vector con 1, 2, ..., 10
            vector2[i] = (i + 1) * 2;  // Llenamos el segundo vector con 2, 4, ..., 20
        }
        printf("Proceso %d ha inicializado los vectores:\n", rank);
        printf("  Vector 1: ");
        for (int i = 0; i < VECTOR_SIZE; i++) {
            printf("%d ", vector1[i]);
        }
        printf("\n  Vector 2: ");
        for (int i = 0; i < VECTOR_SIZE; i++) {
            printf("%d ", vector2[i]);
        }
        printf("\n");
    }

    // Distribuir los vectores a todos los procesos
    MPI_Bcast(vector1, VECTOR_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(vector2, VECTOR_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Proceso %d ha recibido los vectores.\n", rank);

    // Cada procesador suma sus posiciones
    if (rank == 1) {
        printf("Proceso %d (impar):\n", rank);
        for (int i = 1; i < VECTOR_SIZE; i += 2) { // Sumar posiciones impares
            local_sum += vector1[i] + vector2[i];
            printf("  Suma de posición impar %d: %d + %d = %d\n", i, vector1[i], vector2[i], vector1[i] + vector2[i]);
        }
    } else if (rank == 2) {
        printf("Proceso %d (par):\n", rank);
        for (int i = 0; i < VECTOR_SIZE; i += 2) { // Sumar posiciones pares
            local_sum += vector1[i] + vector2[i];
            printf("  Suma de posición par %d: %d + %d = %d\n", i, vector1[i], vector2[i], vector1[i] + vector2[i]);
        }
    }

    // Enviar la suma local al proceso 0
    int total_sum = 0;
    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    // El proceso 0 imprime la suma total
    if (rank == 0) {
        printf("La suma total de los vectores es: %d\n", total_sum);
    }

    // Finalización de MPI
    MPI_Finalize();
    return 0;
}
