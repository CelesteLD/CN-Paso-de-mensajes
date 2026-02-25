#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size;
    int token;
    int next, prev;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    next = (rank + 1) % size;
    prev = (rank - 1 + size) % size;

    if (rank == 0) {
        token = 0;
        printf("Proceso %d inicia el token con valor %d\n", rank, token);

        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
        MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);

        printf("Proceso %d recibe el token final con valor %d\n", rank, token);
    } 
    else {
        MPI_Recv(&token, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &status);

        token++;
        printf("Proceso %d recibe token, lo incrementa a %d y lo envía a %d\n",
               rank, token, next);

        MPI_Send(&token, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}