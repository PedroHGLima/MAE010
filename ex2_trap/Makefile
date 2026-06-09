CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = mpi_trap_generalized

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

run: all
	echo "0 3.141592653589793 10" | mpiexec -n 3 ./mpi_trap_generalized

clean:
	rm -f $(TARGETS) *.o

.PHONY: all run clean
