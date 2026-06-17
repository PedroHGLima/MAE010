#include <stdio.h>
#include <string.h>
#include <mpi.h>

struct Student
{
    char name[50];
    double grade;
    int id;
};

int main(int argc, char *argv[])
{
    int my_rank;
    struct Student student;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if (my_rank == 0)
    {
        snprintf(student.name, 50, "Alice");
        student.grade = 9.5;
        student.id = 12345;
    }

    MPI_Bcast(student.name, 50, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(&student.grade, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&student.id, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Rank %d received: %s, Grade: %.1f, ID: %d\n",
           my_rank, student.name, student.grade, student.id);

    MPI_Finalize();
    return 0;
}
