CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = hello_gather minmax

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

run: all
	mpiexec -n 4 ./hello_gather
	mpiexec -n 4 ./minmax

clean:
	rm -f $(TARGETS) *.o

.PHONY: all run clean
