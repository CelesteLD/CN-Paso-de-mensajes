#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {

    int rank, size;
    int N = 16;  // tamaño total del vector
    int *vector = NULL;
    int *subvector = NULL;
    int *resultado = NULL;
    int local_n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    local_n = N / size;  // tamaño por proceso

    subvector = (int *) malloc(local_n * sizeof(int));

    if (rank == 0) {
        vector = (int *) malloc(N * sizeof(int));
        resultado = (int *) malloc(N * sizeof(int));

        // Inicializar vector
        for (int i = 0; i < N; i++)
            vector[i] = i + 1;

        printf("Vector original:\n");
        for (int i = 0; i < N; i++)
            printf("%d ", vector[i]);
        printf("\n");
    }

    // Distribuir partes del vector
    MPI_Scatter(vector, local_n, MPI_INT,
                subvector, local_n, MPI_INT,
                0, MPI_COMM_WORLD);

    // Operación local (multiplicar por 2)
    for (int i = 0; i < local_n; i++)
        subvector[i] = subvector[i] * 2;

    // Recoger resultados
    MPI_Gather(subvector, local_n, MPI_INT,
               resultado, local_n, MPI_INT,
               0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Vector procesado:\n");
        for (int i = 0; i < N; i++)
            printf("%d ", resultado[i]);
        printf("\n");

        free(vector);
        free(resultado);
    }

    free(subvector);

    MPI_Finalize();
    return 0;
}