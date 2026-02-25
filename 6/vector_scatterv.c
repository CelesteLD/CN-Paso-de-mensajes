#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, size;
    int N = 18;  // tamaño NO divisible por 4 por ejemplo
    int *vector = NULL;
    int *resultado = NULL;

    int *sendcounts = NULL;
    int *displs = NULL;

    int local_n;
    int *subvector;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Solo el root calcula cómo repartir
    if (rank == 0) {

        vector = malloc(N * sizeof(int));
        resultado = malloc(N * sizeof(int));
        sendcounts = malloc(size * sizeof(int));
        displs = malloc(size * sizeof(int));

        for (int i = 0; i < N; i++)
            vector[i] = i + 1;

        int base = N / size;
        int resto = N % size;

        int offset = 0;
        for (int i = 0; i < size; i++) {
            sendcounts[i] = base + (i < resto ? 1 : 0);
            displs[i] = offset;
            offset += sendcounts[i];
        }

        printf("Vector original:\n");
        for (int i = 0; i < N; i++)
            printf("%d ", vector[i]);
        printf("\n");
    }

    // Primero todos necesitan saber cuánto van a recibir
    if (rank != 0) {
        sendcounts = malloc(size * sizeof(int));
    }

    MPI_Bcast(sendcounts, size, MPI_INT, 0, MPI_COMM_WORLD);

    local_n = sendcounts[rank];
    subvector = malloc(local_n * sizeof(int));

    // Scatterv
    MPI_Scatterv(vector, sendcounts, displs, MPI_INT,
                 subvector, local_n, MPI_INT,
                 0, MPI_COMM_WORLD);

    // Operación local (multiplicar por 3)
    for (int i = 0; i < local_n; i++)
        subvector[i] *= 3;

    // Gatherv
    MPI_Gatherv(subvector, local_n, MPI_INT,
                resultado, sendcounts, displs, MPI_INT,
                0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Vector procesado:\n");
        for (int i = 0; i < N; i++)
            printf("%d ", resultado[i]);
        printf("\n");

        free(vector);
        free(resultado);
        free(displs);
    }

    free(sendcounts);
    free(subvector);

    MPI_Finalize();
    return 0;
}