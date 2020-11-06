CC=gcc
ODIR=../obj
IDIR =../include
MKDIR_P=mkdir -p
CFLAGS=-I -O2 -Wall -Wextra

all: obj main

obj:
	${MKDIR_P} ../obj

_DEPS = mpeg.h utils.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o utils.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~