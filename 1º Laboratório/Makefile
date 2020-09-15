CC=gcc
CFLGAS=-I -O2 -Wall
DEPS = lista.h
OBJ = main.o lista.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLGAS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLGAS)

clean:
	rm *.o