#include "scheme.h"

/*
client receives
1. public key

client sends
1. request for public key
2. encrypted messages

runs
1. encrpyt(PK, M) -> CT
*/

int main(int argc, char *argv[]) {
  int sockfd, connection;
  struct sockaddr_in serv_addr, cli_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(9002);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  connection = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

  //testing recv from server
  int64_t recv_int = __INT64_MAX__;
  char d[256];
  printf("%ld\n", recv_int);
  recv(sockfd, &d, sizeof(d), 0);
  printf("Nice: %s\n", d);
  //

  close(sockfd);
  return 0;
}
