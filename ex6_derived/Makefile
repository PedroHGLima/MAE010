CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = student_struct student_three_bcasts

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

run: all
	@echo "=== Rodando 1 Bcast (Derived Struct) ==="
	mpiexec -n 4 ./student_struct
	@echo "\n=== Rodando 3 Bcasts ==="
	mpiexec -n 4 ./student_three_bcasts

clean:
	rm -f $(TARGETS) *.o

.PHONY: all run clean
