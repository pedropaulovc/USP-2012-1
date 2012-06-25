CC=gcc
CFLAGS=-Wall -ansi -pedantic -O3 -Wno-unused-result -lm
DEPS = digrafo.h item.h vertex.h fila.h util.h
OBJ = digrafo.o fila.o

all: EP3-Stefano-Pedro

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

EP3-Stefano-Pedro: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

