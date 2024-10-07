#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char **argv) {
    int rank, size;
    int M, N, P;

    // Inicialización de MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // proceso 0 
    if (rank == 0) {
        printf("Ingrese el número de filas de la matriz A (M): ");
        scanf("%d", &M);
        printf("Ingrese el número de columnas de la matriz A y filas de la matriz B (N): ");
        scanf("%d", &N);
        printf("Ingrese el número de columnas de la matriz B (P): ");
        scanf("%d", &P);
    }

    // Distribuir las dimensiones a todos los procesos
    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&P, 1, MPI_INT, 0, MPI_COMM_WORLD);


    int *A = NULL;
    int *B = NULL;
    int *C = malloc(M * P * sizeof(int));

    if (rank == 0) {
        A = malloc(M * N * sizeof(int));
        B = malloc(N * P * sizeof(int));
        
        // Inicializar matriz C a 0
        for (int i = 0; i < M * P; i++) {
            C[i] = 0;
        }

        // El proceso 0 inicializa las matrices
        printf("Ingrese los valores de la matriz A:\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                printf("A[%d][%d]: ", i, j);
                scanf("%d", &A[i * N + j]);
            }
        }

        printf("Ingrese los valores de la matriz B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                printf("B[%d][%d]: ", i, j);
                scanf("%d", &B[i * P + j]);
            }
        }

        // Imprime matrices iniciales
        printf("\nMatriz A:\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                printf("%d ", A[i * N + j]);
            }
            printf("\n");
        }

        printf("\nMatriz B:\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                printf("%d ", B[i * P + j]);
            }
            printf("\n");
        }
    }

    // Distribuir la matriz B a todos los procesos
    if (rank != 0) {
        B = malloc(N * P * sizeof(int));
    }
    MPI_Bcast(B, N * P, MPI_INT, 0, MPI_COMM_WORLD);
    

    if (rank != 0) {
        A = malloc(M * N * sizeof(int));
    }
    MPI_Bcast(A, M * N, MPI_INT, 0, MPI_COMM_WORLD);


    for (int i = rank; i < M; i += size) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < N; k++) {
                C[i * P + j] += A[i * N + k] * B[k * P + j];
            }
        }
        printf("Proceso %d calculó la fila %d de la matriz C\n", rank, i);
    }

    // Proceso 0 recoge los resultados
    if (rank == 0) {
        for (int i = 1; i < size; i++) {

            MPI_Recv(&C[i * P], P, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    } else {
        MPI_Send(&C[rank * P], P, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }


    if (rank == 0) {
        printf("\nMatriz C (resultado):\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < P; j++) {
                printf("%d ", C[i * P + j]);
            }
            printf("\n");
        }
        free(A);
        free(B);
    }

    free(C);
    if (rank != 0) {
        free(A);
        free(B);
    }

    // Finalización de MPI
    MPI_Finalize();
    return 0;
}
