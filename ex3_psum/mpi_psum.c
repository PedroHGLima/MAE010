#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 12000

int main(int argc, char *argv[])
{
    int my_rank, comm_sz;
    double *global_vector = NULL;
    double *local_vector = NULL;
    int local_n;
    double local_sum = 0.0;
    double total_sum = 0.0;
    double serial_sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    local_n = N / comm_sz;
    local_vector = (double *)malloc(local_n * sizeof(double));

    if (my_rank == 0)
    {
        global_vector = (double *)malloc(N * sizeof(double));
        srand(time(NULL));
        for (int i = 0; i < N; i++)
        {
            global_vector[i] = (double)rand() / RAND_MAX;
            serial_sum += global_vector[i];
        }

        for (int i = 0; i < local_n; i++)
            local_vector[i] = global_vector[i];

        for (int dest = 1; dest < comm_sz; dest++)
            MPI_Send(&global_vector[dest * local_n], local_n, MPI_DOUBLE, dest,
                     0, MPI_COMM_WORLD);
    }
    else
        MPI_Recv(local_vector, local_n, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

    for (int i = 0; i < local_n; i++)
        local_sum += local_vector[i];

    if (my_rank == 0)
    {
        total_sum = local_sum;
        double partial_sum;
        for (int src = 1; src < comm_sz; src++)
        {
            MPI_Recv(&partial_sum, 1, MPI_DOUBLE, src, 1, MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);
            total_sum += partial_sum;
        }

        double rel_error = fabs(total_sum - serial_sum) / serial_sum;

        printf("Parallel Sum = %.15e\n", total_sum);
        printf("Serial Sum   = %.15e\n", serial_sum);
        printf("Relative Error = %.15e\n", rel_error);

        free(global_vector);
    }
    else
        MPI_Send(&local_sum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);

    free(local_vector);
    MPI_Finalize();
    return 0;
}
