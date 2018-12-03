CC=gcc
CFLAGS=-lWarn -pedantic

tempread: tempread.o 
	$(CC) tempread.o -L.  -lcurl -lwiringPi -o tempread


tempread.o:	tempread.c
	$(CC) $(CFLAGS) -c -ansi $<

all: tempread

clean:
	rm  tempread *.o
