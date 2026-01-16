CC = riscv64-linux-gnu-gcc
CFLAGS = -O2 -Wall

all: test

test: main.c test_framework.c test_instr.c
	$(CC) $(CFLAGS) $^ -o test

clean:
	rm -f test
