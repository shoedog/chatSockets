CC=gcc
CFLAGS= -g -Wall

OBJS = client.o utilsIO.o

all: client

client: client.o utilsIO.o
	$(CC) $(CFLAGS) -o client client.o utilsIO.o

client.o: utilsIO.c utilsIO.h
	$(CC) $(CFLAGS) -c client.c

utilsIO.o: utilsIO.c utilsIO.h
	$(CC) $(CFLAGS) -c utilsIO.c

clean: 
	$(RM) $(TARGET) *.o
