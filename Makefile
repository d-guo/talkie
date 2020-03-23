CC = gcc
ARGS = -Wall -g

all: server client

server: server.c
	$(CC) $(ARGS) server.c -o server

client: client.c
	$(CC) $(ARGS) client.c -o client

clean:
	rm -f server client
