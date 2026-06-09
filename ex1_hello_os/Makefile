CC = mpicc
CFLAGS = -O2 -Wall
LIBS = -lm

TARGETS = hello_os hello_ring

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(TARGETS) *.o

.PHONY: all clean
