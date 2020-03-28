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

int vv_mult_m(int x[m], int y[m]) {
    int z = 0;
    for(int i = 0; i < m; i++) {
        z += x[i] * y[i];
    }
    return z % q;
}

int vv_mult_n(int x[n], int y[n]) {
    int z = 0;
    for(int i = 0; i < n; i++) {
        z += x[i] * y[i];
    }
    return z % q;
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
        e[i] = 0;
    }
    memcpy(PS_keys.PK.b, vv_add(mv_mult(PS_keys.PK.A, PS_keys.SK), e), sizeof(PS_keys.PK.b));
    return PS_keys;
}

CT_tuple Enc(pub_key_tuple PK, int M) {
    static CT_tuple CT;
    static int r[m];
    for(int i = 0 ; i < m; i++) {
        r[i] = rand() % q;
    }
    memcpy(CT.CT1, vm_mult(r, PK.A), sizeof(CT.CT1));
    CT.CT2 = vv_mult_m(PK.b, r) + (int) (q / 2) * M;
    return CT;
}

int Dec(int* SK, CT_tuple CT) {
    int w = (CT.CT2 - vv_mult_n(CT.CT1, SK)) % q;
    if(w < (int) (q / 4)) {
        return 0;
    }
    return 1;
}