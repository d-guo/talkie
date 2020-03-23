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
scheme includes setup, encrypt, decrypt

all operations are done over the field Z_q, where q is some (large) prime
messages are in {0, 1} (a single bit)

Setup takes in a security parameter lambda
    samples A from uniform distribution as n x m matrix
    samples e from error distribution (chosen later, probably discrete gaussian) as m-vector
    samples s from uniform distribution as n-vector
outputs keys as PK = (A, s^T * A + e^T) and SK = s

Enc takes in PK and message M

*/

typedef struct {
    int* x;
    int* y;
} tuple;

typedef struct {
    tuple PK;
    int* SK;
} keys;

keys Setup(int lambda);
tuple Enc(tuple PK, int M);
int Dec(int* SK, tuple CT);
#endif