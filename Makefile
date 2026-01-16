CC = riscv64-linux-gnu-gcc
CFLAGS = -O0 -g -Wall

all: test

test: main.o tests.o framework.o
	$(CC) $^ -o test

clean:
	rm -f *.o test

