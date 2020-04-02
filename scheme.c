#include "scheme.h"

int* vv_add(int* x, int* y, int* z) {
    for(int i = 0; i < m; i++) {
        *(z + i) = modq(*(x + i) + *(y + i));
    }
    return z;
}

int vv_mult_m(int* x, int* y) {
    int z = 0;
    for(int i = 0; i < m; i++) {
        z += *(x + i) * *(y + i);
    }
    return modq(z);
}

int vv_mult_n(int* x, int* y) {
    int z = 0;
    for(int i = 0; i < n; i++) {
        z += *(x + i) * *(y + i);
    }
    return modq(z);
}

int* mv_mult(int* A, int* x, int* y) {
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            *(y + i) += *(A + i * n + j) * *(x + j);
        }
    }
    for(int i = 0; i < m; i++) {
        *(y + i) = modq(*(y + i));
    }
    return y;
}

int* vm_mult(int* x, int* A, int* y) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            *(y + i) += *(A + j * n + i) * *(x + j);
        }
    }
    for(int i = 0; i < n; i++) {
        *(y + i) = modq(*(y + i));
    }
    return y;
}

keys Setup() {
    keys PS_keys;
    PS_keys.PK.A = malloc(m * n * sizeof(int));
    PS_keys.PK.b = malloc(m * sizeof(int));
    PS_keys.SK = malloc(n * sizeof(int));
    
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            *(PS_keys.PK.A + i * n + j) = modq(rand());
        }
    }
    for(int i = 0; i < n; i++) {
        *(PS_keys.SK + i) = modq(rand());
    }

    //IP
    int* e = malloc(m * sizeof(int));
    for(int i = 0 ; i < m; i++) {
        *(e + i) = 0;
    }

    int* A_SK = malloc(m * sizeof(int));
    mv_mult(PS_keys.PK.A, PS_keys.SK, A_SK);
    vv_add(A_SK, e, PS_keys.PK.b);
    free(A_SK);
    
    return PS_keys;
}

CT_tuple Enc(pub_key_tuple PK, int M) {
    CT_tuple CT;
    CT.CT1 = malloc(n * sizeof(int));

    int* r = malloc(m * sizeof(int));
    for(int i = 0 ; i < m; i++) {
        *(r + i) = modq(rand());
    }

    vm_mult(r, PK.A, CT.CT1);
    CT.CT2 = modq(vv_mult_m(PK.b, r) + (int) (q / 2) * M);

    free(r);

    return CT;
}

int Dec(int* SK, CT_tuple CT) {
    int w = modq(CT.CT2 - vv_mult_n(CT.CT1, SK));
    if(w < (int) (q / 4)) {
        printf("%d\n", w);
        return 0;
    }
    printf("%d\n", w);
    return 1;
}

int main() {
    keys PS_keys = Setup();
    CT_tuple CT = Enc(PS_keys.PK, 0);
    int M = Dec(PS_keys.SK, CT);
    printf("%d\n", M);
}
