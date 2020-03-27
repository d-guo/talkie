#include "scheme.h"

int* vv_add(int x[m], int y[m]) {
    static int z[m];
    for(int i = 0; i < m; i++) {
        z[i] = x[i] + y[i];
    }
    for(int i = 0; i < m; i++) {
        z[i] = z[i] % q;
    }
    return z;
}

int* mv_mult(int A[m][n], int x[n]) {
    static int y[m];
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    for(int i = 0; i < m; i++) {
        y[i] = y[i] % q;
    }
    return y;
}

int* vm_mult(int x[m], int A[m][n]) {
    static int y[n];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            y[i] += A[i][j] * x[j];
        }
    }
    for(int i = 0; i < n; i++) {
        y[i] = y[i] % q;
    }
    return y;
}
/*
keys Setup() {
    static keys PS_keys;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            PS_keys.PK.A[i][j] = rand() % q;
        }
    }
    for(int i = 0; i < n; i++) {
        PS_keys.SK[i] = rand() % q;
    }
    //IP
    static int e[m];
    for(int i = 0 ; i < m; i++) {
        e[i] = rand() % q;
    }
    memcpy(PS_keys.PK.b, vv_add(mv_mult(PS_keys.PK.A, PS_keys.SK), e), sizeof(PS_keys.PK.b));
    return PS_keys;
}


CT_tuple Enc(pub_key_tuple PK, int M) {



}

int Dec(int* SK, CT_tuple CT) {



}
*/