CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = hello_gather minmax

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

run: all
	@echo "=== Rodando 4(a) (hello_gather) ==="
	mpiexec -n 4 ./hello_gather
	@echo "\n=== Rodando 4(b) (minmax) ==="
	mpiexec -n 4 ./minmax

clean:
	rm -f $(TARGETS) *.o

.PHONY: all run clean
