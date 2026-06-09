CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = mpi_psum

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

run: all
	mpiexec -n 4 ./mpi_psum

clean:
	rm -f $(TARGETS) *.o

.PHONY: all run clean
