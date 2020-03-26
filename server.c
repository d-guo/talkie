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
  int sockfd, cli_socket, binding, reception, M;
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    fprintf(stderr, "ERROR opening socket\n");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(9002);
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

  static int PK1[n][n];
  static int PK2[n];
  //public key
  write(cli_socket, PK1, sizeof(PK1));
  write(cli_socket, PK2, sizeof(PK2));

  static CT_tuple CT;
  while(1) {
    //receive CT
    reception = recv(sockfd, &CT.CT1, sizeof(CT.CT1), MSG_WAITALL);
    reception = recv(sockfd, &CT.CT2, sizeof(CT.CT2), MSG_WAITALL);

    //save CT into file

    //decrypt CT and print message




  }

  close(sockfd);
  return 0;
}
