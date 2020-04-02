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
  int sockfd, connection, reception = 0;
  int M = 0;
  struct sockaddr_in serv_addr;

  sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sockfd < 0) {
    fprintf(stderr, "ERROR opening socket\n");
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(8080);

  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)  
    { 
        fprintf(stderr, "Error in conversion at inet_pton\n"); 
        return -1; 
    } 

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
  while(1) {
    printf("Input bit: ");
    fscanf(stdin, "%d", &M);
    
    //shutdown if M = -1
    if(M == -1) {
      CT = Enc(PK, 0);
      write(sockfd, CT.CT1, n * sizeof(int));
      write(sockfd, &M, sizeof(int));
      break;
    }

    CT = Enc(PK, M);

    //send CT
    write(sockfd, CT.CT1, n * sizeof(int));
    write(sockfd, &CT.CT2, sizeof(int));
  }

  close(sockfd);
  return 0;
}
