CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = hello_os hello_ring

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

run: all
	@echo "=== Rodando Exercício 1(a) (hello_os) ==="
	mpiexec -n 8 ./hello_os
	@echo "\n=== Rodando Exercício 1(b) (hello_ring) ==="
	mpiexec -n 4 ./hello_ring

clean:
	rm -f $(TARGETS) *.o

.PHONY: all run clean
