CC=gcc
CFLGAS=-I -O2 -Wall -lm 
OBJ = main.o utils.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLGAS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLGAS)

clean:
	rm *.o