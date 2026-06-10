#include <mpi.h>
#include <stdio.h>
#include <string.h>

#define MAX_STRING 150

int main(int argc, char *argv[])
{
    int comm_sz, my_rank;
    char my_greeting[MAX_STRING];
    char recv_greeting[MAX_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    snprintf(my_greeting, MAX_STRING, "Greetings from rank %d!", my_rank);

    int dest = (my_rank + 1) % comm_sz;
    int src = (my_rank - 1 + comm_sz) % comm_sz;

    MPI_Sendrecv(my_greeting, strlen(my_greeting) + 1, MPI_CHAR, dest, 0,
                 recv_greeting, MAX_STRING, MPI_CHAR, src, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

    if (my_rank == 0)
    {
        printf("Rank 0 received: %s\n", recv_greeting);

        char buffer[MAX_STRING];
        for (int q = 1; q < comm_sz; q++)
        {
            MPI_Recv(buffer, MAX_STRING, MPI_CHAR, q, 1, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            printf("%s\n", buffer);
        }
    }
    else
        MPI_Send(recv_greeting, strlen(recv_greeting) + 1, MPI_CHAR, 0, 1,
                 MPI_COMM_WORLD);

    MPI_Finalize();
    return 0;
}
