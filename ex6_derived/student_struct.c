#include <stdio.h>
#include <stddef.h>
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
    MPI_Datatype student_type;

    int block_lengths[3] = {50, 1, 1};
    MPI_Aint displacements[3];
    MPI_Datatype types[3] = {MPI_CHAR, MPI_DOUBLE, MPI_INT};

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    displacements[0] = offsetof(struct Student, name);
    displacements[1] = offsetof(struct Student, grade);
    displacements[2] = offsetof(struct Student, id);

    MPI_Type_create_struct(3, block_lengths, displacements, types, &student_type);
    MPI_Type_commit(&student_type);

    if (my_rank == 0)
    {
        snprintf(student.name, 50, "Alice");
        student.grade = 9.5;
        student.id = 12345;
    }

    MPI_Bcast(&student, 1, student_type, 0, MPI_COMM_WORLD);

    printf("Rank %d received: %s, Grade: %.1f, ID: %d\n",
           my_rank, student.name, student.grade, student.id);

    MPI_Type_free(&student_type);
    MPI_Finalize();
    return 0;
}
