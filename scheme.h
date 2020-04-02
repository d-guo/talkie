#ifndef SCHEME_H
#define SCHEME_H

#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

/*
parameters:
n = 2^10 = 1024 (in practice would be much larger)
q = smallest prime greater than 2^24 = 2^24 + 7 = 1048583
m = floor(1.1 * n * log(q)) = 15615
alpha = 1/(sqrt(n) * log^2(n)) = 0.0006504278065642525
mu = 0

scheme includes setup, encrypt, decrypt

all operations are done over the field Z_q, where q is some (large) prime
messages are in {0, 1} (a single bit)

Setup takes in a security parameter lambda (we fix this value as n above)
    samples A from uniform distribution as n x m matrix
    samples e from error distribution (discrete gaussian with mean mu variance alpha) as m-vector
    samples s from uniform distribution as n-vector
outputs keys as PK = (A, s^T * A + e^T) and SK = s

Enc takes in PK and message M
    samples r from uniform distribution of {0, 1} as a m-vector
    interpret PK = (A, s^T * A + e^T) as (A, b^T)
outputs ciphertext as CT = (A * r, b^T * r + M * floor(q / 2))

Dec takes in SK and CT
    interpret CT = (A * r, b^T * r + M * floor(q / 2)) as (u, v)
    find w = ||v - s^T * u||
outputs message 0 if w < q / 4 and 1 otherwise
*/

#define n 1024
#define q 1048583
#define m 15615
#define alpha 0.0006504278065642525
#define mu 0

typedef struct {
    int* A; //n x m
    int* b; //m
} pub_key_tuple;

typedef struct {
    int* CT1; //n
    int CT2;
} CT_tuple;

typedef struct {
    pub_key_tuple PK;
    int* SK; //n
} keys;

//perform operation and put into last parameter
int* vv_add(int* x, int* y, int* z); // m-vectors
int vv_mult_m(int* x, int* y); // m-vectors
int vv_mult_n(int* x, int* y); // n-vectors
int* mv_mult(int* A, int* x, int* y); // n x m matrix m-vector
int* vm_mult(int* x, int* A, int* y); // n-vector, n x m matrix

//so apparently ?? the % operator gives the remainder NOT the mod, so -1 % 2 = -1, not 1 which is bad for us
int modq(int x) {
    return (int) ((((long long int) x % q) + q) % q);
}

keys Setup();
CT_tuple Enc(pub_key_tuple PK, int M);
int Dec(int* SK, CT_tuple CT);
#endif