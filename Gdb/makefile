.PHONY: clean
CC = gcc
CFLAGS = -c -Wall -g -std=c99 -I./
all: clean zr
zr : zr.o add.o
	$(CC) $(LDFLAGS)  -o $@ $^
%.o : %.c
	$(CC) $(CFLAGS)  -o $@ $<
clean:
	rm -f zr *.o core*
