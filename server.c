#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/*
server receives
1. request for public key
2. encrypted messages (ciphertexts)

server sends
1. public key

runs
1. setup(\lambda) -> PK, SK
2. decrypt(SK, CT) -> M
*/

int main(int argc, char *argv[]) {
  return 0;
}
