CC=gcc
CFLGAS=-I -O2 -Wall -lm 
OBJ = main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLGAS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLGAS)

clean:
	rm *.o