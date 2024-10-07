#include <stdio.h>
#include <mpi.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    const int VECTOR_SIZE = 10;  
    char data[VECTOR_SIZE][20];  

    // Inicialización de MPI
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    if (rank == 0) {
        for (int i = 0; i < VECTOR_SIZE; i++) {
            snprintf(data[i], sizeof(data[i]), "Cadena %d", i);
        }
        printf("Proceso %d ha inicializado el vector.\n", rank);
        for (int i = 0; i < VECTOR_SIZE; i++) {
            printf("  %s\n", data[i]);  // Imprime el vector
        }
    }

    // Distribuir el vector a todos los procesos
    MPI_Bcast(data, VECTOR_SIZE * 20, MPI_CHAR, 0, MPI_COMM_WORLD);
    printf("Proceso %d ha recibido el vector.\n", rank);



    // Cada procesador despliega sus posiciones
    if (rank == 1) {
        printf("Proceso %d (impar):\n", rank);
        for (int i = 1; i < VECTOR_SIZE; i += 2) { // Inicia desde 1 y va de 2 en 2
           printf("  Posición impar %d: %s\n", i, data[i]);
    }
    } else if (rank == 2) {
          printf("Proceso %d (par):\n", rank);
          for (int i = 0; i < VECTOR_SIZE; i += 2) { // Inicia desde 0 y va de 2 en 2
          printf("  Posición par %d: %s\n", i, data[i]);
          }
}


    // Finalización de MPI
    MPI_Finalize();
    return 0;
}
