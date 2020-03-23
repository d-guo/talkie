CC = gcc
ARGS = -Wall -g

all: server_c_tcp client_c_tcp

server_c_tcp: server.c
	$(CC) $(ARGS) server.c -o server

client_c_tcp: client.c
	$(CC) $(ARGS) client.c -o client

clean:
	rm -f server client
