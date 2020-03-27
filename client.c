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
  //IP
  reception = recv(sockfd, PK.PK1, sizeof(PK.PK1), MSG_WAITALL);
  if(reception < 0) {
    fprintf(stderr, "ERROR receiving Public Key 1\n");
  }
  reception = recv(sockfd, PK.PK2, sizeof(PK.PK2), MSG_WAITALL);
  if(reception < 0) {
    fprintf(stderr, "ERROR receiving Public Key 2\n");
  }

  printf("Send messages (bits 0 or 1) to server or -1 to disconnect and shutdown server\n");
  printf("Ciphertext saved in CT file\n");

  CT_tuple CT;
  printf("%d\n", CT.CT1[4095]);
  while(1) {
    printf("Input bit: ");
    fscanf(stdin, "%d", &M);
    
    if(M == -1) {
      break;
    }

    //CT = Enc(PK, M);

    //save CT into file

    //send CT

  }

  close(sockfd);
  return 0;
}
