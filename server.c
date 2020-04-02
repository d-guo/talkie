#include "scheme.h"

/*
server receives
1. request for public key
2. encrypted messages (ciphertexts)

server sends
1. public key

runs
1. setup() -> PK, SK
2. decrypt(SK, CT) -> M
*/


int main(int argc, char *argv[]) {
  int sockfd, cli_socket, binding, reception, M;
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sockfd < 0) {
    fprintf(stderr, "ERROR opening socket\n");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  binding = bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
  if(binding < 0) {
    fprintf(stderr, "ERROR on binding\n");
  }

  listen(sockfd, 5);

  clilen = sizeof(cli_addr);
  cli_socket = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
  if (cli_socket < 0) {
    fprintf(stderr, "ERROR on accept\n");
  }

  //generate keys
  keys PS = Setup();
  write(cli_socket, PS.PK.A, n * m * sizeof(int));
  write(cli_socket, PS.PK.b, m * sizeof(int));

  CT_tuple CT;
  CT.CT1 = malloc(n * sizeof(int));

  while(1) {
    //check number of sockets and shutdown if 0
    
    
    //receive CT
    reception = recv(cli_socket, CT.CT1, n * sizeof(int), MSG_WAITALL);
    if(reception < 0) {
      fprintf(stderr, "ERROR receiving Ciphertext 1\n");
    }
    reception = recv(cli_socket, &CT.CT2, sizeof(int), MSG_WAITALL);
    if(reception < 0) {
      fprintf(stderr, "ERROR receiving Ciphertext 2\n");
    }

    //decrypt CT and print message
    M = Dec(PS.SK, CT);
    printf("%d\n", M);
  }

  close(sockfd);
  return 0;
}
