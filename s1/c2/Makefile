CC=gcc
DEBUG=gdb
# CFLAGS=

.SUFFIXES: .c .o .exe

MAIN = FixedXor
DEPS = FixedXor.h

%.o: %.c $(DEPS)
	$(CC) -g -c $< -o $@

%.exe: %.o
	$(CC) -o $@ $^

%.debug: %.o
	$(CC) -g -o $@ $^

.PHONY: run clean debug

run: $(MAIN).exe
	./$<

debug: $(MAIN).debug
	$(DEBUG) ./$<

clean:
	-rm *.o *.exe *.debug