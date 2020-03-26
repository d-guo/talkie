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
n = 2^12 = 4096
q = smallest prime greater than 2^24 = 2^24 + 43 = 16777259
m = floor(1.1 * n * log(q)) = 74953
alpha = 1/(sqrt(n) * log^2(n)) = 0.00022584298839036548
mu = 0

scheme includes setup, encrypt, decrypt

all operations are done over the field Z_q, where q is some (large) prime
messages are in {0, 1} (a single bit)

Setup takes in a security parameter lambda (we fix this value)
    samples A from uniform distribution as n x m matrix
    samples e from error distribution (chosen later, probably discrete gaussian) as m-vector
    samples s from uniform distribution as n-vector
outputs keys as PK = (A, s^T * A + e^T) and SK = s

Enc takes in PK and message M
    samples r from uniform distribution of {0, 1} as a m matrix
    interpret PK = (A, s^T * A + e^T) as (A, b^T)
outputs ciphertext as CT = (Ar, b^Tr + M * floor(q / 2))

Dec takes in SK and CT
    interpret CT = (Ar, b^Tr + M * floor(q / 2)) as (u, v)
    find w = ||v - s^TM||
outputs message 0 if w < q / 4 and 1 otherwise
*/

#define n 4096
#define q 16777259
#define m 74953
#define alpha 0.00022584298839036548
#define mu 0

typedef struct {
    int PK1[n][n];
    int PK2[n];
} pub_key_tuple;

typedef struct {
    int CT1[n];
    int CT2[n];
} CT_tuple;

typedef struct {
    pub_key_tuple PK;
    int SK[n];
} keys;

int* vv_add(int x[n], int y[n]);
int* mv_mult(int A[n][n], int x[n]);

keys Setup();
CT_tuple Enc(pub_key_tuple PK, int M);
int Dec(int* SK, CT_tuple CT);
#endif