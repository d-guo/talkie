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
n = 2^20 = 1099511627776
q = smallest prime greater than 2^40 = 2^40 + 15 = 1099511627791
m = floor(1.1 * n * log(q)) = 33533428930592
alpha = 1/(sqrt(n) * log^2(n)) = 1.2405925875935603e-09


scheme includes setup, encrypt, decrypt

all operations are done over the field Z_q, where q is some (large) prime
messages are in {0, 1} (a single bit)

Setup takes in a security parameter lambda
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