# GRR20190363 Luan Machado Bernardt

CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm

OBJECT= myht

all: $(OBJECT) clean

$(OBJECT): $(OBJECT).o hash.o
	$(CC) $(CFLAGS) $(OBJECT).o hash.o -o $(OBJECT) $(LDFLAGS)

$(OBJECT).o: $(OBJECT).c hash.h
	$(CC) $(CFLAGS) $(OBJECT).c -c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) hash.c -c

clean:
	-rm -f *.o

purge:
	-rm -f $(OBJECT)
