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
  int sockfd, connection, reception, M = 0;
  struct sockaddr_in serv_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    fprintf(stderr, "ERROR opening socket\n");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(9002);
  serv_addr.sin_addr.s_addr = INADDR_ANY;

  connection = connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
  if(connection < 0) {
    fprintf(stderr, "ERROR connecting to server\n");
  }

  pub_key_tuple PK;
  PK.A = malloc(n * m * sizeof(int));
  PK.b = malloc(m * sizeof(int));
  reception = recv(sockfd, PK.A, n * m * sizeof(int), MSG_WAITALL);
  if(reception < 0) {
    fprintf(stderr, "ERROR receiving Public Key 1\n");
  }
  reception = recv(sockfd, PK.b, m * sizeof(int), MSG_WAITALL);
  if(reception < 0) {
    fprintf(stderr, "ERROR receiving Public Key 2\n");
  }

  printf("Send messages (bits 0 or 1) to server or -1 to disconnect and shutdown server\n");
  printf("Ciphertext saved in CT file\n");

  CT_tuple CT;
  CT.CT1 = malloc(n * sizeof(int));
  //while(1) {
    printf("Input bit: ");
    fscanf(stdin, "%d", &M);
    
    //if(M == -1) {
    //  break;
    //}

    CT = Enc(PK, M);

    //save CT into file

    //send CT
    write(sockfd, CT.CT1, n * sizeof(int));
    write(sockfd, &CT.CT2, sizeof(int));


  //}

  close(sockfd);
  return 0;
}
