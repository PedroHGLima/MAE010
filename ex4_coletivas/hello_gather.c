#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 100

int main(void)
{
    char greeting[MAX_STRING];
    char *recv_buffer = NULL;
    int comm_sz, my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    snprintf(greeting, MAX_STRING, "Greetings from process %d of %d!", my_rank,
             comm_sz);

    if (my_rank == 0)
    {
        recv_buffer = (char *)malloc(comm_sz * MAX_STRING * sizeof(char));
    }

    MPI_Gather(greeting, MAX_STRING, MPI_CHAR, recv_buffer, MAX_STRING,
               MPI_CHAR, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        for (int q = 0; q < comm_sz; q++)
        {
            printf("%s\n", &recv_buffer[q * MAX_STRING]);
        }
        free(recv_buffer);
    }

    MPI_Finalize();
    return 0;
}
