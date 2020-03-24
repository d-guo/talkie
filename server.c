#include "scheme.h"

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
  int sockfd, cli_socket;
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(9002);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

  listen(sockfd, 5);
  cli_socket = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

  char d[256] = "works!";
  write(cli_socket, d, sizeof(d));

  close(sockfd);
  return 0;
}
