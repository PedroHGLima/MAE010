#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 12000

int main(void)
{
    int my_rank, comm_sz, local_n;
    double *global_vector = NULL;
    double *local_vector = NULL;

    double local_min, local_max;
    double global_min = 0., global_max = 0.;
    double serial_min = 0., serial_max = 0.;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    local_n = N / comm_sz;
    local_vector = (double *)malloc(local_n * sizeof(double));

    if (my_rank == 0)
    {
        global_vector = (double *)malloc(N * sizeof(double));
        srand(time(NULL));

        global_vector[0] = (double)rand() / RAND_MAX;
        serial_min = global_vector[0];
        serial_max = global_vector[0];

        for (int i = 1; i < N; i++)
        {
            global_vector[i] = (double)rand() / RAND_MAX;
            if (global_vector[i] < serial_min)
                serial_min = global_vector[i];
            if (global_vector[i] > serial_max)
                serial_max = global_vector[i];
        }
    }

    MPI_Scatter(global_vector, local_n, MPI_DOUBLE, local_vector, local_n,
                MPI_DOUBLE, 0, MPI_COMM_WORLD);

    local_min = local_vector[0];
    local_max = local_vector[0];
    for (int i = 1; i < local_n; i++)
    {
        if (local_vector[i] < local_min)
            local_min = local_vector[i];
        if (local_vector[i] > local_max)
            local_max = local_vector[i];
    }

    MPI_Reduce(&local_min, &global_min, 1, MPI_DOUBLE, MPI_MIN, 0,
               MPI_COMM_WORLD);
    MPI_Reduce(&local_max, &global_max, 1, MPI_DOUBLE, MPI_MAX, 0,
               MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        printf("Global Minimum (MPI): %.5e | Serial: %.5e\n", global_min,
               serial_min);
        printf("Global Maximum (MPI): %.5e | Serial: %.5e\n", global_max,
               serial_max);

        char ok = (global_min == serial_min && global_max == serial_max) ? 1 : 0;
        printf("Check: %s\n", ok ? "Success" : "Failure");
        free(global_vector);
    }

    free(local_vector);
    MPI_Finalize();
    return 0;
}
