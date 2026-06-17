CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = mpi_vecadd_gather mpi_vecadd_allgather

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

run: all
	@echo "=== Rodando Gather ==="
	mpiexec -n 4 ./mpi_vecadd_gather
	@echo "\n=== Rodando Allgather ==="
	mpiexec -n 4 ./mpi_vecadd_allgather

clean:
	rm -f $(TARGETS) *.o

.PHONY: all run clean
