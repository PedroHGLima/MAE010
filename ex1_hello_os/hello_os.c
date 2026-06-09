#define _GNU_SOURCE
#include <mpi.h>
#include <sched.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int comm_sz, my_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    pid_t pid = getpid();
    int cpu = sched_getcpu();

    printf("Hello from rank %d/%d -- PID = %d, CPU = %d\n", my_rank, comm_sz,
           pid, cpu);

    MPI_Finalize();
    return 0;
}
