CC = gcc
ARGS = -Wall -g

all: server client

scheme.o: scheme.c
	$(CC) $(ARGS) -c scheme.c

server.o: server.c
	$(CC) $(ARGS) -c server.c

server: server.o scheme.o
	$(CC) $(ARGS) server.o scheme.o -o server

client.o: client.c
	$(CC) $(ARGS) -c client.c

client: client.o scheme.o
	$(CC) $(ARGS) client.o scheme.o -o client

clean:
	rm -f server client *.o
