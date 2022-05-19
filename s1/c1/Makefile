CC=gcc
CFLAGS=-I

.SUFFIXES: .c .o .exe

MAIN=HexToB64

%.o: %.c
	$(CC) -c $< -o $@

%.exe: %.o
	$(CC) -o $@ $^

.PHONY: run clean

run: $(MAIN).exe
	./$<

clean:
	-rm *.o *.exe