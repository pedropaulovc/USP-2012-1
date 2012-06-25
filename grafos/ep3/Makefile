CC=gcc
CFLAGS=-Wall -ansi -pedantic -O2 -Wno-unused-result -lm
DEPS = digrafo.h item.h vertex.h fila.h util.h experimento.h driver.h
OBJ = digrafo.o fila.o experimento.o driver.o main.o

all: EP3-Stefano-Pedro

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

EP3-Stefano-Pedro: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o EP3-Stefano-Pedro
