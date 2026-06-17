#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define N 12000

int main(int argc, char *argv[])
{
    int my_rank, comm_sz, local_n;
    double *x = NULL, *y = NULL, *z = NULL, *serial_z = NULL;
    double *local_x, *local_y, *local_z;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    local_n = N / comm_sz;
    local_x = (double *)malloc(local_n * sizeof(double));
    local_y = (double *)malloc(local_n * sizeof(double));
    local_z = (double *)malloc(local_n * sizeof(double));

    if (my_rank == 0)
    {
        x = (double *)malloc(N * sizeof(double));
        y = (double *)malloc(N * sizeof(double));
        z = (double *)malloc(N * sizeof(double));
        serial_z = (double *)malloc(N * sizeof(double));

        for (int i = 0; i < N; i++)
        {
            x[i] = i;
            y[i] = 2 * i;
            serial_z[i] = x[i] + y[i];
        }
    }

    MPI_Scatter(x, local_n, MPI_DOUBLE, local_x, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(y, local_n, MPI_DOUBLE, local_y, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_n; i++)
        local_z[i] = local_x[i] + local_y[i];

    MPI_Gather(local_z, local_n, MPI_DOUBLE, z, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        char ok = 1;
        for (int i = 0; i < N; i++)
            if (z[i] != serial_z[i])
                ok = 0;

        printf("Check gather: %s\n", ok ? "Success" : "Failure");

        free(x);
        free(y);
        free(z);
        free(serial_z);
    }

    free(local_x);
    free(local_y);
    free(local_z);
    MPI_Finalize();
    return 0;
}
