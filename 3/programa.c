#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char **argv)
{
    int rank, size, tag;
    MPI_Status status;
    char message[50];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    tag = 200;

    if (rank != 0) {
        // Código de los esclavos
        sprintf(message, "Mensaje enviado desde el proceso %d", rank);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, 0, tag, MPI_COMM_WORLD);
    }
    else {
        // Código del maestro
        printf("Maestro recibiendo mensajes...\n");

        // Mensajes en orden lógico (del proceso 1 al proceso size-1)
        /* for (int i = 1; i < size; i++) {
            MPI_Recv(message, 50, MPI_CHAR, i, tag, MPI_COMM_WORLD, &status);
            printf("Recibido del proceso %d: %s\n", i, message);
        } */

        // Mensajes en orden de llegada (cualquiera que llegue primero)
        for (int i = 1; i < size; i++) {
            MPI_Recv(message, 50, MPI_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            printf("Recibido del proceso %d: %s\n", status.MPI_SOURCE, message);
        }
    }
    MPI_Finalize();
    return 0;
}