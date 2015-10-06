CC=gcc
CFLAGS=-I.
CFLAGS+= -m32
OBJ = lib.o main.o 
%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

%: %.o
	$(CC) -o $@ $< $(CFLAGS)

all: $(OBJ)
	$(CC) -o $@ $^ -I. -m32

.PHONY: clean

clean:
	rm -f *.o *~ core *.swp 
